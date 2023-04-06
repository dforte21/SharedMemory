#include "shMemory.h"

int main(){
	unsigned char out[16];
	out[15] = 0;

	MFShMemRead(out, 0x511A, sizeof(out) - 1);
	printf("read: %s\n", out);

	CloseHandle(shMemHandle);
	CloseHandle(threadMutex);
	CloseHandle(processMutex);
	Sleep(3000);
}