/*This RTC module uses the 24 hs per day format*/
// ===========================[ Includes ]===============================
#include "rtc_driver.h"

// ======================[ External variables ]==========================
extern I2C_HandleTypeDef hi2c1;
// ===========================[ Defines ]===============================
#define RTC_SLAVE_ADDRESS	   			(0x68 << 1)
#define RTC_MEMORY_BASE_ADDRESS			0x00
#define RTC_DATETIME_BASE_ADDRESS		RTC_MEMORY_BASE_ADDRESS
#define RTC_ALARM1_BASE_ADDRESS			(RTC_MEMORY_BASE_ADDRESS + 0x07)
#define RTC_ALARM2_BASE_ADDRESS			(RTC_MEMORY_BASE_ADDRESS + 0x0B)
#define RTC_CONTROL_REGISTER_ADDRESS	(RTC_MEMORY_BASE_ADDRESS + 0x0E)
#define RTC_STATUS_REGISTER_ADDRESS		(RTC_MEMORY_BASE_ADDRESS + 0x0F)

#define RTC_ENABLE_ALARM2_INTERRUPT		(1 << 1)
#define RTC_ENABLE_INT_OUTPUT			(1 << 2)
#define RTC_DISABLE_OSCILLATOR			(1 << 7)
#define RTC_CLEAR_ALARM2_INTERRUPT		~(1 << 1)
#define	RTC_SET_ALARM2_MASK_BIT			(1 << 7)
#define RTC_CLEAR_ALARM2_MASK_BIT		~(1 << 7)
#define RTC_SET_24HOURS_FORMAT			~(1 << 6)
#define RTC_SET_DYDT_BIT				(1 << 6)
#define RTC_CLEAR_DYDT_BIT				~(1 << 6)
#define RTC_DATETIME_REGISTERS 			7
#define RTC_ALARM2_REGISTERS			3
#define RTC_MAX_RETRIES				    10

// =======================[ Private functions ]==========================
/**
 * @brief Converts a decimal number to its BCD (Binary Coded Decimal) representation.
 *
 * This function takes an 8-bit decimal number and converts it to BCD format,
 * where each nibble represents a decimal digit.
 *
 * @param[in] decimal  Decimal value to convert (0–99).
 *
 * @return BCD-encoded representation of the decimal value.
 * @note This is a private function and is intended for internal use within the RTC driver.
 * 		 This function does not check if the value is constrained between 0-99, so you should
 * 		 do the checking by yourself.
 */

static uint8_t decimalToBCD(uint8_t decimal){
	return ((decimal / 10) << 4) | (decimal % 10);
}



/**
 * @brief Converts a BCD-encoded byte to its decimal equivalent.
 *
 * This function takes an 8-bit value encoded in Binary Coded Decimal (BCD)
 * format and converts it to the corresponding decimal value.
 *
 * @param[in] bcd  BCD-encoded byte (e.g., 0x25 represents decimal 25).
 *
 * @return Decimal representation of the BCD value.
 *
 * @note This is a private function and is intended for internal use within the RTC driver.
 * 		 This function does not check if the BCD number is a valid one, so you should check
 * 		 your implementation by yourself.
 */

static uint8_t BCDToDecimal(uint8_t bcd){
	return ((bcd >> 4) * 10) + (bcd & 0x0F);
}


/**
 * @brief Writes data to RTC registers over I2C.
 *
 * This function attempts to write a block of data to a specified register address
 * of the RTC device over the I2C bus. It performs multiple retries in case of failure.
 *
 * @param[in] slaveAddress     7-bit I2C address of the RTC device. It must be shifted 1 place to the left.
 * @param[in] registerAddress  Register address in the RTC to write to.
 * @param[in] dataToWrite      Pointer to the data buffer to be written.
 * @param[in] dataSize         Number of bytes to write.
 *
 * @return RTC_OK if the write was successful, RTC_ERROR_WRITE otherwise.
 *
 * @note This is a private function and is intended for internal use within the RTC driver.
 */
