#pragma once
#include <Windows.h>
#include <vector>


struct InjectedData
{
	BYTE* buffer;
	SIZE_T bufferSize;
	LPVOID address;
};

class PEWrite
{

public:
	PEWrite(HANDLE procHandle);
	~PEWrite();
	LPVOID mapBufferIntoProcess(LPBYTE buffer, SIZE_T buffer_size, DWORD protect);
	std::vector<InjectedData>* getInjectedDataVector();

private:
	HANDLE processHandle;
	std::vector<InjectedData>* injectedDataVector;
};

