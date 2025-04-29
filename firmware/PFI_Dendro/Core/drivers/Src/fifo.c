// ==========================[ Includes ]===============================
#include "fifo.h"
// ======================[ Public functions ]===============================
void fifoInit(fifoHandler_t *f, uint8_t *buffer, uint16_t size){
	f->buffer = buffer;
	f->size = size;
	f->head = 0;
	f->tail = 0;
	f->isFull = false;
	return;
}

void fifoReset(fifoHandler_t *f){
	f->head = 0;
	f->tail = 0;
	f->isFull = false;
}

uint16_t fifoAvailable(fifoHandler_t *f){
	if(f->isFull) return f->size;
	if(f->head >= f->tail) return f->head - f->tail;
	return f->size - f->tail + f->head;
}

uint16_t fifoFreeSpace(fifoHandler_t *f){
	return f->size - fifoAvailable(f);
}

bool fifoIsEmpty(fifoHandler_t *f){
	return (!f->isFull) && (f->head == f->tail);
}

bool fifoIsFull(fifoHandler_t *f){
	return f->isFull;
}

bool fifoPush(fifoHandler_t *f, uint8_t data){
	//Check if FIFO is full
	if(f->isFull) return false;						//FIFO buffer is full

	//Push data into the FIFO buffer
	f->buffer[f->head] = data;
	f->head = (f->head + 1) % f->size;

	//Check for full FIFO flag setting
	f->isFull = (f->head == f->tail);
	return true;
}

bool fifoPushMulti(fifoHandler_t *f, const uint8_t *data, uint16_t bytesToPush){
	//Check if size is equal to 0
	if(bytesToPush == 0) return true;						//Do nothing, no data to push

	//Check if there is enough space
	if(bytesToPush > fifoFreeSpace(f)){
		return false; 								//There isn't enough space
	}

	//Push the values into the FIFO buffer
	for(uint16_t i = 0; i < bytesToPush; i++){
		f->buffer[f->head] = data[i];
		f->head = (f->head + 1) % f->size;
	}

	//Check for full FIFO flag setting
	f->isFull = (f->head == f->tail);
	return true;
}

bool fifoPop(fifoHandler_t *f, uint8_t *data){
	//Check for empty FIFO
	if(fifoIsEmpty(f)) return false;				//Empty FIFO

	//Pop the next element
	*data = f->buffer[f->tail];
	f->tail = (f->tail + 1) % f->size;

	//Pop done, clear the full FIFO flag
	f->isFull = false;
	return true;
}

uint16_t fifoPopMulti(fifoHandler_t *f, uint8_t *data, uint16_t bytesToPop){
	uint16_t i = 0;

	//Size check to verify is isFull flag should be changed
	if(bytesToPop > 0 && !fifoIsEmpty(f)){
		f->isFull = false;							//Just by popping an element, FIFO is not full anymore.
	}

	while(i < bytesToPop && (!fifoIsEmpty(f))){
		//Pop the data
		data[i++] = f->buffer[f->tail];
		f->tail = (f->tail + 1) % f->size;
	}
	return i;
}

bool fifoPeek(fifoHandler_t *f, uint8_t *data){
	if(fifoIsEmpty(f)) return false;				//No data to peek

	//Get the next byte without popping it
	*data = f->buffer[f->tail];
	return true;
}





