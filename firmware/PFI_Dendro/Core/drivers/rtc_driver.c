// =======================[ INCLUDES ]==========================
#include "rtc_driver.h"

// =======================[ TYPEDEFS ]==========================
typedef enum{
	RTC_OP_OK = 0,
	RTC_OP_FAILED
}tStatusRTC;

// ========================[ DEFINES ]===========================
#define DEBUG_TEST 1																//0: use module with real RTC, 1: use module with local test functions

#define RTC_SLAVE_ADDRESS				(0x68 << 1)									//RTC defines
#define RTC_MEMORY_BASE_ADDRESS			0x00
#define RTC_DATETIME_BASE_ADDRESS		(RTC_MEMORY_BASE_ADDRESS + 0x0)
#define RTC_DATETIME_REGISTER_NUM		7

uint8_t registers[RTC_DATETIME_REGISTER_NUM] = {0,0, 0x39 | (1 << 6), 0, 0, 0, 0};
// ====================[ PRIVATE FUNCTIONS ]======================
#if DEBUG_TEST == 0
extern I2C_HandleTypeDef hi2c1;

static tStatusRTC writeRTCRegisters(uint16_t slaveAddress, uint16_t registerAddress, uint8_t *dataToWrite, uint16_t dataSize){
	HAL_StatusTypeDef status;
	status = HAL_I2C_Mem_Write(&hi2c1, slaveAddress, registerAddress, I2C_MEMADD_SIZE_8BIT, dataToWrite, dataSize, HAL_MAX_DELAY);
	return (status == HAL_OK) ? RTC_OP_OK : RTC_OP_FAILED;
}



static tStatusRTC readRTCRegisters(uint16_t slaveAddress, uint16_t registerAddress, uint8_t *dataToRead, uint16_t dataSize){
	HAL_StatusTypeDef status;
	status = HAL_I2C_Mem_Read(&hi2c1, slaveAddress, registerAddress, I2C_MEMADD_SIZE_8BIT, dataToRead, dataSize, HAL_MAX_DELAY);
	return (status == HAL_OK) ? RTC_OP_OK : RTC_OP_FAILED;
}

#else
static tStatusRTC writeRTCRegisters(uint16_t slaveAddress, uint16_t registerAddress, uint8_t *dataToWrite, uint16_t dataSize){
	if(slaveAddress == RTC_SLAVE_ADDRESS && registerAddress == RTC_DATETIME_BASE_ADDRESS){
		for(uint16_t i = 0; i < dataSize; i++){
			registers[i] = dataToWrite[i];
		}
	}
	return RTC_OP_OK;
}




static tStatusRTC readRTCRegisters(uint16_t slaveAddress, uint16_t registerAddress, uint8_t *dataToRead, uint16_t dataSize){
	if(slaveAddress == RTC_SLAVE_ADDRESS && registerAddress == RTC_DATETIME_BASE_ADDRESS){
			for(uint16_t i = 0; i < dataSize; i++){
				dataToRead[i] = registers[i];
			}
		}
		return RTC_OP_OK;
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

static checkForValidDate(sDate *date){
	if(date->day > 7){

	}
	else if(date->date > 31 && date->date < 1){

	}
	else if(date->month > 12 && date->month < 1){

	}
	else if(date->year > 99){

	}

}

static checkForValidTime(sTime *time){
	if(time->seconds > 59){

	}
	else if(time->minutes > 59){

	}
	else if(time->hours > 23){

	}
}


// ====================[ PUBLIC FUNCTIONS ]======================

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
	uint8_t dataToRead[RTC_DATETIME_REGISTER_NUM];

	//Read date and time from DS3231 memory
	readRTCRegisters(RTC_SLAVE_ADDRESS, RTC_DATETIME_BASE_ADDRESS, dataToRead, RTC_DATETIME_REGISTER_NUM);

	//Pass time data into the structure
	dateTime->time = (sTime) {.seconds = BCDToDecimal(dataToRead[0]),
							  .minutes = BCDToDecimal(dataToRead[1]),
							  .hours   = BCDToDecimal(dataToRead[2] & 0x3F)};		//Ignore 12/~24 bit, keep hours only

	//Pass date data into the structure
	dateTime->date = (sDate) {.day   = BCDToDecimal(dataToRead[3]),
							  .date  = BCDToDecimal(dataToRead[4]),
							  .month = BCDToDecimal(dataToRead[5] & 0x1F),		//Ignore century bit, keep month only
							  .year  = BCDToDecimal(dataToRead[6])};
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
	//HAL_I2C_Mem_Write(&hi2c1, RTC_SLAVE_ADDRESS, RTC_DATETIME_BASE_ADDRESS, I2C_MEMADD_SIZE_8BIT, dataToWrite, (uint16_t) RTC_DATETIME_REGISTER_NUM, HAL_MAX_DELAY);
	writeRTCRegisters(RTC_SLAVE_ADDRESS, RTC_DATETIME_BASE_ADDRESS, dataToWrite, RTC_DATETIME_REGISTER_NUM);
	return;
}
