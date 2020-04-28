#include "InjectShellcodeController.h"
#include "InjectShellcode.h"
#include "ProcessInfo.h"
#include "TextConverter.h"
#include "Assembler.h"
#include "stdio.h"



InjectShellcodeController::InjectShellcodeController()
{

}

InjectShellcodeController::~InjectShellcodeController()
{
	
}

void InjectShellcodeController::injectBytesShellcode(const char* shellcode)
{
	int lineSize = strlen(shellcode);
	BYTE* line = new BYTE[lineSize];
	int byteSize = 0;
	bool isCorrect = TextConverter::convertCStrToLPBYTE(shellcode, line, &byteSize);
	InjectShellcode* injectShellcode = &(InjectShellcode::getInstance());

	LPVOID address = injectShellcode->mapBufferIntoProcess(line, (SIZE_T)byteSize, PAGE_EXECUTE_READWRITE);

	if (address != NULL)
	{
		injectShellcode->runShellcodeIntoNewThread(address);
	}

	delete [] line;
	
	
}

bool InjectShellcodeController::injectAsmShellcode(const char* shellcode)
{

	int lineSize = strlen(shellcode);
	if (lineSize > 0)
	{

		uint8_t* asmBytes;
		int asmByteSize = 0;

		Assembler* assembler = &(Assembler::getInstance());
		ProcessInfo* processInformation = &(ProcessInfo::getInstance());
		int architecture = processInformation->recognizeArchitecture();

		if (architecture > 0)
		{
			asmByteSize = assembler->convertAsmToByte(std::string(shellcode), &asmBytes, architecture);
			if (asmByteSize > 0)
			{
				printf("\n");
				for (int i = 0; i < asmByteSize; i++)
				{
					printf("%x ", asmBytes[i]);
				}
				printf("\n");

				InjectShellcode* injectShellcode = &(InjectShellcode::getInstance());

				LPVOID address = injectShellcode->mapBufferIntoProcess(asmBytes, (SIZE_T)asmByteSize, PAGE_EXECUTE_READWRITE);

				if (address != NULL)
				{
					injectShellcode->runShellcodeIntoNewThread(address);
					return true;
				}
				else
					return false;

			}
			else
				return false;
		}
		else
			return false;

	}
	else
		return false;
}




