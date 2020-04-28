#pragma once
#include <Windows.h>
#include "distorm.h"


class PEReader
{
public:
	static PEReader& getInstance()
	{
		static PEReader peReader;
		return peReader;
	}

public:
	PEReader();
	PEReader(const PEReader&);
	~PEReader();
	void setProcessHandle(HANDLE processHandle);
	HANDLE getProcessHandle();
	bool readProcess(LPCVOID startAddress);
	unsigned long getProcessSize(LPCVOID startAddress);
	unsigned long getProcessInstructionsCount(LPCVOID startAddress);
	int getInstructionsByIndex(LPCVOID startAddress, _DecodedInst instructions[], unsigned long long startIndex, int instructionCount);
	int getInstructions(LPCVOID startAddress, _DecodedInst instructions[], int byteSize);
	unsigned long getInstructionIndex(LPCVOID startAddress, LPCVOID instructionAddress);
	
private:
	HANDLE processHandle;
	unsigned long processSize;
	
};

