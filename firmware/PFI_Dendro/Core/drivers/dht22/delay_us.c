#include "../drivers/dht22/delay_us.h"
// =======================[ Extern variables ]==========================
extern TIM_HandleTypeDef htim1;
// =======================[ Public functions ]==========================
void delayMicro(uint16_t microseconds){
	__HAL_TIM_SET_COUNTER(&htim1, 0);							//Set timer compare to 0
	while(__HAL_TIM_GET_COUNTER(&htim1) < microseconds);		//Wait until the count is reached
}
