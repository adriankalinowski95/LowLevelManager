#include "PEWrite.h"
#include "stdio.h"

using namespace std;


PEWrite::PEWrite(HANDLE procHandle) :processHandle(procHandle)
{
	this->injectedDataVector = new vector<InjectedData>();

}

LPVOID PEWrite::mapBufferIntoProcess(LPBYTE buffer, SIZE_T buffer_size, DWORD protect)
{

	LPVOID remoteAddress = VirtualAllocEx(this->processHandle, NULL, buffer_size, MEM_COMMIT | MEM_RESERVE, protect);
	if (remoteAddress == NULL) {
		printf("Could not allocate memory in the remote process\n");
		return NULL;
	}
	if (!WriteProcessMemory(this->processHandle, remoteAddress, buffer, buffer_size, NULL)) {
		VirtualFreeEx(this->processHandle, remoteAddress, buffer_size, MEM_FREE);
		return NULL;
	}
	return remoteAddress;
}

vector<InjectedData>* PEWrite::getInjectedDataVector()
{
	return this->injectedDataVector;
}


