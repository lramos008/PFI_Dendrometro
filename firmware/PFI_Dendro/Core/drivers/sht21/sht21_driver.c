// ==========================[ Includes ]===============================
#include "sht21_driver.h"
// =======================[ Private Defines ]===========================
#define SHT21_SLAVE_ADDRESS					(0x40 << 1)
#define SHT21_ISSUE_TEMPERATURE_MEASURE		0xE3							//Hold master mode
#define SHT21_ISSUE_HUMIDITY_MEASURE		0xE5							//Hold master mode
#define SHT21_SOFT_RESET					0xFE							//Soft reset takes 15 ms
#define SHT21_MEASUREMENT_RESOLUTION		0x01							//RH: 8 bits, T: 12 bits
#define SHT21_READ_USER_REGISTER			0xE7
#define SHT21_WRITE_USER_REGISTER			0xE6

// =====================[ External variables ]==========================
extern I2C_HandleTypeDef hi2c1;

void sht21SoftReset(void){
	uint8_t cmd = SHT21_SOFT_RESET;
	HAL_I2C_Master_Transmit(&hi2c1, SHT21_SLAVE_ADDRESS, &cmd, 1, HAL_MAX_DELAY);
	return;
}

float sht21GetTemperature(void){
	uint8_t cmd = SHT21_ISSUE_TEMPERATURE_MEASURE;
	uint8_t reading[3];
	uint16_t readTemp;
	float temperature;
	//Issue a temperature measurement
	HAL_I2C_Master_Transmit(&hi2c1, SHT21_SLAVE_ADDRESS, &cmd, 1, HAL_MAX_DELAY);

	//Read the measurement and CRC bytes
	HAL_I2C_Master_Receive(&hi2c1, SHT21_SLAVE_ADDRESS, reading, 3, HAL_MAX_DELAY);

	//Build the sensor output St
	readTemp = (reading[0] << 8) | (reading[1] & 0xFC);				//Shift Most significantive byte and clear status bits of the Least significative byte

	//Do the conversion to temperature in float format
	temperature = -46.85 + 175.72 * (float) readTemp / 65536.0;

	//Return measurement
	return temperature;
}

float sht21GetRelativeHumidity(void){
	uint8_t cmd = SHT21_ISSUE_HUMIDITY_MEASURE;
	uint8_t reading[3];
	uint8_t readRelativeHumidity;
	float relativeHumidity;

	//Issue a relative humidity measurement
	HAL_I2C_Master_Transmit(&hi2c1, SHT21_SLAVE_ADDRESS, &cmd, 1, HAL_MAX_DELAY);

	//Read the measurement and CRC bytes
	HAL_I2C_Master_Receive(&hi2c1, SHT21_SLAVE_ADDRESS, reading, 3, HAL_MAX_DELAY);

	//Build the sensor output Srh
	readRelativeHumidity = reading[0];

	//Do the conversion to relative humidity in float format
	relativeHumidity = -6.0 + 125.0 * (float) readRelativeHumidity / 65536.0;

	//Return measurement
	return relativeHumidity;
}

void sht21ConfigResolution(void){

}





