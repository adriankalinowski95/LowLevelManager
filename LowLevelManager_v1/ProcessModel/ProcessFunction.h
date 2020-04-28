#pragma once
#include <Windows.h>
#include "distorm.h"
#include <string>
#include <vector>
#include "Assembler/AssemblerInstruction.h"


class ProcessFunction
{
public:
	enum ParameterType
	{
		STACK,
		REGISTER
	};
public:	static constexpr const char* parametTypeMnemonic[] = { "Stack","Register" };

public:
	typedef struct FunctionParameterStruct
	{
		float value;
		int size;
		int type;
		int registerIndex;
		int offset;
	}FunctionParamter;

public:
	ProcessFunction(unsigned long long baseAddress, unsigned long long offsetStartAddress, unsigned long long offsetEndAddress, unsigned long long instructionCount);
	~ProcessFunction();
	unsigned long long getBaseAddress();
	unsigned long long getOffsetStartAddress();
	unsigned long long getOffsetEndAddress();
	unsigned long long getInstructionCount();
	//_DecodedInst* instructions;
	std::vector<AssemblerInstruction*>* instructions;
	std::vector<FunctionParamter*>* getFuncionParameters();
	int getFunctionConvention();
	int callFunction(std::vector<FunctionParamter*>* parameters);

private:
	unsigned long long baseAddress;
	unsigned long long offsetStartAddress;
	unsigned long long offsetEndAddress;
	unsigned long long instructionCount;
	void recognizeReturnedValue(); //mozna dopisac
	int recognizeBaseAddress(); //do dodpisania
	int getBaseMnemonicInstructions();
	int getStackMnemonic();

};

