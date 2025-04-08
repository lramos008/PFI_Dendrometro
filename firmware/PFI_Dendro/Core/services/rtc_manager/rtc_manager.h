#ifndef RTC_MANAGER_H
#define RTC_MANAGER_H

// ===================== [ INCLUDES ]==========================
#include "../../services/rtc_manager/date_and_time.h"
#include "../drivers/rtc/rtc_driver.h"

// ================= [ PUBLIC FUNCTIONS ]======================
void initializeRtc(void);
void readDateTime(sDateTime *dateTime);
void setDateTime(sDateTime *dateTime);
void enableAlarmInterrupt(void);
void disableAlarmInterrupt(void);
void clearAlarmInterruptFlag(void);
void scheduleAlarmInMinutes(uint32_t minutesFromNow);
#endif //RTC_MANAGER_H
