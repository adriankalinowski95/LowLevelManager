#include "PEreader.h"
#include <stdint.h>
#include <stdio.h>

#define MAX_INSTRUCTIONS (2000)
#define BUFFER_SIZE 8000
#define PROCESS_SIZE_BUFFER 16000


PEReader::PEReader()
{
}

PEReader::PEReader(const PEReader&)
{

}

PEReader::~PEReader()
{
}

void PEReader::setProcessHandle(HANDLE processHandle)
{
	this->processHandle = processHandle;
}

HANDLE PEReader::getProcessHandle()
{
	return this->processHandle;
}

bool PEReader::readProcess(LPCVOID startAddress)
{
	BYTE buffer[BUFFER_SIZE];
	SIZE_T readedBytes;


	_DecodeResult res;
	_DecodedInst decodedInstructions[MAX_INSTRUCTIONS];
	unsigned int decodedInstructionsCount = 0, i;
	_OffsetType offset = BUFFER_SIZE;
	_DecodeType dt = Decode64Bits;


	unsigned long currentOffset = 0;

	while (ReadProcessMemory(this->processHandle, (LPCVOID)((DWORD_PTR)startAddress+ currentOffset), (LPVOID)buffer, sizeof(buffer), &readedBytes) != false)
	{
		decodedInstructionsCount = 0;
		res = distorm_decode64((DWORD_PTR)startAddress+ currentOffset, (const unsigned char*)buffer, readedBytes, dt, decodedInstructions, MAX_INSTRUCTIONS, &decodedInstructionsCount);
		if (res == DECRES_INPUTERR) 
		{
			printf("Input error, halting!");
			return false;
		}

		for (i = 0; i < decodedInstructionsCount - 1; i++)
		{
			if ((char)decodedInstructions[i].mnemonic.p[0] == 'C')
			{
			
				if (strcmp((char*)decodedInstructions[i].mnemonic.p, "CALL") == 0)
				{
					//printf("%s\n", (char*)decodedInstructions[i].mnemonic.p);
				}
			}
//			printf("%0*I64x (%02d) %-24s %s%s%s\n", dt != Decode64Bits ? 8 : 16, decodedInstructions[i].offset, decodedInstructions[i].size, (char*)decodedInstructions[i].instructionHex.p, (char*)decodedInstructions[i].mnemonic.p, decodedInstructions[i].operands.length != 0 ? " " : "", (char*)decodedInstructions[i].operands.p);
			
		}
		
		currentOffset = (unsigned long)(decodedInstructions[decodedInstructionsCount - 1].offset - ((DWORD_PTR)startAddress));
		printf("current offset : %d \n", currentOffset);
	}
	return true;
}

unsigned long PEReader::getProcessSize(LPCVOID startAddress)
{
	unsigned long currentOffset = 0;
	BYTE buffer[PROCESS_SIZE_BUFFER];
	SIZE_T readedBytes;
	while (ReadProcessMemory(this->processHandle, (LPCVOID)((DWORD_PTR)startAddress + currentOffset), (LPVOID)buffer, sizeof(buffer), &readedBytes) != false)
	{
		currentOffset += readedBytes;
	}

	this->processSize = currentOffset;

	return this->processSize;
}

unsigned long PEReader::getProcessInstructionsCount(LPCVOID startAddress)
{
	BYTE buffer[BUFFER_SIZE];
	SIZE_T readedBytes;


	_DecodeResult res;
	_DecodedInst decodedInstructions[MAX_INSTRUCTIONS];
	unsigned int decodedInstructionsCount = 0, i;
	_OffsetType offset = BUFFER_SIZE;
	_DecodeType dt = Decode64Bits;


	unsigned long long currentOffset = 0;

	unsigned long instructionsCount = 0;

	while (ReadProcessMemory(this->processHandle, (LPCVOID)((DWORD_PTR)startAddress + currentOffset), (LPVOID)buffer, sizeof(buffer), &readedBytes) != false)
	{
		decodedInstructionsCount = 0;
		res = distorm_decode64((DWORD_PTR)startAddress + currentOffset, (const unsigned char*)buffer, readedBytes, dt, decodedInstructions, MAX_INSTRUCTIONS, &decodedInstructionsCount);
		if (res == DECRES_INPUTERR)
		{
			printf("Input error, halting!");
			return false;
		}

		currentOffset = (unsigned long)(decodedInstructions[decodedInstructionsCount - 1].offset - ((DWORD_PTR)startAddress));
		printf("current offset : %d \n", currentOffset);

		instructionsCount += decodedInstructionsCount;
	}

	return instructionsCount;
}

