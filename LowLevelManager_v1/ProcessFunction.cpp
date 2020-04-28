#include "ProcessFunction.h"
#include "ProcessFunctionStackFrame.h"
#include "ProcessFunctionConvention.h"
#include "ProcessFunctionCaller.h"
#include "MnemonicsX64.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//const int baseIndexes[] = { MnemonicsX64::R_EBP,MnemonicsX64::R_RBP,MnemonicsX64::R_EDI,MnemonicsX64::R_RDI };
const int baseIndexes[] = { MnemonicsX64::R_EBP,MnemonicsX64::R_RBP};
const int stackIndexes[] = { MnemonicsX64::R_ESP,MnemonicsX64::R_RSP };



ProcessFunction::ProcessFunction(unsigned long long baseAddress, unsigned long long offsetStartAddress, unsigned long long offsetEndAddress,unsigned long long instructionCount)
	:baseAddress(baseAddress), offsetStartAddress(offsetStartAddress), offsetEndAddress(offsetEndAddress),instructionCount(instructionCount)
{

}

ProcessFunction::~ProcessFunction()
{
	/*
	if (this->instructions != NULL)
	{
		delete[] instructions;
	}
	*/
	while (!this->instructions->empty()) {
		delete this->instructions->back();
		this->instructions->pop_back();
	}
	
}

unsigned long long ProcessFunction::getBaseAddress()
{
	return this->baseAddress;
}

unsigned long long ProcessFunction::getOffsetStartAddress()
{
	return this->offsetStartAddress;
}

unsigned long long ProcessFunction::getOffsetEndAddress()
{
	return this->offsetEndAddress;
}

unsigned long long ProcessFunction::getInstructionCount()
{
	return this->instructionCount;
}




int ProcessFunction::getFunctionConvention()
{
//	_DecodedInst instAfterCall;
	AssemblerInstruction* assemblerInstruction = new AssemblerInstruction();
	ProcessFunctionConvention* processFunctionConvention = &(ProcessFunctionConvention::getInstance());
	int convention = processFunctionConvention->recognizeConvention(*this->instructions,*assemblerInstruction);
	delete assemblerInstruction;
	return convention;
}

void ProcessFunction::recognizeReturnedValue()
{
		
}

int ProcessFunction::recognizeBaseAddress()
{
	return 0;
}

int ProcessFunction::getBaseMnemonicInstructions()
{

	if (this->instructionCount <= 0)
	{
		return -1;
	}

	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());
	std::string tempMnemonic;
	std::string tempOperations;
	std::string pushMnemonic;
	std::string registerMnemonic;
	mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_PUSH, &pushMnemonic);


	for (int i = 0; i < this->instructionCount; i++)
	{
		//tempMnemonic.assign((const char*)this->instructions[i].mnemonic.p);
	  //	tempOperations.assign((const char*)this->instructions[i].operands.p);
		tempMnemonic.assign(this->instructions->at(i)->getMnemonic());
	  	tempOperations.assign(this->instructions->at(i)->getOperands());

		std::transform(tempMnemonic.begin(), tempMnemonic.end(), tempMnemonic.begin(), std::toupper);
		std::transform(tempOperations.begin(), tempOperations.end(), tempOperations.begin(), std::toupper);

		if (strcmp(tempMnemonic.c_str(), pushMnemonic.c_str()) == 0)
		{
			for (int j = 0; j < (sizeof(baseIndexes) / sizeof(const int)); j++)
			{
				mnemonicInstance->getRegisterByIndex(baseIndexes[j],&registerMnemonic);
				std::transform(registerMnemonic.begin(), registerMnemonic.end(), registerMnemonic.begin(), std::toupper);

				if (strcmp(registerMnemonic.c_str(), tempOperations.c_str()) == 0)
				{
					return baseIndexes[j];
				}
			}
		}

	}

	return -1;
}

int ProcessFunction::getStackMnemonic()
{
	if (this->instructionCount <= 0)
	{
		return -1;
	}


	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());
	std::string tempMnemonic;
	std::string tempOperations;
	std::string pushMnemonic;
	std::string registerMnemonic;
	mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_PUSH, &pushMnemonic);


	for (int i = 0; i < this->instructionCount; i++)
	{
		//tempMnemonic.assign((const char*)this->instructions[i].mnemonic.p);
	//	tempOperations.assign((const char*)this->instructions[i].operands.p);

		tempMnemonic.assign(this->instructions->at(i)->getMnemonic());
		tempOperations.assign(this->instructions->at(i)->getOperands());

		std::transform(tempMnemonic.begin(), tempMnemonic.end(), tempMnemonic.begin(), std::toupper);
		std::transform(tempOperations.begin(), tempOperations.end(), tempOperations.begin(), std::toupper);

			for (int j = 0; j < (sizeof(stackIndexes) / sizeof(const int)); j++)
			{
				mnemonicInstance->getRegisterByIndex(stackIndexes[j], &registerMnemonic);
				std::transform(registerMnemonic.begin(), registerMnemonic.end(), registerMnemonic.begin(), std::toupper);

				//size_t size = tempOperations.find(registerMnemonic);

				if (tempOperations.find(registerMnemonic) != std::string::npos)
				{
					return stackIndexes[j];
				}
			}


	}


	return -1;
}

std::vector<ProcessFunction::FunctionParamter*>* ProcessFunction::getFuncionParameters()
{
	int index = -1;
	//_DecodedInst* baseInstruction = NULL;
	//int baseRegister = this->getBaseMnemonicInstructions(baseInstruction, &index);

	AssemblerInstruction* assemblerInstruction;
	int baseRegister = this->getBaseMnemonicInstructions();
	if (baseRegister == -1)
		return NULL;

	int stackRegister = this->getStackMnemonic();
	if (stackRegister == -1)
		return NULL;

	std::string baseRegisterMnemonic;
	std::string stackRegisterMnemonic;

	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());
	mnemonicInstance->getRegisterByIndex(baseRegister, &baseRegisterMnemonic);
	mnemonicInstance->getRegisterByIndex(stackRegister, &stackRegisterMnemonic);


	std::vector<ProcessFunction::FunctionParamter*>* functionParameters = new std::vector<ProcessFunction::FunctionParamter*>;
	ProcessFunctionStackFrame* processFunctionStackFrameInstance = &(ProcessFunctionStackFrame::getInstance());

	int isCorrect = processFunctionStackFrameInstance->getFuncionParameters(*this->instructions,baseRegisterMnemonic.c_str(),
																			stackRegisterMnemonic.c_str(), functionParameters);

	if (isCorrect == 1)
		return functionParameters;

	return NULL;
}

int ProcessFunction::callFunction(std::vector<FunctionParamter*>* parameters)
{
	ProcessFunctionCaller* processFunctionCaller = &(ProcessFunctionCaller::getInstance());
	int success = processFunctionCaller->callFunction(parameters,*this->instructions);

	if (success == 1)
		return 1;
	else
		return 0;
}

