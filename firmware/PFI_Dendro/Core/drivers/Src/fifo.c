// ==========================[ Includes ]===============================
#include "fifo.h"
// ======================[ Public functions ]===============================
void FIFOInit(FIFO_t *fifo){
	fifo->head = 0;
	fifo->tail = 0;
	fifo->isFull = false;
	return;
}


bool FIFOIsEmpty(const FIFO_t *fifo){
	return (fifo->head == fifo->tail) && (!fifo->isFull);
}

bool FIFOIsFull(const FIFO_t *fifo){
	return fifo->isFull;
}

uint16_t FIFOGetCount(const FIFO_t *fifo){
	if(fifo->isFull) return FIFO_SIZE;
	return (fifo->head - fifo->tail) & (FIFO_SIZE - 1);
}
