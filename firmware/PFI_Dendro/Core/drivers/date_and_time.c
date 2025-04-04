// ===============================[ Includes ]===================================
#include "date_and_time.h"

// ===============================[ Defines ]====================================
#define DATETIME_MONTH_PER_YEAR 12

// ==========================[ Private functions ]===============================
static uint32_t dateTimeIsLeapYear(uint32_t year){
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

static uint32_t dateTimeDaysInMonth(uint32_t month, uint32_t year){
	const uint32_t daysInMonth[DATETIME_MONTH_PER_YEAR] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	uint32_t currentDay;
	if(month < 1 || month > 12){
		currentDay = 0;					//Invalid month
	}
	//If the current month is February check for leap year
	else if(month == 2 && dateTimeIsLeapYear(year)){
		currentDay = 29;
	}
	else{
		currentDay = daysInMonth[month - 1];
	}
	return currentDay;
}

static void dateTimeNormalize(sDateTime *dateTime){
	//Adjust seconds
	dateTime->minutes += dateTime->seconds / 60;
	dateTime->seconds %= 60;

	//Adjust minutes
	dateTime->hours += dateTime->minutes / 60;
	dateTime->minutes %= 60;

	//Adjust hours
	dateTime->date += dateTime->hours / 24;
	dateTime->hours %= 24;

	//Adjust months and years
	while(dateTime->date > dateTimeDaysInMonth(dateTime->month, 2000 + dateTime->year)){
		dateTime->date -= dateTimeDaysInMonth(dateTime->month, 2000 + dateTime->year);
		dateTime->month++;
		if(dateTime->month > 12){
			dateTime->month = 1;
			dateTime->year++;
		}
	}
	return;
}

// ==========================[ Public functions ]===============================

tDateTimeStatus isValidDateTime(sDateTime *dateTime){
	tDateTimeStatus status;
	//Check for valid date
	if(dateTime->day > 7 || dateTime->day < 1 ||
	   dateTime->date > dateTimeDaysInMonth(dateTime->month, 2000 + dateTime->year) ||
	   dateTime->date < 1 || dateTime->month > 12 || dateTime->month < 1 || dateTime->year > 99)
	{
		status = DATETIME_INVALID_DATE;
	}
	else if(dateTime->seconds > 59 || dateTime->minutes > 59 || dateTime->hours > 23){
		status = DATETIME_INVALID_TIME;
	}
	else{
		status = DATETIME_OK;
	}
	return status;
}

void dateTimeAddSeconds(sDateTime *dateTime, uint32_t secondsToAdd){
	if(dateTime == NULL) return;
	dateTime->seconds += secondsToAdd;
	dateTimeNormalize(dateTime);
}

void dateTimeAddMinutes(sDateTime *dateTime, uint32_t minutesToAdd){
	if(dateTime == NULL) return;
	dateTime->minutes += minutesToAdd;
	dateTimeNormalize(dateTime);
}

void dateTimeAddHours(sDateTime *dateTime, uint32_t hoursToAdd){
	if(dateTime == NULL) return;
	dateTime->hours += hoursToAdd;
	dateTimeNormalize(dateTime);
}




