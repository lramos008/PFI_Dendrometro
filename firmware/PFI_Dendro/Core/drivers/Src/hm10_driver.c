// =============================[ Includes ]===================================
#include "hm10_driver.h"
#include <string.h>
#include <stdio.h>


// ========================[ AT commands ]==============================
#define HM10_CHECK_RESPONSE				"AT"
#define HM10_SET_DEVICE_NAME			"AT+NAME"
#define HM10_SET_BAUDRATE				"AT+BAUD"
#define HM10_CHECK_BAUDRATE				"AT+BAUD?"
#define HM10_CONFIG_ROLE				"AT+ROLE"
#define HM10_SET_ADV_INTERVAL			"AT+ADVI"
#define HM10_SET_ADV_TYPE				"AT+ADTY"
#define HM10_SLEEP						"AT+SLEEP"
#define HM10_RESET						"AT+RESET"
#define HM10_ENABLE_AUTOSLEEP			"AT+PWRM1"
#define HM10_DEFINE_WORK_TYPE			"AT+IMME"
#define HM10_CONFIG_TRANSMISSION_POWER	"AT+POWE"


// ==========================[ Private defines ]===============================
#define CMD_BUFFER_SIZE          32
#define RESPONSE_BUFFER_SIZE     32
#define HM10_DMA_BUFFER_SIZE     64
#define GLOBAL_TIMEOUT           100
#define ENABLE_CONFIG_FUNCTIONS  0


// ======================[ Global variables ]===========================
static UART_HandleTypeDef *hm10Uart = NULL;
char response[RESPONSE_BUFFER_SIZE] = {0};
uint8_t HM10DMABuffer[HM10_DMA_BUFFER_SIZE] = {0};
volatile bool receptionCompleteFlag = false;							//Use to know when to process a received command
volatile uint16_t receivedBytes = 0;



// ======================[ Public functions: Initialization ]===========================
//Initializes the HM10 for its use
HM10Status_t HM10Init(UART_HandleTypeDef *huart){
	HM10Status_t status;
	//Register the used UART
	hm10Uart = huart;

//	//Check if the device is present
//	status = HM10IsPresent();
//	if(status != HM10_OK) return status;

	//Initiate DMA reception
	HAL_UART_Receive_DMA(hm10Uart, HM10DMABuffer, HM10_DMA_BUFFER_SIZE);

	//Enable IDLE line interrupt
	__HAL_UART_ENABLE_IT(hm10Uart, UART_IT_IDLE);

	return HM10_OK;
}

void HM10RegisterUart(UART_HandleTypeDef *huart){
	hm10Uart = huart;
	return;
}



void HM10Callback(UART_HandleTypeDef *huart){
	if(__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE)){
		//Clear idle flag
		__HAL_UART_CLEAR_IDLEFLAG(huart);

		//Pause DMA
		HAL_UART_DMAStop(huart);

		//Calculate the number of received bytes
		receivedBytes = HM10_DMA_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(huart->hdmarx);

		//Process data
		receptionCompleteFlag = true;

		//Reset DMA
		HAL_UART_Receive_DMA(huart, HM10DMABuffer, HM10_DMA_BUFFER_SIZE);
	}
}



// ======================[ Config functions ]===========================
#if ENABLE_CONFIG_FUNCTIONS == 1
// ======================[ Config Private functions ]===========================
//Sends the AT command and handle the errors of trasmission, but not the response of the HM10
static HM10Status_t HM10TransmitATCommand(const char *command, char *response, uint16_t maxLength, uint32_t timeout){
	char cmdBuffer[CMD_BUFFER_SIZE] = {0};
	int bytesToSend;
	HAL_StatusTypeDef status;

	// Add termination characters to the command
	bytesToSend = snprintf(cmdBuffer, CMD_BUFFER_SIZE, "%s\r\n", command);
	if(bytesToSend < 0) return HM10_ERROR_STRING;

	// Send AT command via UART
	status = HAL_UART_Transmit(hm10Uart, (uint8_t *)cmdBuffer, bytesToSend, timeout);
	if(status == HAL_BUSY) return HM10_ERROR_BUSY;
	else if(status != HAL_OK) return HM10_ERROR_UART;

	//Wait for response
	uint32_t startTime = HAL_GetTick();
	uint16_t index = 0;
	uint8_t receivedCharacter;
	while(HAL_GetTick() - startTime < timeout && index < maxLength - 1){
		status = HAL_UART_Receive(hm10Uart, &receivedCharacter, 1, 10);			// 10 ms of timeout between each character
		if(status == HAL_OK){
			response[index++] = receivedCharacter;
			if(receivedCharacter == '\n') break;								//End of AT command
		}
	}

	// Add end of string character
	response[index] = '\0';

	//Handle condition if there is no character in reception
	if(index == 0) return HM10_ERROR_TIMEOUT;
	return HM10_OK;
}


