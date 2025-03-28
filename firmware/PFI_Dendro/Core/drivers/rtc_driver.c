#include "main.h"
#include "rtc_driver.h"

//Define address map from the RTC
#define RTC_START_ADDRESS				0x00;
#define RTC_SECONDS_REGISTER			(RTC_START_ADDRESS + 0x00)
#define RTC_MINUTES_REGISTER			(RTC_START_ADDRESS + 0x01)
#define RTC_HOURS_REGISTER				(RTC_START_ADDRESS + 0x02)
#define RTC_DAY_REGISTER				(RTC_START_ADDRESS + 0x03)
#define RTC_DATE_REGISTER				(RTC_START_ADDRESS + 0x04)
#define RTC_MONTH_REGISTER				(RTC_START_ADDRESS + 0x05)
#define RTC_YEAR_REGISTER				(RTC_START_ADDRESS + 0x06)
#define RTC_ALARM1_SECONDS_REGISTER		(RTC_START_ADDRESS + 0x07)
#define RTC_ALARM1_MINUTES_REGISTER		(RTC_START_ADDRESS + 0x08)
#define RTC_ALARM1_HOURS_REGISTER		(RTC_START_ADDRESS + 0x09)
#define RTC_ALARM1_DATE_REGISTER		(RTC_START_ADDRESS + 0x0A)
#define RTC_ALARM2_MINUTES_REGISTER		(RTC_START_ADDRESS + 0x0B)
#define RTC_ALARM2_HOURS_REGISTER		(RTC_START_ADDRESS + 0x0C)
#define RTC_ALARM2_DATE_REGISTER		(RTC_START_ADDRESS + 0x0D)
#define RTC_CONTROL_REGISTER			(RTC_START_ADDRESS + 0x0E)
#define RTC_STATUS_REGISTER				(RTC_START_ADDRESS + 0x11)


/**
 * Configure and start the RTC for its use.
 *
 * @param none
 * @return none
 */
void RTCInit(void){
	//Configurar para tener formato de 24 horas (indicador AM / PM).

}

/**
 * Read date and time from the RTC.
 *
 * @param Pointer to a structure that will store the date and time read.
 * @return none
 */
void RTCGetDateAndTime(sDateAndTime *dateTime){

}

/**
 * Configure RTC with the desired date and time.
 *
 * @param Pointer to a structure that stores the date and time to be configured.
 * @return none
 */
void RTCSetDateAndTime(const sDateAndTime *dateTime){

}

/**
 * Stop RTC and free its ocuppied resources.
 *
 * @param none
 * @return none
 */
void RTCDeinit(void){

}
