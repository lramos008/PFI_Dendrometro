#include "rtc_manager.h"
#include "rtc_driver.h"

static void rtcToDateTimeFormat(sRtcDateTime *rtcDateTime, sDateTime *dateTime){
	dateTime->seconds   = (uint32_t) (rtcDateTime->seconds);
	dateTime->minutes   = (uint32_t) (rtcDateTime->minutes);
	dateTime->hours     = (uint32_t) (rtcDateTime->hours);
	dateTime->dayOfWeek = (uint32_t) (rtcDateTime->dayOfWeek);
	dateTime->date      = (uint32_t) (rtcDateTime->date);
	dateTime->month     = (uint32_t) (rtcDateTime->month);
	dateTime->year      = (uint32_t) (rtcDateTime->year);
	return;
}

void initializeRtc(void){
	disableAlarmInterrupt();
	clearAlarmInterruptFlag();
	return;
}

void setDateTime(sDateTime *dateTime){
	if(dateTimeisValid(dateTime) == DATETIME_OK){
		//Convert to the data type the rtc can handle
		const sRtcDateTime rtcDateTime = {.seconds   = (uint8_t) (dateTime->seconds),
										  .minutes   = (uint8_t) (dateTime->minutes),
										  .hours     = (uint8_t) (dateTime->hours),
										  .dayOfWeek = (uint8_t) (dateTime->dayOfWeek),
										  .date      = (uint8_t) (dateTime->date),
										  .month     = (uint8_t) (dateTime->month),
										  .year      = (uint8_t) (dateTime->year)		};

		//Write date and time information into the rtc
		rtcWriteDateTime(&rtcDateTime);
	}
	return;
}

void readDateTime(sDateTime *dateTime){
	sRtcDateTime rtcDateTime = {0};

	//Read date and time from the RTC
	rtcReadDateTime(&rtcDateTime);

	//Cast values to uint32_t
	rtcToDateTimeFormat(&rtcDateTime, dateTime);
	return;
}

void enableAlarmInterrupt(void){
	rtcSetAlarm2Interrupt(true);
}

void disableAlarmInterrupt(void){
	rtcSetAlarm2Interrupt(false);
}

void clearAlarmInterruptFlag(void){
	rtcClearAlarm2Flag();
}

void scheduleAlarmInMinutes(uint32_t minutesFromNow){
	sDateTime dateTime = {0};

	//Read current datetime
	readDateTime(&dateTime);

	//Add minutes
	dateTimeAddMinutes(&dateTime, minutesFromNow);

	//Convert again to rtc structure
	const sRtcDateTime rtcDateTime = {.seconds   = (uint8_t) (dateTime.seconds),
									  	   .minutes   = (uint8_t) (dateTime.minutes),
										   .hours     = (uint8_t) (dateTime.hours),
										   .dayOfWeek = (uint8_t) (dateTime.dayOfWeek),
										   .date      = (uint8_t) (dateTime.date),
										   .month     = (uint8_t) (dateTime.month),
										   .year      = (uint8_t) (dateTime.year)		};

	//Send new alarm to RTC
	rtcSetAlarm2(RTC_ALARM2_MINUTES_MATCH, rtcDateTime.minutes, rtcDateTime.hours, rtcDateTime.date);
	return;
}
