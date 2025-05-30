// ===============================[ Includes ]===================================
#include "../Inc/date_and_time.h"

// ==========================[ Private functions ]===============================

/**
 * Check if a year is leap year.
 *
 * @param year Year to check (must be the complete year, do not abbreviate).
 * @return 1 if it is leap year, 0 otherwise.
 */
static uint32_t dateTimeIsLeapYear(uint32_t year){
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

/**
 * Get the max number of days for a certain month on a certain year.
 *
 * @param month Specified month.
 * @param year  Specified year (do not abbreviate year).
 * @return 0 if an invalid month was entered, or the max number of days
 * 		   for that specific month and year otherwise.
 */
static uint32_t dateTimeDaysInMonth(uint32_t month, uint32_t year){
	const uint32_t daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	uint32_t maxDays;
	if(month < 1 || month > 12){
		maxDays = 0;					//Invalid month
	}
	//If the current month is February check for leap year
	else if(month == 2 && dateTimeIsLeapYear(year)){
		maxDays = 29;
	}
	else{
		maxDays = daysInMonth[month - 1];
	}
	return maxDays;
}

/**
 * Convert a date and time to a standard format. This functions is used
 * with the dateTimeAddSeconds, dateTimeAddMinutes and dateTimeAddHours
 * functions, so the add operation doesn't throw out of range values.
 *
 * @param dateTime Pointer to a sDateTime structure.
 * @return None.
 */
static void dateTimeNormalize(sDateTime *dateTime){
	uint32_t daysAdded;

	//Adjust seconds
	dateTime->minutes += dateTime->seconds / 60;
	dateTime->seconds %= 60;

	//Adjust minutes
	dateTime->hours += dateTime->minutes / 60;
	dateTime->minutes %= 60;

	//Adjust hours
	dateTime->date += dateTime->hours / 24;
	daysAdded = dateTime->hours / 24;
	dateTime->hours %= 24;

	//Adjust day of the week
	if(daysAdded > 0){
		dateTime->dayOfWeek = ((dateTime->dayOfWeek - 1 + daysAdded) % 7) + 1;		//Substract 1 to daoOfWeek in order to use modulus operation.
																					//Then add 1 to retrieve original number
	}

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

/**
 * Check if the entered date and time meet the requirements of the standard
 * date and time format.
 *
 * @param dateTime Pointer to a sDateTime structure.
 * @return DATETIME_OK for a valid date and time,
 * 		   DATETIME_INVALID_DATE if the entered date is incorrect,
 * 		   DATETIME_INVALID_TIME if the entered time is incorrect.
 */
tDateTimeStatus dateTimeisValid(sDateTime *dateTime){
	tDateTimeStatus status;
	//Check for valid date
	if(dateTime->dayOfWeek > 7 || dateTime->dayOfWeek < 1 ||
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

/**
 * Add specified seconds to a current date and time. In case the
 * total number of seconds exceeds the maximum value given by the
 * standard date and time format, the entire date and time will be
 * normalized to get the correct representation.
 *
 * @param dateTime Pointer to a sDateTime structure.
 * @param secondsToAdd Seconds to add to the current date and time.
 * @return None.
 */
void dateTimeAddSeconds(sDateTime *dateTime, uint32_t secondsToAdd){
	if(dateTime == NULL) return;
	dateTime->seconds += secondsToAdd;
	dateTimeNormalize(dateTime);
}

/**
 * Add specified minutes to a current date and time. In case the
 * total number of minutes exceeds the maximum value given by the
 * standard date and time format, the entire date and time will be
 * normalized to get the correct representation.
 *
 * @param dateTime Pointer to a sDateTime structure.
 * @param minutesToAdd Minutes to add to the current date and time.
 * @return None.
 */
void dateTimeAddMinutes(sDateTime *dateTime, uint32_t minutesToAdd){
	if(dateTime == NULL) return;
	dateTime->minutes += minutesToAdd;
	dateTimeNormalize(dateTime);
}

/**
 * Add specified hours to a current date and time. In case the
 * total number of hours exceeds the maximum value given by the
 * standard date and time format, the entire date and time will be
 * normalized to get the correct representation.
 *
 * @param dateTime Pointer to a sDateTime structure.
 * @param hoursToAdd Hours to add to the current date and time.
 * @return None.
 */
void dateTimeAddHours(sDateTime *dateTime, uint32_t hoursToAdd){
	if(dateTime == NULL) return;
	dateTime->hours += hoursToAdd;
	dateTimeNormalize(dateTime);
}