//Send AT command and check for an OK response from the hm10
static HM10Status_t HM10SendATCheckOK(const char *command){
	HM10Status_t status;
	//Clean response buffer
	memset(response, 0, RESPONSE_BUFFER_SIZE);

	//Send AT command
	status = HM10TransmitATCommand(command, response, RESPONSE_BUFFER_SIZE, GLOBAL_TIMEOUT);

	//Check for errors
	if(status != HM10_OK) return status;														//Possible transmission error
	if(strncmp(response, "OK", 2) != 0) return HM10_ERROR_AT_COMMAND_RESPONSE;					//Possible error response from HM10
	return HM10_OK;
}


// ======================[ Config Public functions ]===========================
HM10Status_t HM10IsPresent(void){
	return HM10SendATCheckOK(HM10_CHECK_RESPONSE);
}



HM10Status_t HM10SetBaudrate(HM10Baudrate_t baudrate){
	char cmdBuffer[CMD_BUFFER_SIZE] = {0};
	//Build AT command
	snprintf(cmdBuffer, CMD_BUFFER_SIZE, "%s%u", HM10_SET_BAUDRATE, baudrate);
	return HM10SendATCheckOK((const char *)cmdBuffer);
}



HM10Status_t HM10SetDeviceName(const char *name){
	char cmdBuffer[CMD_BUFFER_SIZE] = {0};
	snprintf(cmdBuffer, CMD_BUFFER_SIZE, "%s%s", HM10_SET_DEVICE_NAME, name);
	return HM10SendATCheckOK((const char *)cmdBuffer);
}


HM10Status_t HM10SetRole(HM10Role_t role){
	char cmdBuffer[CMD_BUFFER_SIZE] = {0};
	//Build AT command
	snprintf(cmdBuffer, CMD_BUFFER_SIZE, "%s%u", HM10_CONFIG_ROLE, role);
	return HM10SendATCheckOK((const char *)cmdBuffer);
}



/*Define si se conecta automaticamente para recibir datos, o espera a un comando AT inicialmente IMME = 0 Auto connect*/
HM10Status_t HM10SetModuleWorkType(HM10WorkType_t workType){
	char cmdBuffer[CMD_BUFFER_SIZE] = {0};
	//Build AT command
	snprintf(cmdBuffer, CMD_BUFFER_SIZE, "%s%u", HM10_DEFINE_WORK_TYPE, workType);
	return HM10SendATCheckOK((const char *)cmdBuffer);
}



HM10Status_t HM10ConfigAdvertisingType(HM10AdvType type){
	char cmdBuffer[CMD_BUFFER_SIZE] = {0};
	//Build AT command
	snprintf(cmdBuffer, CMD_BUFFER_SIZE, "%s%u", HM10_SET_ADV_TYPE, type);
	return HM10SendATCheckOK((const char *)cmdBuffer);
}



HM10Status_t HM10SetAdvertisingInterval(HM10AdvInterval_t interval){
	char cmdBuffer[CMD_BUFFER_SIZE] = {0};
	//Build AT command
	snprintf(cmdBuffer, CMD_BUFFER_SIZE, "%s%X", HM10_SET_ADV_INTERVAL, interval);
	return HM10SendATCheckOK((const char *)cmdBuffer);
}



/*Configura la potencia de transmision (puede reducir el rango)*/
HM10Status_t HM10ConfigTransmissionPower(HM10PowerMode_t powerMode){
	char cmdBuffer[CMD_BUFFER_SIZE] = {0};
	//Build AT command
	snprintf(cmdBuffer, CMD_BUFFER_SIZE, "%s%u", HM10_CONFIG_TRANSMISSION_POWER, powerMode);
	return HM10SendATCheckOK((const char *)cmdBuffer);
}



HM10Status_t HM10EnableAutoSleep(void){
	return HM10SendATCheckOK(HM10_ENABLE_AUTOSLEEP);
}



HM10Status_t HM10ResetModule(void){
	return HM10SendATCheckOK(HM10_RESET);
}

#endif


// ======================[ Public functions: Control ]===========================
HM10Status_t HM10Send(const uint8_t *data, uint16_t length){
	HAL_StatusTypeDef status;
	status = HAL_UART_Transmit(hm10Uart, data, length, 100);
	if(status == HAL_BUSY) return HM10_ERROR_BUSY;
	else if(status != HAL_OK) return HM10_ERROR_UART;
	return HM10_OK;
}



const char *HM10GetLastResponse(void){
	return response;
}




uint8_t *HM10GetReceptionBuffer(void){
	return HM10DMABuffer;
}



void HM10ClearReceptionBuffer(void){
	memset(HM10DMABuffer, 0, HM10_DMA_BUFFER_SIZE);
}

