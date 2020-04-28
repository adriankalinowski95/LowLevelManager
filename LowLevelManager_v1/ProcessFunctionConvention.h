#pragma once
#include <Windows.h>
#include "ProcessInstructionReader.h"
#include "distorm.h"
#include <vector>

class ProcessFunctionConvention
{
public:
	enum FunctionConvention
	{
		CDECL_CONVENTION = 1,
		STDCALL_CONVENTION = 2,
		OTHER_CONVENTION = 4
	};	

public:
	static ProcessFunctionConvention& getInstance()
	{
		static ProcessFunctionConvention instance;
		return instance;
	}

public:
	ProcessFunctionConvention();
	~ProcessFunctionConvention();
	int recognizeConvention(std::vector<AssemblerInstruction*>& instructions, AssemblerInstruction& afterCallInstruction);
	//int recognizeConvention(AssemblerInstruction* instructions,int instructionsCount, AssemblerInstruction* afterCallInstruction)

private:
	int searchCallAddress(unsigned long long startFunctionAddress, std::vector<AssemblerInstruction*>& callInstructions);
	//int searchCallAddress(unsigned long long startFunctionAddress, AssemblerInstruction* callInstruction);


};

