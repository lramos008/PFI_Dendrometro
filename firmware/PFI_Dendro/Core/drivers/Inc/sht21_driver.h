#ifndef SHT21_DRIVER_H
#define SHT21_DRIVER_H
// ==========================[ Includes ]===============================
#include "main.h"

#include "crc8.h"
// ==========================[ Typedefs ]===============================
typedef enum{
	SHT21_OK = 0,
	SHT21_ERROR_I2C_TRANSMIT,
	SHT21_ERROR_I2C_RECEIVE,
	SHT21_ERROR_CRC,
	SHT21_ERROR_UNKNOWN
}tSht21Status;

// =======================[ Public functions ]==========================
tSht21Status sht21Init(void);
tSht21Status sht21GetRelativeHumidity(float *relativeHumidity);
tSht21Status sht21GetTemperature(float *temperature);
tSht21Status sht21SoftReset(void);
#endif //SHT21_DRIVER_H
