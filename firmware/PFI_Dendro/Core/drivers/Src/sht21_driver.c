/* This library is a driver for the SHT21 in hold master mode. This means
 * the SHT21 module forces the master into a wait state while measuring
 * temperature or relative humidity by pulling down the SCL line. By doing
 * so, the user doesn't need to implement delays on his own. For non blocking
 * applications, use the SHT21 in no hold master mode. */
// ==========================[ Includes ]===============================
#include "../Inc/sht21_driver.h"
// =======================[ Private Defines ]===========================
#define SHT21_SLAVE_ADDRESS					(0x40 << 1)
#define SHT21_TRIGGER_TEMPERATURE_MEASURE	0xE3							//Hold master mode
#define SHT21_TRIGGER_HUMIDITY_MEASURE		0xE5							//Hold master mode
#define SHT21_REBOOT_SENSOR					0xFE							//Soft reset takes 15 ms
#define SHT21_RESOLUTION_MODE1				(0 << 7) | (0 << 0)				//RH: 12 bits, T: 14 bits
#define SHT21_RESOLUTION_MODE2				(0 << 7) | (1 << 0)				//RH: 8 bits, T: 12 bits
#define SHT21_RESOLUTION_MODE3				(1 << 7) | (0 << 0)				//RH: 10 bits, T: 13 bits
#define SHT21_RESOLUTION_MODE4				(1 << 7) | (1 << 0)				//RH: 11 bits, T: 11 bits
#define SHT21_READ_USER_REGISTER			0xE7
#define SHT21_WRITE_USER_REGISTER			0xE6
#define SHT21_STARTUP_DELAY					15								//in ms

// =====================[ External variables ]==========================
extern I2C_HandleTypeDef hi2c1;
// ==========================[ Typedefs ]===============================
typedef float (*ConversionFunction)(uint16_t rawSignalOutput);

typedef enum{
	SHT21_MEASURE_HUMIDITY = 0,
	SHT21_MEASURE_TEMPERATURE
}tSht21Measurement;
// ===================== [ Private function ]===========================

static tSht21Status sht21ConfigResolution(uint8_t mode){
	uint8_t cmd = SHT21_READ_USER_REGISTER;
	HAL_StatusTypeDef status;
	uint8_t userRegister;
	uint8_t buffer[2];

	//Read the user register
	status = HAL_I2C_Master_Transmit(&hi2c1, SHT21_SLAVE_ADDRESS, &cmd, 1, HAL_MAX_DELAY);			//Send the read command
	if(status != HAL_OK) return SHT21_ERROR_I2C_TRANSMIT;

	status = HAL_I2C_Master_Receive(&hi2c1, SHT21_SLAVE_ADDRESS, &userRegister, 1, HAL_MAX_DELAY);
	if(status != HAL_OK) return SHT21_ERROR_I2C_RECEIVE;

	//Modify the resolution
	userRegister &= ~((1 << 0) | (1 << 7));			//Clean bit 0 and 7 (Measurement resolution)
	userRegister |= mode;

	//Write the user register
	buffer[0] = SHT21_WRITE_USER_REGISTER;			//Write command
	buffer[1] = userRegister;						//Register content to be written
	status = HAL_I2C_Master_Transmit(&hi2c1, SHT21_SLAVE_ADDRESS, buffer, 2, HAL_MAX_DELAY);
	if(status != HAL_OK) return SHT21_ERROR_I2C_TRANSMIT;

	//Resolution configuration is OK
	return SHT21_OK;
}

static tSht21Status sht21SendCommand(uint8_t cmd){
	HAL_StatusTypeDef status;
	status = HAL_I2C_Master_Transmit(&hi2c1, SHT21_SLAVE_ADDRESS, &cmd, 1, HAL_MAX_DELAY);
	return(status == HAL_OK) ? SHT21_OK : SHT21_ERROR_I2C_TRANSMIT;
}

static float temperatureConversion(uint16_t rawSignalOutput){
	return (-46.85 + 175.72 * (float) rawSignalOutput / 65536.0);
}

static float humidityConversion(uint16_t rawSignalOutput){
	return (-6.0 + 125.0 * (float) rawSignalOutput / 65536.0);
}

static tSht21Status sht21ReadMeasurement(tSht21Measurement measurementType, float *measurement){
	ConversionFunction doMeasurementConversion = NULL;
	HAL_StatusTypeDef status;
	uint16_t rawSignalOutput;
	uint8_t calculatedCRC;
	uint8_t buffer[3];
	uint8_t cmd;

	//Check measurement type
	switch(measurementType){
	case SHT21_MEASURE_HUMIDITY:
		cmd = SHT21_TRIGGER_HUMIDITY_MEASURE;
		doMeasurementConversion = humidityConversion;			//Dependency injection to select the function
		break;
	case SHT21_MEASURE_TEMPERATURE:
		cmd = SHT21_TRIGGER_TEMPERATURE_MEASURE;
		doMeasurementConversion = temperatureConversion;
		break;
	default:
		return SHT21_ERROR_UNKNOWN;
	}

	//Issue the selected measurement command
	status = HAL_I2C_Master_Transmit(&hi2c1, SHT21_SLAVE_ADDRESS, &cmd, 1, HAL_MAX_DELAY);
	if(status != HAL_OK) return SHT21_ERROR_I2C_TRANSMIT;

	//Read the sensor´s response
	status = HAL_I2C_Master_Receive(&hi2c1, SHT21_SLAVE_ADDRESS, buffer, 3, HAL_MAX_DELAY);
	if(status != HAL_OK) return SHT21_ERROR_I2C_RECEIVE;

	//Calculate CRC and compare
	calculatedCRC = calculateCRC(buffer, 2);
	if(buffer[2] != calculatedCRC) return SHT21_ERROR_CRC;

	//Do the measurement conversion
	rawSignalOutput = (buffer[0] << 8) | (buffer[1] & ~(0x03));							//Clear status bits from the second byte received
																						//in order to calculate the relative humidity
	*measurement = doMeasurementConversion(rawSignalOutput);							//Save measurement conversion
	return SHT21_OK;
}

// ===================== [ Public functions ]===========================
tSht21Status sht21Init(void){
	//Obs: Heater is turned off when power on occurs or at soft reset by default
	tSht21Status status;
	HAL_Delay(SHT21_STARTUP_DELAY);														//Wait start up time
	status = sht21ConfigResolution(SHT21_RESOLUTION_MODE2);								//RH: 8 bits, T: 12 bits
	return status;
}

tSht21Status sht21GetRelativeHumidity(float *relativeHumidity){
	tSht21Status status;
	status = sht21ReadMeasurement(SHT21_MEASURE_HUMIDITY, relativeHumidity);
	return status;
}

tSht21Status sht21GetTemperature(float *temperature){
	tSht21Status status;
	status = sht21ReadMeasurement(SHT21_MEASURE_TEMPERATURE, temperature);
	return status;
}

tSht21Status sht21SoftReset(void){
	tSht21Status status;
	status = sht21SendCommand(SHT21_REBOOT_SENSOR);
	if(status == SHT21_OK) HAL_Delay(SHT21_STARTUP_DELAY);								//Wait until the SHT21 starts again
	return status;
}













