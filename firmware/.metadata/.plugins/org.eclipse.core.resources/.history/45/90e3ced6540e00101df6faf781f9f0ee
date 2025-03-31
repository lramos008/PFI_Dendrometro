#ifndef RTC_DRIVER
#define RTC_DRIVER

//Structure declaration
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


//Define function prototypes
void RTCInit(void);
void RTCGetDateAndTime(sDateAndTime *dateTime);
void RTCSetDateAndTime(const sDateAndTime *dateTime);
void RTCDeinit(void);
#endif	// RTC_DRIVER
