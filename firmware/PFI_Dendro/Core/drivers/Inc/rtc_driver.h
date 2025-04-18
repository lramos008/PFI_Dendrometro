#ifndef RTC_DRIVER_H
#define RTC_DRIVER_H

// ===================== [ INCLUDES ]==========================
#include "main.h"
#include <stdbool.h>
// =======================[ ENUMS ]==========================
typedef enum{
	RTC_OK = 0,
	RTC_ERROR_WRITE,
	RTC_ERROR_READ
}tRtcStatus;

typedef enum{
	RTC_ALARM2_ONCE_PER_MINUTE = 0,
	RTC_ALARM2_MINUTES_MATCH,
	RTC_ALARM2_MINUTES_HOURS_MATCH,
	RTC_ALARM2_MINUTES_HOURS_DATE_MATCH,
	RTC_ALARM2_MINUTES_HOURS_DAY_MATCH
}tRtcAlarm2Mode;

// =====================[ STRUCTURES ]=======================
typedef struct{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t dayOfWeek;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}sRtcDateTime;

// =================[ FUNCTION PROTOTYPES ]==================
tRtcStatus rtcReadDateTime(sRtcDateTime *dateTime);
tRtcStatus rtcWriteDateTime(const sRtcDateTime *dateTime);
tRtcStatus rtcSetAlarm2(tRtcAlarm2Mode mode, uint8_t minutes, uint8_t hours, uint8_t dyDt);
tRtcStatus rtcSetAlarm2Interrupt(bool enable);
tRtcStatus rtcClearAlarm2Flag(void);
#endif	// RTC_DRIVER_H
