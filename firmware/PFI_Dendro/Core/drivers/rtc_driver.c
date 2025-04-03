// =======================[ INCLUDES ]==========================
#include "rtc_driver.h"

// ========================[ DEFINES ]===========================
#define DEBUG_TEST 0
#define RTC_SLAVE_ADDRESS				(0x68 << 1)									//RTC defines
#define RTC_MEMORY_BASE_ADDRESS			0x00
#define RTC_DATETIME_BASE_ADDRESS		(RTC_MEMORY_BASE_ADDRESS + 0x00)
#define RTC_ALARM1_BASE_ADDRESS			(RTC_MEMORY_BASE_ADDRESS + 0x07)
#define RTC_ALARM2_BASE_ADDRESS			(RTC_MEMORY_BASE_ADDRESS + 0x0B)
#define RTC_CONTROL_REGISTER_ADDRESS	(RTC_MEMORY_BASE_ADDRESS + 0x0E)
#define RTC_STATUS_REGISTER_ADDRESS		(RTC_MEMORY_BASE_ADDRESS + 0x0F)

#define RTC_TURN_ON_ALARM2				(1 << 1)
#define RTC_ENABLE_INTERRUPT_OUTPUT		(1 << 2)
#define RTC_DISABLE_OSCILLATOR			(1 << 7)
#define RTC_ENABLE_OSCILLATOR			~(1 << 7)
#define RTC_DATETIME_REGISTER_NUM		7
#define MAX_RETRIES						10

uint8_t registers[RTC_DATETIME_REGISTER_NUM] = {0};
// ====================[ PRIVATE FUNCTIONS ]======================
#if DEBUG_TEST == 0
extern I2C_HandleTypeDef hi2c1;

static tStatusRTC writeRTCRegisters(uint16_t slaveAddress, uint16_t registerAddress, uint8_t *dataToWrite, uint16_t dataSize){
	HAL_StatusTypeDef status;
	status = HAL_I2C_Mem_Write(&hi2c1, slaveAddress, registerAddress, I2C_MEMADD_SIZE_8BIT, dataToWrite, dataSize, HAL_MAX_DELAY);
	return (status == HAL_OK) ? RTC_OK : RTC_ERROR_WRITE_FAILED;
}



static tStatusRTC readRTCRegisters(uint16_t slaveAddress, uint16_t registerAddress, uint8_t *dataToRead, uint16_t dataSize){
	HAL_StatusTypeDef status;
	status = HAL_I2C_Mem_Read(&hi2c1, slaveAddress, registerAddress, I2C_MEMADD_SIZE_8BIT, dataToRead, dataSize, HAL_MAX_DELAY);
	return (status == HAL_OK) ? RTC_OK : RTC_ERROR_READ_FAILED;
}

#else
static tStatusRTC writeRTCRegisters(uint16_t slaveAddress, uint16_t registerAddress, uint8_t *dataToWrite, uint16_t dataSize){
	if(slaveAddress == RTC_SLAVE_ADDRESS && registerAddress == RTC_DATETIME_BASE_ADDRESS){
		for(uint16_t i = 0; i < dataSize; i++){
			registers[i] = dataToWrite[i];
		}
	}
	return RTC_OK;
}




static tStatusRTC readRTCRegisters(uint16_t slaveAddress, uint16_t registerAddress, uint8_t *dataToRead, uint16_t dataSize){
	if(slaveAddress == RTC_SLAVE_ADDRESS && registerAddress == RTC_DATETIME_BASE_ADDRESS){
			for(uint16_t i = 0; i < dataSize; i++){
				dataToRead[i] = registers[i];
			}
	}
	return RTC_OK;
}
#endif


/**
 * Convert a decimal number into its BCD representation
 *
 * @param Desired decimal number between 0 and 99.
 * @return BCD representation (4 bits per digit, 4 MSBs are tens, the other 4 bits are units).
 */
static uint8_t decimalToBCD(uint8_t decimal){
	return ((decimal / 10) << 4) | (decimal % 10);
}

/**
 * Convert a BCD representation into its corresponding decimal number.
 *
 * @param BCD representation (4 bits per digit, 4 MSBs are tens, the other 4 bits are units).
 * @return Resulting decimal number between 0 and 99.
 */
