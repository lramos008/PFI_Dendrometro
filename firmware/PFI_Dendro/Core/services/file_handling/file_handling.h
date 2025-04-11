#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H
// ==========================[ Includes ]===============================
#include <string.h>

// ==========================[ Typedefs ]===============================
typedef enum{
	FILE_OK = 0,
	FILE_ERROR_MOUNT,
	FILE_ERROR_UNMOUNT,
	FILE_ERROR_OPEN,
	FILE_ERROR_CLOSE,
	FILE_ERROR_WRITE,
	FILE_ERROR_READ,
	FILE_ERROR_NOT_FOUND,
	FILE_ERROR_INVALID_PATH,
	FILE_ERROR_NULL_POINTER
}tFileStatus;

#endif //FILE_HANDLING_H
