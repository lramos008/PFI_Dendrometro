#ifndef RTC_DRIVER_H
#define RTC_DRIVER_H

// ===================== [ INCLUDES ]==========================
#include "main.h"
#include <stdbool.h>
// =======================[ ENUMS ]==========================
/**
 * @enum tRtcStatus
 * @brief States of the RTC operations.
 */
typedef enum{
	RTC_OK = 0,								/**<Successful operation.*/
	RTC_ERROR_WRITE,						/**<Error during writing operation on the RTC*/
	RTC_ERROR_READ							/**<Error during reading operation on the RTC*/
}tRtcStatus;



/**
 * @enum tRtcAlarm2Mode
 * @brief Alarm 2 trigger modes for the RTC.
 */
typedef enum{
	RTC_ALARM2_ONCE_PER_MINUTE = 0,			/**< Triggers once per minute (when seconds match 00). */
	RTC_ALARM2_MINUTES_MATCH,				/**< Triggers when minutes match. */
	RTC_ALARM2_MINUTES_HOURS_MATCH,			/**< Triggers when minutes and hours match. */
	RTC_ALARM2_MINUTES_HOURS_DATE_MATCH,	/**< Triggers when minutes, hours, and date match. */
	RTC_ALARM2_MINUTES_HOURS_DAY_MATCH		/**< Triggers when minutes, hours, and day of week match. */
}tRtcAlarm2Mode;

// =====================[ STRUCTURES ]=======================
/**
 * @brief Structure representing the date and time of the RTC. Every value is BCD encoded.
 */
typedef struct{
	uint8_t seconds;						/**< Seconds (0–59). */
	uint8_t minutes;						/**< Minutes (0–59). */
	uint8_t hours;							/**< Hours (0–23). */
	uint8_t dayOfWeek;						/**< Day of the week (1–7). */
	uint8_t date;							/**< Day of the month (1–31). */
	uint8_t month;							/**< Month (1–12). */
	uint8_t year;							/**< Year (0–99). */
}sRtcDateTime;

// =================[ FUNCTION PROTOTYPES ]==================
/**
 * @brief Reads the current date and time from the RTC (DS3231).
 *
 * This function reads the date and time registers from the RTC, decodes the BCD values,
 * and stores the decoded values into the provided `sRtcDateTime` structure.
 *
 * @param dateTime Pointer to the structure where the decoded date and time will be stored.
 *
 * @return tRtcStatus Returns RTC_OK if the read operation is successful,
 *         or an error status if the operation fails.
 */
tRtcStatus rtcReadDateTime(sRtcDateTime *dateTime);


/**
 * @brief Writes the specified date and time to the RTC (DS3231).
 *
 * This function encodes the provided date and time values in BCD format and writes them
 * to the RTC's date and time registers.
 *
 * @param dateTime Pointer to the structure containing the date and time to be written to the RTC.
 *
 * @return tRtcStatus Returns RTC_OK if the write operation is successful,
 *         or an error status if the operation fails.
 */
tRtcStatus rtcWriteDateTime(const sRtcDateTime *dateTime);


/**
 * @brief Configures RTC Alarm 2 with the specified mode, time, and date.
 *
 * This function sets up the RTC Alarm 2 with a specific mode, time, and date by encoding
 * the parameters into BCD format and writing them to the RTC's alarm 2 registers. The
 * alarm can be configured to trigger based on different conditions like matching minutes,
 * hours, date, or day.
 *
 * @param mode The mode of Alarm 2, determining the conditions for the alarm to trigger.
 *             See @ref tRtcAlarm2Mode for possible modes.
 * @param minutes The minutes value for Alarm 2 (0-59).
 * @param hours The hours value for Alarm 2 (0-23).
 * @param dyDt The day or date value for Alarm 2 (depends on the mode):
 *             - Day (1-7) if the mode is `RTC_ALARM2_MINUTES_HOURS_DAY_MATCH`.
 *             - Date (1-31) if the mode is `RTC_ALARM2_MINUTES_HOURS_DATE_MATCH`.
 *
 * @return tRtcStatus Returns RTC_OK if the operation is successful,
 *         or an error status if the operation fails.
 */
tRtcStatus rtcSetAlarm2(tRtcAlarm2Mode mode, uint8_t minutes, uint8_t hours, uint8_t dyDt);


/**
 * @brief Enables or disables the Alarm 2 interrupt on the RTC.
 *
 * This function modifies the RTC control register to either enable or disable the Alarm 2 interrupt
 * and the interrupt output. The interrupt can be triggered based on the previously configured Alarm 2 mode.
 *
 * @param enable If `true`, enables the Alarm 2 interrupt and output; if `false`, disables them.
 *
 * @return tRtcStatus Returns `RTC_OK` if the operation was successful,
 *         or an error status if the operation failed.
 */
tRtcStatus rtcSetAlarm2Interrupt(bool enable);



/**
 * @brief Clears the Alarm 2 interrupt flag in the RTC status register.
 *
 * This function reads the RTC status register, clears the Alarm 2 interrupt flag (A2F),
 * and writes the updated value back to the register. The A2F bit is set when an Alarm 2
 * interrupt occurs, and it needs to be cleared manually to reset the interrupt condition.
 *
 * @return tRtcStatus Returns `RTC_OK` if the operation was successful,
 *         or an error status if the operation failed.
 */
tRtcStatus rtcClearAlarm2Flag(void);
#endif	// RTC_DRIVER_H
