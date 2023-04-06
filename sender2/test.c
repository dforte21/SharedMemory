#include "shMemory.h"

int main(){
	unsigned char in[16] = "123!? test TEST";

	MFShMemWrite(in, 0x0000, sizeof(in));

	Sleep(4000);
	CloseHandle(shMemHandle);
	CloseHandle(threadMutex);
	CloseHandle(processMutex);
}