#ifndef RTC_DRIVER
#define RTC_DRIVER
#include "main.h"

// =======================[ ENUMS ]==========================
typedef enum{
	RTC_OK = 0,
	RTC_ERROR_WRITE_FAILED,
	RTC_ERROR_READ_FAILED,
	RTC_INVALID_DATE_FORMAT,
	RTC_INVALID_TIME_FORMAT
}tRtcStatus

// =====================[ STRUCTURES ]=======================





// =============== FUNCTION PROTOTYPES ==============
void RTCInit(void);
tRtcStatus RTCGetDateAndTime(sDateAndTime *dateTime);
tRtcStatus RTCSetDateAndTime(const sDateAndTime *dateTime);
tRtcStatus RTCConfigAlarm1(void);
tRtcStatus RTCConfigAlarm2(void);
#endif	// RTC_DRIVER
