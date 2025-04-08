// ==============================[ Includes ]===================================
#include "../../services/environment_measure/environment_data.h"
// ==========================[ Public Functions ]===============================
void environmentGetTempAndHR(sEnvironmentData *data){
	uint8_t hrBytes[2];
	uint8_t tempBytes[2];
	uint8_t checksum;
	uint16_t temp, hr;

	//Send start signal
	dht22Start();

	//Check if sensor is present
	if(dht22CheckResponse() == DHT22_OK){
		//Receive integral HR byte
		hrBytes[0] = dht22Read();

		//Receive decimal HR byte
		hrBytes[1] = dht22Read();

		//Receive integral temp byte
		tempBytes[0] = dht22Read();

		//Receive decimal temp byte
		tempBytes[1] = dht22Read();

		//Receive checksum
		checksum = dht22Read();

		//Check if the transmission went OK
		if(checksumControl(hrBytes, tempBytes, checksum) == DHT22_OK){
			//Convert relative humidity into a float number
			hr = (hrBytes[0] << 8) | hrBytes[1];
			data->relativeHumidity = (float) (hr / 10.0);

			//Convert temperature into a float number
			temp = (tempBytes[0] << 8) | tempBytes[1];
			data->temperature = (float) (temp / 10.0);

			//Set status to OK
			data->status = ENVIRONMENT_OK;
		}
		else{
			data->status = ERROR_HR_TEMP_CHECKSUM_FAILED;
		}
	}
	else{
		data->status = ERROR_HR_TEMP_SENSOR_NOT_PRESENT;
	}
	return;
}
