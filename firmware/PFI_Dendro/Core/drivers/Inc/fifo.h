#ifndef FIFO_H
#define FIFO_H
// ==========================[ Includes ]===============================
#include <stdint.h>
#include <stdbool.h>
// ===========================[ Defines ]===============================
#define FIFO_SIZE 8										//It should be power of 2
// ==========================[ Typedefs ]===============================
typedef struct{
	uint8_t buffer[FIFO_SIZE];
	uint16_t head;
	uint16_t tail;
	bool isFull;
}FIFO_t;
// ======================[ Public functions ]===============================
void FIFOInit(FIFO_t *fifo);

static inline bool FIFOPush(FIFO_t *fifo, uint8_t data){
	if(fifo->isFull) return false;							//Full FIFO

	//Push data
	fifo->buffer[fifo->head] = data;
	fifo->head = (fifo->head + 1) & (FIFO_SIZE - 1);		//Only with powers of 2. Atomic operation to prevent interruption.
	fifo->isFull = (fifo->head == fifo->tail);
	return true;
}

static inline bool FIFOPop(FIFO_t *fifo, uint8_t *data){
	if((fifo->head == fifo->tail) && (!fifo->isFull)){
		return false;										//Empty FIFO
	}

	//Pop data
	*data = fifo->buffer[fifo->tail];
	fifo->tail = (fifo->tail + 1) & (FIFO_SIZE - 1);
	fifo->isFull = false;
	return true;
}

bool FIFOIsEmpty(const FIFO_t *fifo);
bool FIFOIsFull(const FIFO_t *fifo);
uint16_t FIFOGetCount(const FIFO_t *fifo);
#endif //FIFO_H
