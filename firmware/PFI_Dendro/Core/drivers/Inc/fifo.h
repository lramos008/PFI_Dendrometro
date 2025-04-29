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
	volatile bool isFull;
}fifoHandler_t;
// ======================[ Public functions ]===============================
void fifoInit(fifoHandler_t *f, uint8_t *buffer, uint16_t size);
void fifoReset(fifoHandler_t *f);
uint16_t fifoAvailable(fifoHandler_t *f);
uint16_t fifoFreeSpace(fifoHandler_t *f);
bool fifoIsEmpty(fifoHandler_t *f);
bool fifoIsFull(fifoHandler_t *f);
bool fifoPush(fifoHandler_t *f, uint8_t data);
bool fifoPushMulti(fifoHandler_t *f, const uint8_t *data, uint16_t bytesToPush);
bool fifoPop(fifoHandler_t *f, uint8_t *data);
uint16_t fifoPopMulti(fifoHandler_t *f, uint8_t *data, uint16_t bytesToPop);
bool fifoPeek(fifoHandler_t *f, uint8_t *data);
#endif //FIFO_H