int PEReader::getInstructionsByIndex(LPCVOID startAddress, _DecodedInst instructions[], unsigned long long startIndex,int instructionCount)
{	
	BYTE buffer[BUFFER_SIZE];
	SIZE_T readedBytes;

	_DecodeResult res;
	_DecodeType dt = Decode64Bits;
	_DecodedInst decodedInstructions[MAX_INSTRUCTIONS];

	unsigned int decodedInstructionsCount = 0;
	unsigned long long currentOffset = 0;
	unsigned long long instructionsCount = 0;
	unsigned long long instructionsReaded = 0;

	while (ReadProcessMemory(this->processHandle, (LPCVOID)((DWORD_PTR)startAddress + currentOffset), (LPVOID)buffer, sizeof(buffer), &readedBytes) != false)
	{
		decodedInstructionsCount = 0;
		res = distorm_decode64((DWORD_PTR)startAddress + currentOffset, (const unsigned char*)buffer, readedBytes, dt, decodedInstructions, MAX_INSTRUCTIONS, &decodedInstructionsCount);
		if (res == DECRES_INPUTERR)
		{
			printf("Input error, halting!");
			return false;
		}

		currentOffset = (unsigned long)(decodedInstructions[decodedInstructionsCount - 1].offset - ((DWORD_PTR)startAddress));

		if (startIndex >= instructionsCount && startIndex <= (instructionsCount + decodedInstructionsCount))
		{


			for (int i = 0; i < decodedInstructionsCount; i++)
			{
				if (instructionsReaded >= instructionCount)
				{
					break;
				}
				if ((i + instructionsCount) >= (startIndex) && (i + instructionsCount) <= (startIndex+ instructionCount))
				{
					memcpy(&instructions[instructionsReaded], &decodedInstructions[i], sizeof(_DecodedInst));
					instructionsReaded++;
				}
			}
			if (instructionsReaded >= instructionCount)
			{
				break;
			}
			/*
			if ((startIndex + instructionCount) <= (instructionsCount + decodedInstructionsCount))
			{
				int relativeStartIndex = startIndex - instructionsCount;
				for (int i = 0; i < instructionCount; i ++)
				{
					instructions[i] = instructions[relativeStartIndex + i];
					instructionsReaded++;
				}
				break;
			}
			else
			{

			}
			*/
		
		}

		instructionsCount += decodedInstructionsCount;
		
	}


	return instructionsReaded;
}

int PEReader::getInstructions(LPCVOID startAddress, _DecodedInst instructions[], int byteSize)
{

	BYTE buffer[BUFFER_SIZE];
	SIZE_T readedBytes;

	_DecodeResult res;
	_DecodeType dt = Decode64Bits;
		
	unsigned int decodedInstructionsCount = 0;
	unsigned long long currentOffset = 0;

	bool success = ReadProcessMemory(this->processHandle, (LPCVOID)((DWORD_PTR)startAddress), (LPVOID)buffer, byteSize, &readedBytes);

	if (success == false)
	{
		return -1;
	}
	
	res = distorm_decode64((DWORD_PTR)startAddress, (const unsigned char*)buffer, readedBytes, dt, instructions, MAX_INSTRUCTIONS, &decodedInstructionsCount);
			
	if (res == DECRES_INPUTERR)
	{
		return -1;
	}
	return decodedInstructionsCount;
}

unsigned long PEReader::getInstructionIndex(LPCVOID startAddress, LPCVOID instructionAddress)
{
	BYTE buffer[BUFFER_SIZE];
	SIZE_T readedBytes;


	_DecodeResult res;
	_DecodedInst decodedInstructions[MAX_INSTRUCTIONS];
	unsigned int decodedInstructionsCount = 0, i;
	_OffsetType offset = BUFFER_SIZE;
	_DecodeType dt = Decode64Bits;


	unsigned long currentOffset = 0;

	unsigned long long instructionsCount = 0;
	unsigned long long instructionIndex = 0;

	while (ReadProcessMemory(this->processHandle, (LPCVOID)((DWORD_PTR)startAddress + currentOffset), (LPVOID)buffer, sizeof(buffer), &readedBytes) != false)
	{
		decodedInstructionsCount = 0;
		res = distorm_decode64((DWORD_PTR)startAddress + currentOffset, (const unsigned char*)buffer, readedBytes, dt, decodedInstructions, MAX_INSTRUCTIONS, &decodedInstructionsCount);
		if (res == DECRES_INPUTERR)
		{
			printf("Input error, halting!");
			return false;
		}

		if(((DWORD_PTR)instructionAddress >= decodedInstructions[0].offset) && ((DWORD_PTR)instructionAddress <= decodedInstructions[decodedInstructionsCount - 1].offset))
		{
			for (int i = 0; i < decodedInstructionsCount; i++)
			{
				if (decodedInstructions[i].offset == (DWORD_PTR)instructionAddress)
				{
					instructionIndex = i + instructionsCount;
					break;
				}
			}
			if (instructionIndex != 0)
			{
				break;
			}
		}
		currentOffset = (unsigned long)(decodedInstructions[decodedInstructionsCount - 1].offset - ((DWORD_PTR)startAddress));
		instructionsCount += decodedInstructionsCount;

	}
	return instructionIndex;
}

