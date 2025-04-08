#ifndef ENVIRONMENT_DATA_H
#define ENVIRONMENT_DATA_H
// ===========================[ Includes ]===============================
#include "../drivers/dht22/dht22_driver.h"
// ===========================[ Typedefs ]===============================
typedef enum{
	ENVIRONMENT_OK,
	ERROR_FAILED_HR_TEMP_MEASURE,
	ERROR_FAILED_LIGHT_MEASURE,
	ERROR_HR_TEMP_SENSOR_NOT_PRESENT,
	ERROR_LIGHT_SENSOR_NOT_PRESENT,
	ERROR_HR_TEMP_CHECKSUM_FAILED
}tEnvironmentStatus;
// ==========================[ Structures ]==============================
typedef struct{
	float relativeHumidity;
	float temperature;
	float lightLevel;
	tEnvironmentStatus status;
}sEnvironmentData;
// =======================[ Public functions ]===========================
void environmentGetTempAndHR(sEnvironmentData *data);
#endif //ENVIRONMENT_DATA_H
