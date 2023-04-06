#include "MFSharedMem.h"

__declspec(dllexport) unsigned char *__stdcall MFShMemGetPointer(void){
	unsigned char	*shmAddress;
	HANDLE			shmFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "M2_SVTH_SHMEMORY");

	if (!shMemHandle && !shmFile)
	{
		shMemHandle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, SHARED_MEMORY_SIZE, "M2_SVTH_SHMEMORY");
		if(!shMemHandle){
			printf("Error: Could not create Shared Memory\n");
			return (NULL);
		}
		shmAddress = MapViewOfFile(shMemHandle, FILE_MAP_ALL_ACCESS, 0, 0, SHARED_MEMORY_SIZE);
		if(!shmAddress){
			printf("Error: Could not map Shared Memory\n");
			return (NULL);
		}
		memset(shmAddress, 0, SHARED_MEMORY_SIZE);
		UnmapViewOfFile(shmAddress);
		shmFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "M2_SVTH_SHMEMORY");
		if(!shmFile){
			printf("Error: Could not open Shared Memory\n");
			return (NULL);
		}
		threadMutex = CreateMutex(NULL, FALSE, NULL);
		processMutex = CreateMutex(NULL, FALSE, "M2_SVTH_MUTEX");
	}
	else if (!shMemHandle && shmFile && !processMutex)
		processMutex = OpenMutex(SYNCHRONIZE, FALSE, "M2_SVTH_MUTEX");
	shmAddress = MapViewOfFile(shmFile, FILE_MAP_ALL_ACCESS, 0, 0, SHARED_MEMORY_SIZE);
	if(!shmAddress){
			printf("Error: Could not map Shared Memory\n");
			return (NULL);
	}
	CloseHandle(shmFile);
	return (shmAddress);
}

__declspec(dllexport) void  __stdcall MFShMemRead (unsigned char *destBuffer, const unsigned int startOffset, const unsigned int numOfBytes){
	if (startOffset + numOfBytes > SHARED_MEMORY_SIZE)
	{
		printf("Error: Offset out of bounds\n");
		memset(destBuffer, 0, numOfBytes);
		return ;
	}
	unsigned char *sMem = MFShMemGetPointer();
	WaitForSingleObject(processMutex, INFINITE);
	WaitForSingleObject(threadMutex, INFINITE);

	if (!sMem){
		memset(destBuffer, 0, numOfBytes);
		return ;
	}
	memcpy(destBuffer, &sMem[startOffset], numOfBytes);
	UnmapViewOfFile(sMem);
	ReleaseMutex(threadMutex);
	ReleaseMutex(processMutex);
}

__declspec(dllexport) void  __stdcall MFShMemWrite(const unsigned char *sourceBuffer, const unsigned int startOffset, const unsigned int numOfBytes){
	if (startOffset + numOfBytes > SHARED_MEMORY_SIZE)
	{
		printf("Error: Offset out of bounds\n");
		return ;
	}
	unsigned char *sMem = MFShMemGetPointer();
	WaitForSingleObject(processMutex, INFINITE);
	WaitForSingleObject(threadMutex, INFINITE);
	
	if (!sMem)
		return ;
	memcpy(&sMem[startOffset], sourceBuffer, numOfBytes);
	UnmapViewOfFile(sMem);
	ReleaseMutex(threadMutex);
	ReleaseMutex(processMutex);
}

__declspec(dllexport) unsigned char __stdcall MFShMemDisableComm(void){
	return (0);
}

__declspec(dllexport) char  __stdcall MFShMemSend (const unsigned int startOffset, const unsigned int numOfBytes){
	(void)numOfBytes;
	(void)startOffset;
	return (0);
}