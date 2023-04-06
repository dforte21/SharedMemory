#include "shMemory.h"

int main(){
	unsigned char in[16] = "TEST test 123!?";

	MFShMemWrite(in, 0x511A, sizeof(in));

	Sleep(4000);
	CloseHandle(shMemHandle);
	CloseHandle(threadMutex);
	CloseHandle(processMutex);
}