#pragma once
#include "ProcessFunction.h"
#include "Assembler/AssemblerInstruction.h"

class ProcessFunctionStackFrame
{
public:
	static ProcessFunctionStackFrame& getInstance()
	{
		static ProcessFunctionStackFrame instance;
		return instance;
	}

public:
	typedef enum
	{
		VERIABLE = 1, // moze to byc zmienna
		ARGUMENT = 2, // moze to byc argument
		REGISTER = 4, // moze to byc rejestr z ktorego pobieramy argument
		VALUE = 8,
		PUSH_BASE_REGISTER = 16,//wartosc przypisana do rejestru,
		PUSH_TO_STACK = 32
	};

public:
		typedef struct StackElementStruct
		{
			//_DecodedInst* instruction;
			AssemblerInstruction* instruction;
			unsigned long long address;
			int type;
			int registerIndex;
		}StackElement;
public:
	ProcessFunctionStackFrame();
	~ProcessFunctionStackFrame();
	int getFuncionParameters(std::vector <AssemblerInstruction*>& functionInstructions, std::string baseMnemonic, std::string stackMnemonic,
		std::vector<ProcessFunction::FunctionParamter*>* functionParameters);



private:
	StackElement* recognizeInstruction(AssemblerInstruction* instruction, std::string baseMnemonic, std::string stackMnemonic,
			unsigned long long* baseRegister, unsigned long long* stackRegister);
	ProcessFunction::FunctionParamter* recognizeStackElement(StackElement* stackElement);
	int stackoffset;


};