static uint8_t BCDToDecimal(uint8_t bcd){
	return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

/**
 * Check for a valid date format. It does a minimum check to ensure
 * compatibility with the format of the DS3231's registers. It does
 * not check for leap year or max days per month conditions.
 *
 * @param Pointer to a structure that contains the date.
 * @return RTC_OK if there is a valid date, RTC_INVALID_DATE_FORMAT otherwise.
 */
static tStatusRTC isValidDate(const sDate *date){
	tStatusRTC status = RTC_OK;
	if(date->day   > 7  || date->day   < 1 ||
	   date->date  > 31 || date->date  < 1 ||
	   date->month > 12 || date->month < 1 ||
	   date->year  > 99)
	{
		status = RTC_INVALID_DATE_FORMAT;
	}
	return status;
}


/**
 * Check for a valid time format. It does a minimum check to ensure
 * compatibility with the format of the DS3231's registers.
 *
 * @param Pointer to a structure that contains the time.
 * @return RTC_OK if there is a valid time, RTC_INVALID_TIME_FORMAT otherwise.
 */
static tStatusRTC isValidTime(const sTime *time){
	tStatusRTC status = RTC_OK;
	if(time->seconds > 59 ||
	   time->minutes > 59 ||
	   time->hours   > 23)
	{
		status = RTC_INVALID_TIME_FORMAT;
	}
	return status;
}

/**
 * Check for a valid date and time format. It does a minimum check to ensure
 * compatibility with the format of the DS3231's registers. It does not check
 * for leap year or max days per month conditions.
 *
 * @param Pointer to a structure that contains the date and time.
 * @return RTC_OK if there are a valid date and time, RTC_INVALID_DATE_FORMAT if
 *         there is an invalid date format, RTC_INVALID_TIME_FORMAT if there is
 *         an invalid time format.
 */
static tStatusRTC isValidDateTime(const sDateAndTime *dateTime){
	tStatusRTC status;

	//CHeck if date is valid
	status = isValidDate(&dateTime->date);
	if(status == RTC_OK){
		//Check if time is valid
		status = isValidTime(&dateTime->time);
	}
	//else invalid date or time format
	return status;
}


// ====================[ PUBLIC FUNCTIONS ]======================

/**
 * Configure RTC alarm 2 and interrupt. This function also stops
 * the oscillator (under battery condition) to lower power consumption.
 *
 * @param none
 * @return none
 */
void RTCInit(void){
	uint8_t auxRegister;
	//Enable alarm 2 interrupt
	//Configure ~INT/SQW pin as output for interrupt
	//Disable oscillator (with battery)
	auxRegister = RTC_TURN_ON_ALARM2 | RTC_ENABLE_INTERRUPT_OUTPUT | RTC_DISABLE_OSCILLATOR;
	writeRTCRegisters(RTC_SLAVE_ADDRESS, RTC_CONTROL_REGISTER_ADDRESS, &auxRegister, 1);
	return;
}


/**
 * Read date and time from the RTC.
 *
 * @param Pointer to a structure that will store the date and time read.
 * @return RTC_OK if the read operation was successful, RTC_ERROR_READ_FAILED
 * 		   if there was an error while reading the DS3231 registers.
 */
tStatusRTC RTCGetDateAndTime(sDateAndTime *dateTime){
	tStatusRTC status;
	uint8_t counter = 0;
	uint8_t dataToRead[RTC_DATETIME_REGISTER_NUM];

	//Try to read date and time from DS3231 memory
	do{
		status = readRTCRegisters(RTC_SLAVE_ADDRESS, RTC_DATETIME_BASE_ADDRESS, dataToRead, RTC_DATETIME_REGISTER_NUM);
		counter++;
	}while(status != RTC_OK || counter < MAX_RETRIES);

	if(status == RTC_OK){
		//Pass time data into the structure
		dateTime->time = (sTime) {.seconds = BCDToDecimal(dataToRead[0]),
								  .minutes = BCDToDecimal(dataToRead[1]),
								  .hours   = BCDToDecimal(dataToRead[2] & 0x3F)};		//Ignore 12/~24 bit, keep hours only

		//Pass date data into the structure
		dateTime->date = (sDate) {.day   = BCDToDecimal(dataToRead[3]),
								  .date  = BCDToDecimal(dataToRead[4]),
								  .month = BCDToDecimal(dataToRead[5] & 0x1F),		//Ignore century bit, keep month only
								  .year  = BCDToDecimal(dataToRead[6])};
	}
	//else read operation failed
	return status;
}


/**
 * Configure RTC with the desired date and time.
 *
 * @param Pointer to a structure that stores the date and time to be configured.
 * @return RTC_OK if the write operation was successful, RTC_ERROR_WRITE_FAILED
 * 		   if there was an error while writing the DS3231 registers,
 * 		   RTC_INVALID_DATE_FORMAT or RTC_INVALID_TIME_FORMAT if there is a format
 * 		   error on the date and time used.
 */
tStatusRTC RTCSetDateAndTime(const sDateAndTime *dateTime){
	tStatusRTC status;
	uint8_t counter = 0;
	uint8_t dataToWrite[RTC_DATETIME_REGISTER_NUM];

	status = isValidDateTime(dateTime);
	//Check if there is a valid time format
	if(status == RTC_OK){
		//Convert time into BCD
		dataToWrite[0] = decimalToBCD(dateTime->time.seconds);
		dataToWrite[1] = decimalToBCD(dateTime->time.minutes);
		dataToWrite[2] = decimalToBCD(dateTime->time.hours) & 0x3F;		//Ensure that 12/~24 bit is low to select 24 hours format

		//Convert date into BCD
		dataToWrite[3] = decimalToBCD(dateTime->date.day);
		dataToWrite[4] = decimalToBCD(dateTime->date.date);
		dataToWrite[5] = decimalToBCD(dateTime->date.month);
		dataToWrite[6] = decimalToBCD(dateTime->date.year);

		//Write date and time on DS3231's memory
		do{
			status = writeRTCRegisters(RTC_SLAVE_ADDRESS, RTC_DATETIME_BASE_ADDRESS, dataToWrite, RTC_DATETIME_REGISTER_NUM);
			counter++;
		}while(status != RTC_OK|| counter < MAX_RETRIES);
	}
	return status;
}

tStatusRTC configNextMinutesAlarm(sDateAndTime currentDateTime, uint8_t minutesUntilAlarm){
	uint8_t auxRegister;

}

void clearMinutesAlarm(void){

}
