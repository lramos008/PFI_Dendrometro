#ifndef RTC_DRIVER
#define RTC_DRIVER
#include "main.h"

// ==================== STRUCTURES ===================
typedef struct{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
} sTime;

typedef struct{
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;
} sDate;

typedef struct{
	sDate date;
	sTime time;
}sDateAndTime;


// =============== FUNCTION PROTOTYPES ==============
void RTCInit(void);
void RTCGetDateAndTime(sDateAndTime *dateTime);
void RTCSetDateAndTime(const sDateAndTime *dateTime);
#endif	// RTC_DRIVER
