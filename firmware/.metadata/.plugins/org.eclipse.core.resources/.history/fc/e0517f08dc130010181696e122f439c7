#ifndef DATE_AND_TIME_H
#define DATE_AND_TIME_H
#include <stdint.h>
#include <stddef.h>
// ==========================[ Typedefs ]===============================
typedef enum{
	DATETIME_OK = 0,
	DATETIME_INVALID_DATE,
	DATETIME_INVALID_TIME
}tDateTimeStatus;

// ==========================[ Structures ]===============================
typedef struct{
	uint32_t seconds;
	uint32_t minutes;
	uint32_t hours;
	uint32_t dayOfWeek;
	uint32_t date;
	uint32_t month;
	uint32_t year;
}sDateTime;

// =======================[ Public functions ]==========================
tDateTimeStatus dateTimeisValid(sDateTime *dateTime);
void dateTimeAddSeconds(sDateTime *dateTime, uint32_t seconds);
void dateTimeAddMinutes(sDateTime *dateTime, uint32_t minutes);
void dateTimeAddHours(sDateTime *dateTime, uint32_t hours);
#endif //DATE_AND_TIME_H
