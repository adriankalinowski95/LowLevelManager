#include "ProcessFunctionCaller.h"
#include "ProcessFunctionConvention.h"
#include "Service/MnemonicsX64.h"
#include "Assembler/Assembler.h"
#include "Service/InjectShellcode.h"
#include "Service/ProcessInfo.h"

#include <iostream>

#define X64_STACK_OFFSET 8
#define X86_STACK_OFFSET 4
#define VERIABLE_STRING "veriable"
#define VERIABLE_DD ".dd"
///dodac zamiane quadra word! (double)

const int fixedPointIndexes[] = { MnemonicsX64::R_RCX,MnemonicsX64::R_RDX,MnemonicsX64::R_R8,MnemonicsX64::R_R9,MnemonicsX64::R_EAX,MnemonicsX64::R_ECX,MnemonicsX64::R_EDX,
								  MnemonicsX64::R_R8D,MnemonicsX64::R_R9D,MnemonicsX64::R_R8W,MnemonicsX64::R_R9W,MnemonicsX64::R_R8B,MnemonicsX64::R_R9B,
								  MnemonicsX64::R_CX,MnemonicsX64::R_CL,MnemonicsX64::R_DX,MnemonicsX64::R_DL,MnemonicsX64::R_AX,MnemonicsX64::R_AL };

const int floatPointIndexes[] = { MnemonicsX64::R_XMM0,MnemonicsX64::R_XMM1,MnemonicsX64::R_XMM2,MnemonicsX64::R_XMM3};

const int tempFixedPointRegisterIndex = MnemonicsX64::R_RCX;
const int tempFloatPointRegisterIndex = MnemonicsX64::R_XMM0;

template <std::size_t N>
bool findInArray(int number, const int(&array)[N]) {
	return std::find(std::begin(array), std::end(array), number) != std::end(array);
}

typedef union convertTypeUnion {
	float floatVeriable;
	double doubleVeriable;
	int intVeriable;
};



ProcessFunctionCaller::ProcessFunctionCaller()
{
	ProcessInfo* processInformation = &(ProcessInfo::getInstance());
	int architecture = processInformation->recognizeArchitecture();

	if (architecture == ProcessInfo::X86Arch)
		architectureOffset = X86_STACK_OFFSET;
	else if (architecture == ProcessInfo::X64Arch)
		architectureOffset = X64_STACK_OFFSET;
}

ProcessFunctionCaller::~ProcessFunctionCaller()
{

}



int ProcessFunctionCaller::callFunction(std::vector<ProcessFunction::FunctionParamter*>* parameters, std::vector<AssemblerInstruction*>& instructions)
{
	ProcessInfo* processInformation = &(ProcessInfo::getInstance());
	int architecture = processInformation->recognizeArchitecture();

	if (architecture == ProcessInfo::X86Arch)
	{
		architectureOffset = X86_STACK_OFFSET;
	}
	else if (architecture == ProcessInfo::X64Arch)
	{
		architectureOffset = X64_STACK_OFFSET;
	}


	std::string asmInstructions;

	asmInstructions = this->getInstructionsToCall(parameters, instructions);

	if (asmInstructions.length() > 0)
	{
		uint8_t* asmBytes;
		Assembler* assembler = &(Assembler::getInstance());
		int asmByteSize = 0;
		if (architecture == ProcessInfo::X86Arch)
			 asmByteSize = assembler->convertAsmToByte(asmInstructions, &asmBytes, Assembler::X86Arch);
		else if(architecture == ProcessInfo::X64Arch)
			 asmByteSize = assembler->convertAsmToByte(asmInstructions, &asmBytes, Assembler::X64Arch);

		if (asmByteSize > 0)
		{
			InjectShellcode* injectShellcode = &(InjectShellcode::getInstance());

			LPVOID address = injectShellcode->mapBufferIntoProcess(asmBytes, (SIZE_T)asmByteSize, PAGE_EXECUTE_READWRITE);

			if (address != NULL)
			{
				bool success = injectShellcode->runShellcodeIntoNewThread(address);
				if (success)
					return 1;
			}
		}
	}

	return 0;
}




