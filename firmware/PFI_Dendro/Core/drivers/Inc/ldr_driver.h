#ifndef LDR_DRIVER_H
#define LDR_DRIVER_H
// ==============================[ Includes ]==========================================
#include <stdint.h>

// ==============================[ Typedefs ]==========================================
typedef enum{
	LDR_DAY = 0,
	LDR_NIGHT
}LDRState_t;

// ======================[ Public functions prototypes ]===============================
void LDRInit(void);
void LDRSetThresholds(uint16_t dayThreshold, uint16_t nightThreshold);
LDRState_t LDRGetState(void);
#endif //LDR_DRIVER_H
