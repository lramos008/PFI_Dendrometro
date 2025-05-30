#ifndef HM10_DRIVER_H
#define HM10_DRIVER_H
// ==========================[ Includes ]===============================
#include <string.h>
#include <stdbool.h>
#include "main.h"
// ==========================[ Typedefs ]===============================
typedef enum{
	HM10_OK = 0,
	HM10_ERROR_BUSY,
	HM10_ERROR_UART,
	HM10_ERROR_AT_COMMAND_RESPONSE,
	HM10_ERROR_STRING,
	HM10_ERROR_TIMEOUT,
	HM10_ERROR_UNKNOWN
}HM10Status_t;

typedef enum{
	HM10_BAUD_9600 = 0,
	HM10_BAUD_19200,
	HM10_BAUD_38400,
	HM10_BAUD_57600,
	HM10_BAUD_115200,
	HM10_BAUD_4800,
	HM10_BAUD_2400,
	HM10_BAUD_1200,
	HM10_BAUD_230400
}HM10Baudrate_t;

typedef enum{
	HM10_ROLE_PERIPHERAL = 0,
	HM10_ROLE_CENTRAL
}HM10Role_t;

typedef enum{
	HM10_AUTO_CONNECT = 0,
	HM10_WAIT_AT_START
}HM10WorkType_t;

typedef enum{
	HM10_ADV_ALL = 0,
	HM10_ADV_ONLY_LAST_CONNECTION,
	HM10_ADV_NO_CONNECTION,
	HM10_ADV_ONLY_ADV
}HM10AdvType;

typedef enum{
	HM10_INTERVAL_100MS = 0,				// 100 ms
	HM10_INTERVAL_252MS,					// 252,5 ms
	HM10_INTERVAL_211MS, 					// 211,25 ms
	HM10_INTERVAL_318MS,					// 318,75 ms
	HM10_INTERVAL_417MS, 					// 417,50 ms
	HM10_INTERVAL_546MS,					// 546,25 ms
	HM10_INTERVAL_760MS,					// 760,00 ms
	HM10_INTERVAL_852MS,					// 852,50 ms
	HM10_INTERVAL_1022MS,					// 1022,5 ms
	HM10_INTERVAL_1285MS,					// 1285 ms
	HM10_INTERVAL_2000MS,					// 2000 ms
	HM10_INTERVAL_3000MS,					// 3000 ms
	HM10_INTERVAL_4000MS,					// 4000 ms
	HM10_INTERVAL_5000MS,					// 5000 ms
	HM10_INTERVAL_6000MS,					// 6000 ms
	HM10_INTERVAL_7000MS					// 7000 ms
}HM10AdvInterval_t;

typedef enum{
	HM10_POWER_LOW = 0,					// -23 dbm
	HM10_POWER_MEDIUM_LOW,				// -6 dbm
	HM10_POWER_MEDIUM_HIGH,				//  0 dbm
	HM10_POWER_HIGH						//  6 dbm
}HM10PowerMode_t;

// ======================[ Public functions prototypes ]===========================
//Init
HM10Status_t HM10Init(UART_HandleTypeDef *huart);
void HM10RegisterUart(UART_HandleTypeDef *huart);
void HM10Callback(UART_HandleTypeDef *huart);
HM10Status_t HM10IsPresent(void);

//Config
HM10Status_t HM10SetBaudrate(HM10Baudrate_t baudrate);
HM10Status_t HM10SetDeviceName(const char *name);
HM10Status_t HM10SetRole(HM10Role_t role);
HM10Status_t HM10SetModuleWorkType(HM10WorkType_t workType);
HM10Status_t HM10ConfigAdvertisingType(HM10AdvType type);
HM10Status_t HM10SetAdvertisingInterval(HM10AdvInterval_t interval);
HM10Status_t HM10ConfigTransmissionPower(HM10PowerMode_t powerMode);
HM10Status_t HM10EnableAutoSleep(void);

//Control
HM10Status_t HM10Send(const uint8_t *data, uint16_t length);
HM10Status_t HM10ResetModule(void);
const char *HM10GetLastResponse(void);
uint8_t *HM10GetReceptionBuffer(void);
void HM10ClearReceptionBuffer(void);
#endif //HM10_DRIVER_H