std::string ProcessFunctionCaller::getInstructionsToCall(std::vector<ProcessFunction::FunctionParamter*>* parameters, std::vector<AssemblerInstruction*>& instructions)
{
	ProcessInfo* processInformation = &(ProcessInfo::getInstance());
	ProcessFunctionConvention* processFunctionConvention = &(ProcessFunctionConvention::getInstance());
	AssemblerInstruction* afterCallInstruction = new AssemblerInstruction();
	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());
	int convention = processFunctionConvention->recognizeConvention(instructions, *afterCallInstruction);

	if (convention <= 0) return std::string();

	int architecture = processInformation->recognizeArchitecture();

	std::string newInstructions;
	std::string asmInstructions;
	std::string assemblerVeriables;
	std::string stackRegister;
	std::string subMnemonic;
	std::string retMnemonic;
	std::string addMnemonic;
	int veriableCount = 0;
	int stackOffset = 0;

	mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_SUB, &subMnemonic);
	mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_ADD, &addMnemonic);
	std::vector<ProcessFunction::FunctionParamter*>stackParameters;
	std::vector<ProcessFunction::FunctionParamter*>registerParameters;

	if (architecture == ProcessInfo::X64Arch)
		mnemonicInstance->getRegisterByIndex(MnemonicsX64::R_RSP, &stackRegister);
	else if (architecture == ProcessInfo::X86Arch)
		mnemonicInstance->getRegisterByIndex(MnemonicsX64::R_ESP, &stackRegister);


	for (int i = 0; i < parameters->size(); i++)
	{
		if (parameters->at(i)->type == ProcessFunction::REGISTER)
		{
			registerParameters.push_back(parameters->at(i));
		}
		else if (parameters->at(i)->type == ProcessFunction::STACK)
		{
			stackParameters.push_back(parameters->at(i));
		}
	}

	//error!
	char hex_string_1[50];
	sprintf(hex_string_1, "0x%X", (int)((registerParameters.size() + 1) * architectureOffset));
	asmInstructions += subMnemonic + " " + stackRegister + " ," + std::string(hex_string_1) + '\n';

	///utworzenie instrukcji wrzucania parametrow przez stos
	for (int i = 0; i < stackParameters.size(); i++)
	{
		asmInstructions += putParamByStack(stackParameters.at(stackParameters.size() - i - 1), stackRegister,&stackOffset);
	}
	//utworzenie przesuniecia spowodowanego parametrami wrzucanymi przez rejestr
	if (registerParameters.size() > 0)
	{
		char hex_string[50];
		sprintf(hex_string, "0x%X", (int)(registerParameters.size() * architectureOffset));
		asmInstructions += subMnemonic + " " + stackRegister+ " ," + std::string(hex_string) + '\n';
	//	stackOffset += 8;
	}
	//utworzenie instrukcji wrzucania parametrow przez rejestr
	for (int i = 0; i < registerParameters.size(); i++)
	{
		asmInstructions += putParametersByRegister(registerParameters.at(i), assemblerVeriables,&veriableCount);
	}
	unsigned long long startFunctionAddress = instructions.at(0)->getOffset();

	asmInstructions += putCallInstructions(startFunctionAddress);

	asmInstructions += putFunctionEpilog(instructions,convention, stackOffset, registerParameters.size());


	asmInstructions += addMnemonic + " " + stackRegister + " ," + std::string(hex_string_1) + '\n';

	mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_RET, &retMnemonic);

	asmInstructions += retMnemonic + '\n';

	asmInstructions += assemblerVeriables;


	return asmInstructions;
}

std::string ProcessFunctionCaller::putParamByStack(const ProcessFunction::FunctionParamter* parameter, std::string stackRegister, int* stackOffset)
{

	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());

	std::string instructions;
	std::string registerMnemonic;
	std::string instructionMnemonic;
	mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_PUSH, &instructionMnemonic);


	if (parameter->type == ProcessFunction::ParameterType::STACK)
	{
		if (findInArray(parameter->registerIndex, fixedPointIndexes) == true)
		{
			char hex_string[50];
			sprintf(hex_string, "0x%X", (int)parameter->value);

			instructions = instructionMnemonic + " " + std::string(hex_string) + '\n';
			*stackOffset += architectureOffset;
			return instructions;
		}
		else if (findInArray(parameter->registerIndex, floatPointIndexes) == true)
		{
			char hex_string[50];
			convertTypeUnion convertTypeUnion;
			convertTypeUnion.floatVeriable = (float)parameter->value;
			sprintf(hex_string, "0x%X", convertTypeUnion.intVeriable);

			instructions = instructionMnemonic + " " + std::string(hex_string) + '\n';
			*stackOffset += architectureOffset;
			return instructions;
		}

	}

	return std::string();
}

