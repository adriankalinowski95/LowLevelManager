#pragma once

#include <windows.h>
#include <vector>

#define MAX_PROCESS_NAME_LENGTH 255

struct ProcessStruct {

	WCHAR processName[MAX_PATH];
	DWORD processPID;
};


class Injector
{
	public:
		Injector();
		~Injector();
		HANDLE loadProcessByName(LPWSTR processName);
		HANDLE loadProcessByPID(DWORD processID);
		HANDLE getInjectedProcessHandle();
		LPWSTR getInjectedProcessName();
		bool getProcessList(std::vector<ProcessStruct> *processList);
		LPVOID mapBufferIntoProcess(HANDLE hProcess, LPBYTE buffer, SIZE_T buffer_size, DWORD protect = PAGE_EXECUTE_READWRITE);
		bool runShellcodeIntoNewThread(HANDLE hProcess, LPVOID remote_shellcode_ptr);

	private:
		HANDLE injectedProcessHandle;
		WCHAR injectedProcessName[MAX_PROCESS_NAME_LENGTH];

};