static tRtcStatus rtcWriteRegisters(uint16_t slaveAddress, uint16_t registerAddress, uint8_t *dataToWrite, uint16_t dataSize){
	HAL_StatusTypeDef status;
	uint8_t retries = 0;

	//Try to write on RTC registers
	do{
		status = HAL_I2C_Mem_Write(&hi2c1, slaveAddress, registerAddress, I2C_MEMADD_SIZE_8BIT, dataToWrite, dataSize, HAL_MAX_DELAY);
		retries++;
	}while(status != HAL_OK && retries < RTC_MAX_RETRIES);

	//Return writing status
	return (status == HAL_OK) ? RTC_OK : RTC_ERROR_WRITE;
}


/**
 * @brief Reads data from RTC registers over I2C.
 *
 * This function attempts to read a block of data starting from a specified register
 * address of the RTC device using the I2C bus. It performs multiple retries in case of failure.
 *
 * @param[in]  slaveAddress     7-bit I2C address of the RTC device. It must be shifted 1 place to the left.
 * @param[in]  registerAddress  Register address in the RTC to start reading from.
 * @param[out] dataToRead       Pointer to the buffer where read data will be stored.
 * @param[in]  dataSize         Number of bytes to read.
 *
 * @return RTC_OK if the read was successful, RTC_ERROR_READ otherwise.
 *
 * @note This is a private function and is intended for internal use within the RTC driver.
 */
static tRtcStatus rtcReadRegisters(uint16_t slaveAddress, uint16_t registerAddress, uint8_t *dataToRead, uint16_t dataSize){
	HAL_StatusTypeDef status;
	uint8_t retries = 0;
	do{
		status = HAL_I2C_Mem_Read(&hi2c1, slaveAddress, registerAddress, I2C_MEMADD_SIZE_8BIT, dataToRead, dataSize, HAL_MAX_DELAY);
		retries++;
	}while(status != HAL_OK && retries < RTC_MAX_RETRIES);

	return (status == HAL_OK) ? RTC_OK : RTC_ERROR_READ;
}



// =======================[ Public functions ]==========================
tRtcStatus rtcReadDateTime(sRtcDateTime *dateTime){
	tRtcStatus status;
	uint8_t rtcRegisters[RTC_DATETIME_REGISTERS];

	//Read date and time from DS3231 memory
	status = rtcReadRegisters(RTC_SLAVE_ADDRESS, RTC_DATETIME_BASE_ADDRESS, rtcRegisters, RTC_DATETIME_REGISTERS);


	if(status == RTC_OK){
		//Decode and pass time data into the structure
		dateTime->seconds = BCDToDecimal(rtcRegisters[0]);
		dateTime->minutes = BCDToDecimal(rtcRegisters[1]);
		dateTime->hours   = BCDToDecimal(rtcRegisters[2] & 0x3F);

		//Decode and pass date data into the structure
		dateTime->dayOfWeek = BCDToDecimal(rtcRegisters[3]);
		dateTime->date      = BCDToDecimal(rtcRegisters[4]);
		dateTime->month     = BCDToDecimal(rtcRegisters[5] & 0x1F);
		dateTime->year      = BCDToDecimal(rtcRegisters[6]);
	}

	//Return status of the operation
	return status;
}

tRtcStatus rtcWriteDateTime(const sRtcDateTime *dateTime){
	tRtcStatus status;
	uint8_t rtcRegisters[RTC_DATETIME_REGISTERS];

	//Encode time data in BCD format
	rtcRegisters[0] = decimalToBCD(dateTime->seconds);
	rtcRegisters[1] = decimalToBCD(dateTime->minutes);
	rtcRegisters[2] = decimalToBCD(dateTime->hours) & 0x3F;			//Ensure that 12/~24 bit is low to select 24 hours format

	//Encode date data
	rtcRegisters[3] = decimalToBCD(dateTime->dayOfWeek);
	rtcRegisters[4] = decimalToBCD(dateTime->date);
	rtcRegisters[5] = decimalToBCD(dateTime->month);
	rtcRegisters[6] = decimalToBCD(dateTime->year);

	//Write date and time on DS3231's memory
	status = rtcWriteRegisters(RTC_SLAVE_ADDRESS, RTC_DATETIME_BASE_ADDRESS, rtcRegisters, RTC_DATETIME_REGISTERS);

	//Return status of the operation
	return status;
}

