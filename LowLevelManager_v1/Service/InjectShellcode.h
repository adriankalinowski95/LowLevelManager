#pragma once
#include <Windows.h>

class InjectShellcode
{
public:
	static InjectShellcode& getInstance()
	{
		static InjectShellcode injectShellcode;
		return injectShellcode;
	}

public:
	InjectShellcode();
	InjectShellcode(const InjectShellcode&);
	~InjectShellcode();
	void setProcessHandle(HANDLE processHandle);
	HANDLE getProcessHandle();
	LPVOID mapBufferIntoProcess(LPBYTE buffer, SIZE_T buffer_size, DWORD protect);
	bool runShellcodeIntoNewThread(LPVOID remoteShellcodePointer);

private:
	HANDLE processHandle;

};

