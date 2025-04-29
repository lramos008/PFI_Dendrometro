#ifndef FIFO_H
#define FIFO_H
// ==========================[ Includes ]===============================
#include <stdint.h>
#include <stdbool.h>
// ==========================[ Typedefs ]===============================
typedef struct{
	uint8_t *buffer;
	uint16_t size;
	volatile uint16_t head;
	volatile uint16_t tail;
}fifoHandler_t;
// ======================[ Public functions ]===============================
void fifoInit(fifoHandler_t *f, uint8_t *buffer, uint16_t size);
bool fifoPush(fifoHandler_t *f, uint8_t data);
bool fifoPushBuffer(fifoHandler_t *f, const uint8_t *data, uint16_t size);
bool fifoPop(fifoHandler_t *f, uint8_t *data);
bool fifoPopBuffer(fifoHandler_t *f, uint8_t *data);
bool fifoPeek(fifoHandler_t *f, uint8_t *data);
uint16_t fifoAvailable(fifoHandler_t *f);
bool fifoIsFull(fifoHandler_t *f);
#endif //FIFO_H
