// ==============================[ Includes ]====================================
#include "../drivers/dht22/dht22_driver.h"
// ==========================[ Private defines ]=================================
#define DHT22_PORT GPIOA
#define DHT22_PIN  GPIO_PIN_1

#define DHT22_POWER_ON_TIME		1
#define DHT22_DATA_BITS_SIZE	8
// ==========================[ Private Functions ]===============================
static void setPinAsOutput(GPIO_TypeDef *GPIOx, uint16_t GPIOPin){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIOPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

static void setPinAsInput(GPIO_TypeDef *GPIOx, uint16_t GPIOPin){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIOPin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

// ==========================[ Public Functions ]===============================
void dht22Start(void){
	//Check pin to output and pull the pin low
	setPinAsOutput(DHT22_PORT, DHT22_PIN);
	HAL_GPIO_WritePin(DHT22_PORT, DHT22_PIN, GPIO_PIN_RESET);

	//Wait at least 1 ms so the DHT22 detects the MCU's signal
	delayMicro(1200);

	//Pull the pin high to finish the start signal
	HAL_GPIO_WritePin(DHT22_PORT, DHT22_PIN, GPIO_PIN_SET);
	delayMicro(40);

	//Change pin to input in order to receive the sensor's response
	setPinAsInput(DHT22_PORT, DHT22_PIN);
	return;
}

tDht22State dht22CheckResponse(void){
	tDht22State status = DHT22_SENSOR_NOT_PRESENT;
	//DHT22 response, see if the signal is pulled low
	delayMicro(40);													//Check at the middle of the interval (80 us)
	if(HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN) == GPIO_PIN_RESET){
		//The signal should be pulled high now for 80 us. If not, the sensor is not present.
		delayMicro(40);												//Check at the middle of the interval
		status = (HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN) == GPIO_PIN_SET) ? DHT22_OK : DHT22_SENSOR_NOT_PRESENT;
	}

	//Wait until the pin is pulled low again, just before the DHT22 starts transmitting data.
	while(HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN) == GPIO_PIN_SET);
	return status;
}

uint8_t dht22Read(void){
	uint8_t data = 0;
	//Prepare to receive data bits
	for(uint8_t i = 0; i < DHT22_DATA_BITS_SIZE; i++){
		//Wait for pin to become high and then check the high time length
		while(HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN) == GPIO_PIN_RESET);
		delayMicro(40);												//A "0" is a high level expected to last 28 us (max), so if there is
																	//a high after 40 us, it is effectively a "1".
		if(HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN) == GPIO_PIN_RESET){
			//The sent bit is "0".
			data &= ~(1 << (7 - i));
		}
		else{
			data |= (1 << (7 - i));
		}

		//Wait until the signal goes low again, the DHT22 is ready to send another bit
		while(HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN) == GPIO_PIN_SET);
	}
	return data;
}


tDht22State checksumControl(uint8_t *hrBytes, uint8_t *tempBytes, uint8_t checksum){
	uint16_t sum;
	uint8_t calculatedChecksum;

	//Calculate checksum
	sum = ((uint16_t) hrBytes[0] + (uint16_t) hrBytes[1] + (uint16_t) tempBytes[0] + (uint16_t) tempBytes[1]);
	calculatedChecksum = (uint8_t) (sum & 0xFF);									//Take only the first 8 bits as the checksum

	//Compare with received value and return the result of the comparation
	return (checksum == calculatedChecksum) ? DHT22_OK : DHT22_CHECKSUM_FAILED;
}






