#ifndef FS_INTERFACE_H
#define FS_INTERFACE_H
// ==========================[ Includes ]===============================
#include <stdint.h>
// ==========================[ Typedefs ]===============================
typedef enum{
	FS_OK = 0,
	FS_ERR_INIT,
	FS_ERR_MOUNT,
	FS_ERR_UNMOUNT,
	FS_ERR_OPEN,
	FS_ERR_CLOSE,
	FS_ERR_WRITE,
	FS_ERR_READ,
	FS_ERR_SD_NOT_MOUNTED,
	FS_FILE_NOT_FOUND,
	FS_ERR_UNKNOWN
}tFSResult;

typedef enum{
	FILE_MODE_READ = 0,
	FILE_MODE_WRITE,
	FILE_MODE_APPEND,
	FILE_MODE_CREATE_NEW,
	FILE_MODE_CREATE_ALWAYS,
	FILE_MODE_INVALID
}tFSOpenMode;
// =======================[ Public functions ]============================
tFSResult fsMountSdCard(void);
tFSResult fsUnmountSdCard(void);
tFSResult fsOpen(const char *path, tFSOpenMode mode);
tFSResult fsClose(void);
tFSResult fsRead(void *buffer, uint32_t bufferSize, uint32_t *bytesRead);
tFSResult fsWrite(const void *buffer, uint32_t bufferSize, uint32_t *bytesWritten);
tFSResult fsCheckIfFileExists(const char *filename);
#endif //FS_INTERFACE_H