tRtcStatus rtcSetAlarm2(tRtcAlarm2Mode mode, uint8_t minutes, uint8_t hours, uint8_t dyDt){
	tRtcStatus status;
	uint8_t alarm2Registers[RTC_ALARM2_REGISTERS] = {RTC_SET_ALARM2_MASK_BIT, RTC_SET_ALARM2_MASK_BIT, RTC_SET_ALARM2_MASK_BIT};
//	uint8_t checkRegisters[RTC_ALARM2_REGISTERS] = {0};
	//Decide which registers should be masked
	switch(mode){
	case RTC_ALARM2_ONCE_PER_MINUTE:
		//set by default
		break;
	case RTC_ALARM2_MINUTES_MATCH:
		//Unmask alarm2 mask bits
		alarm2Registers[0] &= RTC_CLEAR_ALARM2_MASK_BIT;
		break;
	case RTC_ALARM2_MINUTES_HOURS_MATCH:
		//Unmask alarm2 mask bits
		alarm2Registers[0] &= RTC_CLEAR_ALARM2_MASK_BIT;
		alarm2Registers[1] &= RTC_CLEAR_ALARM2_MASK_BIT;
		break;
	case RTC_ALARM2_MINUTES_HOURS_DAY_MATCH:
	case RTC_ALARM2_MINUTES_HOURS_DATE_MATCH:
		//Unmask alarm2 mask bits
		alarm2Registers[0] &= RTC_CLEAR_ALARM2_MASK_BIT;
		alarm2Registers[1] &= RTC_CLEAR_ALARM2_MASK_BIT;
		alarm2Registers[2] &= RTC_CLEAR_ALARM2_MASK_BIT;

		//Select day or date
		if(mode == RTC_ALARM2_MINUTES_HOURS_DATE_MATCH){
			alarm2Registers[2] &= RTC_CLEAR_DYDT_BIT;
		}
		else{
			alarm2Registers[2] |= RTC_SET_DYDT_BIT;
		}
		break;
	default:
		break;
	}

	//Select 24 hours format
	alarm2Registers[1] &= RTC_SET_24HOURS_FORMAT;

	//Encode alarm 2 time and date vaues into bcd format
	alarm2Registers[0] &= 0x80;								//Clear minutes bits
	alarm2Registers[1] &= 0xC0;								//Clear hours bits
	alarm2Registers[2] &= 0xC0;								//Clear date/day bits
	alarm2Registers[0] |= (decimalToBCD(minutes) & 0x7F);	//Ensure the BCD conversion has only the requiered number of bits
	alarm2Registers[1] |= (decimalToBCD(hours)   & 0x3F);
	alarm2Registers[2] |= (decimalToBCD(dyDt)    & 0x3F);

	//Write alarm2 registers
	status = rtcWriteRegisters(RTC_SLAVE_ADDRESS, RTC_ALARM2_BASE_ADDRESS, alarm2Registers, RTC_ALARM2_REGISTERS);

	return status;
}


tRtcStatus rtcSetAlarm2Interrupt(bool enable){
	tRtcStatus status;
	uint8_t controlRegister;


	//Read the control register
	status = rtcReadRegisters(RTC_SLAVE_ADDRESS, RTC_CONTROL_REGISTER_ADDRESS, &controlRegister, 1);
	if(status == RTC_OK){
		//Check if interrupt should be enabled or disabled
		if(enable){
			controlRegister |= RTC_ENABLE_ALARM2_INTERRUPT | RTC_ENABLE_INT_OUTPUT;
		}
		else{
			controlRegister &= ~(RTC_ENABLE_ALARM2_INTERRUPT | RTC_ENABLE_INT_OUTPUT);
		}

		//Write the control register
		status = rtcWriteRegisters(RTC_SLAVE_ADDRESS, RTC_CONTROL_REGISTER_ADDRESS, &controlRegister, 1);

	}

	//Return status of the operation
	return status;
}




tRtcStatus rtcClearAlarm2Flag(void){
	tRtcStatus status;
	uint8_t statusRegister;

	//Read the status register
	status = rtcReadRegisters(RTC_SLAVE_ADDRESS, RTC_STATUS_REGISTER_ADDRESS, &statusRegister, 1);
	if(status == RTC_OK){
		//Clear the A2F bit
		statusRegister &= RTC_CLEAR_ALARM2_INTERRUPT;

		//Write the status register bit 1 to clear the A2F
		status = rtcWriteRegisters(RTC_SLAVE_ADDRESS, RTC_STATUS_REGISTER_ADDRESS, &statusRegister, 1);

	}
	return status;
}