std::string ProcessFunctionCaller::putParametersByRegister(const ProcessFunction::FunctionParamter* parameter, std::string& assemblerVeriables, int* veriableCount)
{
	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());
	std::string instructions;
	std::string registerMnemonic;
	std::string instructionMnemonic;

	mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_PUSH, &instructionMnemonic);
	

	if (parameter->type == ProcessFunction::ParameterType::REGISTER)
	{
		mnemonicInstance->getRegisterByIndex(parameter->registerIndex, &registerMnemonic);

		if (findInArray(parameter->registerIndex, fixedPointIndexes) == true)
		{
			mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_MOV, &instructionMnemonic);
			instructions += instructionMnemonic + " ";
			instructions += registerMnemonic;
			instructions += ", ";
			instructions += std::to_string((int)parameter->value) + '\n';
			return instructions;
		}
		else if (findInArray(parameter->registerIndex, floatPointIndexes) == true)
		{

			char hex_string[50];
			convertTypeUnion convertTypeUnion;
			convertTypeUnion.floatVeriable = (float)parameter->value;

			sprintf(hex_string, "0x%X", convertTypeUnion.intVeriable);
			mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_MOVSS, &instructionMnemonic);

			std::string veriable = VERIABLE_STRING + std::to_string(*veriableCount);
			instructions += instructionMnemonic + " "+ registerMnemonic + ", [" + veriable + "]" + '\n';
			
			assemblerVeriables += veriable + ":" + '\n' + VERIABLE_DD + " " + std::string(hex_string) + '\n';

			*veriableCount += 1;

			return instructions;
		}
	}

	return std::string();
}

std::string ProcessFunctionCaller::putCallInstructions(unsigned long long functionAddress)
{
	std::string instructions;
	std::string registerMnemonic;
	std::string instructionMnemonic;
	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());


	if (architectureOffset == X86_STACK_OFFSET)
	{
		mnemonicInstance->getRegisterByIndex(MnemonicsX64::R_EAX, &registerMnemonic);
		mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_MOV, &instructionMnemonic);
	}
	else if (architectureOffset == X64_STACK_OFFSET)
	{
		mnemonicInstance->getRegisterByIndex(MnemonicsX64::R_RAX, &registerMnemonic);
		mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_MOV, &instructionMnemonic);
	}

	char hex_string[50];
	sprintf(hex_string, "0x%I64X", functionAddress);

	instructions += instructionMnemonic + " " + registerMnemonic + ", " + hex_string + '\n';

	mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_CALL, &instructionMnemonic);

	instructions += instructionMnemonic + " " + registerMnemonic + '\n';


	return instructions;
}
std::string ProcessFunctionCaller::putFunctionEpilog(std::vector<AssemblerInstruction*>& instructions, int convention, int stackOffset, int paramByRegisterCount)
{

	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());

	std::string asmInstructions;
	std::string addInstruction;
	std::string stackRegister;

	mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_ADD, &addInstruction);

	if (architectureOffset == X64_STACK_OFFSET)
		mnemonicInstance->getRegisterByIndex(MnemonicsX64::R_RSP, &stackRegister);
	else if (architectureOffset == X86_STACK_OFFSET)
		mnemonicInstance->getRegisterByIndex(MnemonicsX64::R_ESP, &stackRegister);

	if (instructions.size() > 0)
	{
		if (convention == ProcessFunctionConvention::CDECL_CONVENTION)
		{
			char hex_string[50];
			sprintf(hex_string, "0x%X", stackOffset);
			asmInstructions = addInstruction + " " + stackRegister + " ," + hex_string + '\n';
			return asmInstructions;
		}
		if (convention == ProcessFunctionConvention::OTHER_CONVENTION)
		{
			char hex_string[50];
			sprintf(hex_string, "0x%X", stackOffset + paramByRegisterCount * architectureOffset);
			asmInstructions = addInstruction + " " + stackRegister+ " ," + hex_string + '\n';
			return asmInstructions;
		}
	}
	return std::string();
}
