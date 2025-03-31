#include "main.h"
#include "rtc_driver.h"

extern I2C_HandleTypeDef hi2c1;
//Limpiar A2F luego de cada interrupción, sino la línea queda en alto y no vuelve a bajo.

//Define address map from the RTC
#define RTC_SLAVE_ADDRESS				(0x68 << 1)
#define RTC_MEMORY_BASE_ADDRESS			0x00
#define RTC_DATETIME_BASE_ADDRESS		(RTC_MEMORY_BASE_ADDRESS + 0x0)
#define RTC_DATETIME_REGISTER_NUM		7


static uint8_t decimalToBCD(uint8_t decimal){
	return ((decimal / 10) << 4) | (decimal % 10);
}

static uint8_t BCDToDecimal(uint8_t bcd){
	return ((bcd >> 4) * 10) + (bcd & 0x0F);
}


/**
 * Configure and start the RTC for its use.
 *
 * @param none
 * @return none
 */
void RTCInit(void){
	//Enable periodic interrupt generation
	//If the corresponding Alarm Interrupt Enable ‘A1IE’ or ‘A2IE’ is also set to logic 1 and
	//the INTCN bit is set to logic 1, the alarm condition will activate the INT/SQW signal.


	//Set EOSC to para deteenr el oscilador (ahorrar batería hasta que arranque el dispositivo).

}

/**
 * Read date and time from the RTC.
 *
 * @param Pointer to a structure that will store the date and time read.
 * @return none
 */
void RTCGetDateAndTime(sDateAndTime *dateTime){
	uint8_t readData[RTC_DATETIME_REGISTER_NUM];

	//Read date and time from DS3231 memory
	HAL_I2C_Mem_Read(&hi2c1, RTC_SLAVE_ADDRESS, RTC_DATETIME_BASE_ADDRESS, I2C_MEMADD_SIZE_8BIT, readData, (uint16_t) RTC_DATETIME_REGISTER_NUM, HAL_MAX_DELAY);

	//Pass time data into the structure
	dateTime->time = (sTime) {.seconds = BCDToDecimal(readData[0]),
							  .minutes = BCDToDecimal(readData[1]),
							  .hours   = BCDToDecimal(readData[2]) & 0x3F};		//Ignore 12/~24 bit, keep hours only

	//Pass date data into the structure
	dateTime->date = (sDate) {.day   = BCDToDecimal(readData[3]),
							  .date  = BCDToDecimal(readData[4]),
							  .month = BCDToDecimal(readData[5] & 0x1F),		//Ignore century bit, keep month only
							  .year  = BCDToDecimal(readData[6])};
	return;
}

/**
 * Configure RTC with the desired date and time.
 *
 * @param Pointer to a structure that stores the date and time to be configured.
 * @return none
 */
void RTCSetDateAndTime(const sDateAndTime *dateTime){
	uint8_t dataToWrite[RTC_DATETIME_REGISTER_NUM];

	//Convert time into BCD
	dataToWrite[0] = decimalToBCD(dateTime->time.seconds);
	dataToWrite[1] = decimalToBCD(dateTime->time.minutes);
	dataToWrite[2] = decimalToBCD(dateTime->time.hours) & 0x3F;					//Ensure that 12/~24 bit is low to select 24 hours format

	//Convert date into BCD
	dataToWrite[3] = decimalToBCD(dateTime->date.day);
	dataToWrite[4] = decimalToBCD(dateTime->date.date);
	dataToWrite[5] = decimalToBCD(dateTime->date.month);
	dataToWrite[6] = decimalToBCD(dateTime->date.year);

	//Write date and time on DS3231's memory
	HAL_I2C_Mem_Write(&hi2c1, RTC_SLAVE_ADDRESS, RTC_DATETIME_BASE_ADDRESS, I2C_MEMADD_SIZE_8BIT, dataToWrite, (uint16_t) RTC_DATETIME_REGISTER_NUM, HAL_MAX_DELAY);
	return;
}
