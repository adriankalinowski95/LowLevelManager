#include "ProcessFunctionStackFrame.h"
#include "Service/ProcessInfo.h"
#include "Service/MnemonicsX64.h"
#include <vector>
#include <algorithm>

//dodac uniwersalna metode do analizy
#define ESP_START_ADDRESS 0xFFFFFFFF

#define RECOGNIZE_ERROR -1
#define RECOGNIZE_WITHOUT_STACK_ELEMENT 0
#define RECOGNIZE_OK 1

#define X64_STACK_OFFSET 8
#define X86_STACK_OFFSET 4

const int baseIndexes[] = { MnemonicsX64::R_EBP,MnemonicsX64::R_RBP,MnemonicsX64::R_EDI,MnemonicsX64::R_RDI };

const int stackIndexes[] = { MnemonicsX64::R_ESP,MnemonicsX64::R_RSP };

const int functionRecognizeIndexes[] = { MnemonicsX64::I_MOV,MnemonicsX64::I_PUSH,MnemonicsX64::I_POP,
										   MnemonicsX64::I_ADD,MnemonicsX64::I_SUB,MnemonicsX64::I_LEA };

/*
int recognizeMov(ProcessFunctionStackFrame::StackElement** stackElement, _DecodedInst* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset);
int recognizePush(ProcessFunctionStackFrame::StackElement** stackElement, _DecodedInst* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset);
int recognizePop(ProcessFunctionStackFrame::StackElement** stackElement, _DecodedInst* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset);
int recognizeAdd(ProcessFunctionStackFrame::StackElement** stackElement, _DecodedInst* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset);
int recognizeSub(ProcessFunctionStackFrame::StackElement** stackElement, _DecodedInst* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset);
int recognizeLea(ProcessFunctionStackFrame::StackElement** stackElement, _DecodedInst* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset);



int (*stackMnemonicsOperations[])(ProcessFunctionStackFrame::StackElement** stackElement, _DecodedInst* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister,int stackOffset) = { recognizeMov,recognizePush,recognizePop,recognizeAdd,recognizeSub,recognizeLea};
*/

int recognizeMov(ProcessFunctionStackFrame::StackElement** stackElement,AssemblerInstruction* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset);
int recognizePush(ProcessFunctionStackFrame::StackElement** stackElement,AssemblerInstruction* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset);
int recognizePop(ProcessFunctionStackFrame::StackElement** stackElement,AssemblerInstruction* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset);
int recognizeAdd(ProcessFunctionStackFrame::StackElement** stackElement,AssemblerInstruction* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset);
int recognizeSub(ProcessFunctionStackFrame::StackElement** stackElement,AssemblerInstruction* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset);
int recognizeLea(ProcessFunctionStackFrame::StackElement** stackElement,AssemblerInstruction* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset);
int recognizeOther(ProcessFunctionStackFrame::StackElement** stackElement, AssemblerInstruction* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset);



int (*stackMnemonicsOperations[])(ProcessFunctionStackFrame::StackElement** stackElement, AssemblerInstruction* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset) = { recognizeMov,recognizePush,recognizePop,recognizeAdd,recognizeSub,recognizeLea };


ProcessFunctionStackFrame::ProcessFunctionStackFrame()
{
	ProcessInfo* processInformation = &(ProcessInfo::getInstance());
	int architecture = processInformation->recognizeArchitecture();
	
	if (architecture == ProcessInfo::X86Arch)
		stackoffset = X86_STACK_OFFSET;
	else if (architecture == ProcessInfo::X64Arch)
		stackoffset = X64_STACK_OFFSET;
}

ProcessFunctionStackFrame::~ProcessFunctionStackFrame()
{

}

//int ProcessFunctionStackFrame::getFuncionParameters(_DecodedInst* functionInstructions, int functionInstructionsCount, std::string baseMnemonic, std::string stackMnemonic,
//													std::vector<ProcessFunction::FunctionParamter*>* functionParameters)
int ProcessFunctionStackFrame::getFuncionParameters(std::vector <AssemblerInstruction*>& functionInstructions, std::string baseMnemonic, std::string stackMnemonic,
	std::vector<ProcessFunction::FunctionParamter*>* functionParameters)
{
	ProcessInfo* processInformation = &(ProcessInfo::getInstance());
	int architecture = processInformation->recognizeArchitecture();

	if (architecture == ProcessInfo::X86Arch)
	{
		stackoffset = X86_STACK_OFFSET;
	}
	else if (architecture == ProcessInfo::X64Arch)
	{
		stackoffset = X64_STACK_OFFSET;
	}

	unsigned long long stackRegister = ESP_START_ADDRESS;
	unsigned long long baseRegister = 0;

	std::vector<StackElement* > stackVector;
	for (int i = 0; i < functionInstructions.size(); i++)
	{
		StackElement* stackElement = this->recognizeInstruction(functionInstructions.at(i), baseMnemonic, stackMnemonic,&baseRegister,&stackRegister);
		if (stackElement != nullptr )
		{
			stackVector.push_back(stackElement);
		}
	}

	if (baseRegister > 0)
	{
		
		std::vector<StackElement*> potentialArguments;

		bool stackElementRedundade = false;
		for (int i = 0; i < stackVector.size(); i++)
		{
			if (stackVector.at(i)->address > ESP_START_ADDRESS)
			{

				for (int j = 0; j < potentialArguments.size(); j++)
				{
					if (stackVector.at(i)->address == potentialArguments.at(j)->address)
					{
						stackElementRedundade = true;
						break;
					}
				}
				if (stackElementRedundade == false && (stackVector.at(i)->type & (ProcessFunctionStackFrame::ARGUMENT + ProcessFunctionStackFrame::VERIABLE)) > 0)
				{
					potentialArguments.push_back(stackVector.at(i));
				}
				else
				{
					stackElementRedundade = false;
				}
			}
		}
		if (potentialArguments.size() > 0)
		{

			for (int i = 0; i < potentialArguments.size(); i++)
			{

				ProcessFunction::FunctionParamter* argument = this->recognizeStackElement(potentialArguments.at(i));
				if (argument != nullptr)
				{
					functionParameters->push_back(argument);
					argument->offset =  potentialArguments.at(i)->address - ESP_START_ADDRESS;
				}
			}
		}

		return 1;

	}
	else
	{
		return 1;
	}



	return 0;
}

//ProcessFunctionStackFrame::StackElement* ProcessFunctionStackFrame::recognizeInstruction(_DecodedInst* instruction,std::string baseMnemonic,std::string stackMnemonic,
//																						unsigned long long* baseRegister,unsigned long long* stackRegister)
ProcessFunctionStackFrame::StackElement* ProcessFunctionStackFrame::recognizeInstruction(AssemblerInstruction* instruction,std::string baseMnemonic,std::string stackMnemonic,
																					unsigned long long* baseRegister,unsigned long long* stackRegister)
{

	
	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());

//	std::string tempMnemonic((const char*)instruction->mnemonic.p);
//	std::string tempOperands((const char*)instruction->operands.p);

	std::string tempMnemonic(instruction->getMnemonic());
	std::string tempOperands(instruction->getOperands());

	std::transform(tempMnemonic.begin(), tempMnemonic.end(), tempMnemonic.begin(), std::toupper);
	std::transform(tempOperands.begin(), tempOperands.end(), tempOperands.begin(), std::toupper);

	int recognizeInstruction = mnemonicInstance->getInstructionIndex(tempMnemonic);
	int stackInstruction = -1;

	if (recognizeInstruction == -1)
	{
		return nullptr;
	}

	std::string recognizedInstruction;
	
	int isRecognized = mnemonicInstance->getInstructionByIndex(recognizeInstruction,&recognizedInstruction);

	if (isRecognized == -1)
	{
		return nullptr;
	}

	std::string temp;

	for (int i = 0; i < (sizeof(functionRecognizeIndexes) / sizeof(int)); i++)
	{
		isRecognized = mnemonicInstance->getInstructionByIndex(functionRecognizeIndexes[i], &temp);
		if (isRecognized == -1)
		{
			return nullptr;
		}

		if (recognizedInstruction.find(temp) != std::string::npos)
		{
			stackInstruction = i;
			break;
		}
	}
	/*
	if (stackInstruction == -1)
	{
		return nullptr;
	}
	*/
	StackElement* newStackElement = NULL;
	int status = 0;
	if (stackInstruction == -1)
	{
		status = recognizeOther(&newStackElement, instruction, baseMnemonic, stackMnemonic, baseRegister, stackRegister, this->stackoffset);
	}else
	 status = stackMnemonicsOperations[stackInstruction](&newStackElement,instruction, baseMnemonic,stackMnemonic, baseRegister, stackRegister,this->stackoffset);
	
	if (status == RECOGNIZE_ERROR)
	{
		return nullptr;
	}
	if (status == RECOGNIZE_WITHOUT_STACK_ELEMENT)
	{
		return 0;
	}
	if (status == RECOGNIZE_OK)
	{
		return newStackElement;
	}
	
	return nullptr;
}

ProcessFunction::FunctionParamter* ProcessFunctionStackFrame::recognizeStackElement(StackElement* stackElement)
{
	ProcessFunction::FunctionParamter* functionParameter = new ProcessFunction::FunctionParamter;
	if((stackElement->type & PUSH_TO_STACK) == PUSH_TO_STACK)
	{

		functionParameter->type = ProcessFunction::REGISTER;
		//functionParameter->size = 8;
		functionParameter->size = stackoffset;
		functionParameter->value = (int)0;
		functionParameter->registerIndex = stackElement->registerIndex;
		
		return functionParameter;
	}
	else 	if ((stackElement->type & ARGUMENT) == ARGUMENT)
	{
		functionParameter->type = ProcessFunction::STACK;
		functionParameter->size = stackoffset;
		//functionParameter->size = 8;
		functionParameter->value = (int)0;
		functionParameter->registerIndex = stackElement->registerIndex;
		return functionParameter;
	}

	delete functionParameter;

	return nullptr;
}


//int recognizeMov(ProcessFunctionStackFrame::StackElement** stackElement, _DecodedInst* instruction, std::string baseMnemonic, std::string stackMnemonic,
//	unsigned long long* baseRegister, unsigned long long* stackRegister)
int recognizeMov(ProcessFunctionStackFrame::StackElement** stackElement, AssemblerInstruction* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset)
{
	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());
	MnemonicsX64::InstructionAnalyse* instructionAnalyse = mnemonicInstance->getInstructionAnalyze(instruction);


	int stackRegisterIndex = mnemonicInstance->getRegisterIndex(stackMnemonic);
	int baseRegisterIndex = mnemonicInstance->getRegisterIndex(baseMnemonic);


	if (instructionAnalyse->arguments.size() == 2)
	{
		if (MnemonicsX64::REGISTER_ADDRESS == instructionAnalyse->arguments[0]->type)
		{
			if (instructionAnalyse->arguments[1]->registerIndex == stackRegisterIndex && instructionAnalyse->arguments[1]->type == MnemonicsX64::REGISTER_VALUE) 
			{
				*stackElement = new ProcessFunctionStackFrame::StackElement;
				(*stackElement)->address = *stackRegister + instructionAnalyse->arguments[1]->offsetAddress;
				(*stackElement)->instruction = instruction;
				(*stackElement)->type = ProcessFunctionStackFrame::ARGUMENT + ProcessFunctionStackFrame::VERIABLE + ProcessFunctionStackFrame::REGISTER;
				(*stackElement)->registerIndex = instructionAnalyse->arguments[0]->registerIndex;

				return 1;
			}
			else if (instructionAnalyse->arguments[1]->registerIndex == baseRegisterIndex && instructionAnalyse->arguments[1]->type == MnemonicsX64::REGISTER_VALUE)
			{
				*stackElement = new ProcessFunctionStackFrame::StackElement;
				(*stackElement)->address = *baseRegister + instructionAnalyse->arguments[1]->offsetAddress;
				(*stackElement)->instruction = instruction;
				(*stackElement)->type = ProcessFunctionStackFrame::ARGUMENT + ProcessFunctionStackFrame::VERIABLE;
				(*stackElement)->registerIndex = instructionAnalyse->arguments[0]->registerIndex;

				return 1;
			}
			else if (instructionAnalyse->arguments[0]->registerIndex == baseRegisterIndex && instructionAnalyse->arguments[1]->registerIndex == stackRegisterIndex)
			{
				*baseRegister = *stackRegister;
				
				return 1;
			}
		}
		else if (MnemonicsX64::REGISTER_VALUE == instructionAnalyse->arguments[0]->type)
		{
			if (instructionAnalyse->arguments[0]->registerIndex == stackRegisterIndex)
			{
				*stackElement = new ProcessFunctionStackFrame::StackElement;
				(*stackElement)->address = *stackRegister + instructionAnalyse->arguments[0]->offsetAddress;
				(*stackElement)->instruction = instruction;
				(*stackElement)->type = ProcessFunctionStackFrame::ARGUMENT + ProcessFunctionStackFrame::VERIABLE + ProcessFunctionStackFrame::REGISTER + ProcessFunctionStackFrame::PUSH_TO_STACK;
				(*stackElement)->registerIndex = instructionAnalyse->arguments[1]->registerIndex;

				return 1;
			}
			
		}
		
		if (MnemonicsX64::VALUE == instructionAnalyse->arguments[1]->type)
		{

			if (MnemonicsX64::REGISTER_ADDRESS == instructionAnalyse->arguments[0]->type)
			{
				*stackElement = new ProcessFunctionStackFrame::StackElement;
				(*stackElement)->instruction = instruction;
				(*stackElement)->type = ProcessFunctionStackFrame::VALUE;
				(*stackElement)->registerIndex = instructionAnalyse->arguments[0]->registerIndex;
				(*stackElement)->address = 0;

				return 1;
			}
			else if (MnemonicsX64::REGISTER_VALUE == instructionAnalyse->arguments[0]->type)
			{
				if (instructionAnalyse->arguments[0]->registerIndex == stackRegisterIndex)
				{
					*stackElement = new ProcessFunctionStackFrame::StackElement;
					(*stackElement)->address = *stackRegister + instructionAnalyse->arguments[0]->offsetAddress;
					(*stackElement)->instruction = instruction;
					(*stackElement)->type = ProcessFunctionStackFrame::ARGUMENT + ProcessFunctionStackFrame::VERIABLE + ProcessFunctionStackFrame::VALUE;
					(*stackElement)->registerIndex = instructionAnalyse->arguments[0]->registerIndex;

					return 1;
				}
				else if (instructionAnalyse->arguments[0]->registerIndex == baseRegisterIndex)
				{
					*stackElement = new ProcessFunctionStackFrame::StackElement;
					(*stackElement)->address = *baseRegister + instructionAnalyse->arguments[0]->offsetAddress;
					(*stackElement)->instruction = instruction;
					(*stackElement)->type = ProcessFunctionStackFrame::ARGUMENT + ProcessFunctionStackFrame::VERIABLE + ProcessFunctionStackFrame::VALUE;
					(*stackElement)->registerIndex = instructionAnalyse->arguments[0]->registerIndex;

					return 1;
				}
			}

		}



	}


	return 0;
}

//int recognizePush(ProcessFunctionStackFrame::StackElement** stackElement, _DecodedInst* instruction, std::string baseMnemonic, std::string stackMnemonic,
//	unsigned long long* baseRegister, unsigned long long* stackRegister,int stackOffset)
int recognizePush(ProcessFunctionStackFrame::StackElement** stackElement, AssemblerInstruction* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset)
{
	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());
	MnemonicsX64::InstructionAnalyse* instructionAnalyse = mnemonicInstance->getInstructionAnalyze(instruction);


	int stackRegisterIndex = mnemonicInstance->getRegisterIndex(stackMnemonic);
	int baseRegisterIndex = mnemonicInstance->getRegisterIndex(baseMnemonic);


	if (instructionAnalyse->arguments.size() == 1)
	{
		*stackRegister -= stackOffset;
		if (instructionAnalyse->arguments[0]->registerIndex == baseRegisterIndex)
		{
			*stackElement = new ProcessFunctionStackFrame::StackElement;
			(*stackElement)->address = *stackRegister;
			(*stackElement)->instruction = instruction;
			(*stackElement)->type = ProcessFunctionStackFrame::PUSH_BASE_REGISTER;
			(*stackElement)->registerIndex = instructionAnalyse->arguments[0]->registerIndex;
		}
		
		return 1;
	}
	return 0;
}

//int recognizeAdd(ProcessFunctionStackFrame::StackElement** stackElement, _DecodedInst* instruction, std::string baseMnemonic, std::string stackMnemonic,
//	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset)
int recognizeAdd(ProcessFunctionStackFrame::StackElement** stackElement, AssemblerInstruction* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset)
{
	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());
	MnemonicsX64::InstructionAnalyse* instructionAnalyse = mnemonicInstance->getInstructionAnalyze(instruction);


	int stackRegisterIndex = mnemonicInstance->getRegisterIndex(stackMnemonic);
	int baseRegisterIndex = mnemonicInstance->getRegisterIndex(baseMnemonic);


	if (instructionAnalyse->arguments.size() == 2)
	{
		if (MnemonicsX64::REGISTER_ADDRESS == instructionAnalyse->arguments[0]->type && instructionAnalyse->arguments[0]->registerIndex == stackRegisterIndex
			&& MnemonicsX64::VALUE == instructionAnalyse->arguments[1]->type)
		{
			*stackRegister += instructionAnalyse->arguments[1]->value;
			return 1;
		}
		else if (instructionAnalyse->arguments[1]->registerIndex == baseRegisterIndex && instructionAnalyse->arguments[1]->type == MnemonicsX64::REGISTER_VALUE)
		{
			*stackElement = new ProcessFunctionStackFrame::StackElement;
			(*stackElement)->address = *baseRegister + instructionAnalyse->arguments[1]->offsetAddress;
			(*stackElement)->instruction = instruction;
			(*stackElement)->type = ProcessFunctionStackFrame::ARGUMENT + ProcessFunctionStackFrame::VERIABLE;
			(*stackElement)->registerIndex = instructionAnalyse->arguments[0]->registerIndex;

			return 1;
		}


	}

	return 0;
}
//AssemblerInstruction
//int recognizeSub(ProcessFunctionStackFrame::StackElement** stackElement, _DecodedInst* instruction, std::string baseMnemonic, std::string stackMnemonic,
//	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset)
int recognizeSub(ProcessFunctionStackFrame::StackElement** stackElement, AssemblerInstruction* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset)
{
	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());
	MnemonicsX64::InstructionAnalyse* instructionAnalyse = mnemonicInstance->getInstructionAnalyze(instruction);


	int stackRegisterIndex = mnemonicInstance->getRegisterIndex(stackMnemonic);
	int baseRegisterIndex = mnemonicInstance->getRegisterIndex(baseMnemonic);


	if (instructionAnalyse->arguments.size() == 2)
	{
		if (MnemonicsX64::REGISTER_ADDRESS == instructionAnalyse->arguments[0]->type && instructionAnalyse->arguments[0]->registerIndex == stackRegisterIndex
			&& MnemonicsX64::VALUE == instructionAnalyse->arguments[1]->type)
		{
			*stackRegister -= instructionAnalyse->arguments[1]->value;
			return 1;
		}
	}

	return 0;
}

//int recognizePop(ProcessFunctionStackFrame::StackElement** stackElement, _DecodedInst* instruction, std::string baseMnemonic, std::string stackMnemonic,
//	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset)
int recognizePop(ProcessFunctionStackFrame::StackElement** stackElement, AssemblerInstruction* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset)
{
	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());
	MnemonicsX64::InstructionAnalyse* instructionAnalyse = mnemonicInstance->getInstructionAnalyze(instruction);


	int stackRegisterIndex = mnemonicInstance->getRegisterIndex(stackMnemonic);
	int baseRegisterIndex = mnemonicInstance->getRegisterIndex(baseMnemonic);


	if (instructionAnalyse->arguments.size() == 1)
	{
		*stackRegister += stackOffset;
		return 1;
	}


	return 0;
}

//int recognizeLea(ProcessFunctionStackFrame::StackElement** stackElement, _DecodedInst* instruction, std::string baseMnemonic, std::string stackMnemonic,
//	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset)
int recognizeLea(ProcessFunctionStackFrame::StackElement** stackElement, AssemblerInstruction* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset)
{
	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());
	MnemonicsX64::InstructionAnalyse* instructionAnalyse = mnemonicInstance->getInstructionAnalyze(instruction);


	int stackRegisterIndex = mnemonicInstance->getRegisterIndex(stackMnemonic);
	int baseRegisterIndex = mnemonicInstance->getRegisterIndex(baseMnemonic);



	if (instructionAnalyse->arguments.size() == 2)
	{
		if (MnemonicsX64::REGISTER_ADDRESS == instructionAnalyse->arguments[0]->type && instructionAnalyse->arguments[0]->registerIndex == baseRegisterIndex
			&& MnemonicsX64::REGISTER_VALUE == instructionAnalyse->arguments[1]->type)
		{
			*baseRegister = *stackRegister + instructionAnalyse->arguments[1]->offsetAddress;
			return 1;
		}
		else if(MnemonicsX64::REGISTER_ADDRESS == instructionAnalyse->arguments[0]->type && instructionAnalyse->arguments[0]->registerIndex == stackRegisterIndex
			&& instructionAnalyse->arguments[1]->registerIndex == baseRegisterIndex && MnemonicsX64::REGISTER_VALUE == instructionAnalyse->arguments[1]->type)
		{
			*stackRegister = *baseRegister + instructionAnalyse->arguments[1]->offsetAddress;
			return 1;
		}
	}

	return 0;
}
int recognizeOther(ProcessFunctionStackFrame::StackElement** stackElement, AssemblerInstruction* instruction, std::string baseMnemonic, std::string stackMnemonic,
	unsigned long long* baseRegister, unsigned long long* stackRegister, int stackOffset)
{
	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());
	MnemonicsX64::InstructionAnalyse* instructionAnalyse = mnemonicInstance->getInstructionAnalyze(instruction);


	int stackRegisterIndex = mnemonicInstance->getRegisterIndex(stackMnemonic);
	int baseRegisterIndex = mnemonicInstance->getRegisterIndex(baseMnemonic);



	if (instructionAnalyse->arguments.size() == 2)
	{
		if (MnemonicsX64::REGISTER_ADDRESS == instructionAnalyse->arguments[0]->type)
		{
			if (instructionAnalyse->arguments[1]->registerIndex == stackRegisterIndex && instructionAnalyse->arguments[1]->type == MnemonicsX64::REGISTER_VALUE)
			{
				*stackElement = new ProcessFunctionStackFrame::StackElement;
				(*stackElement)->address = *stackRegister + instructionAnalyse->arguments[1]->offsetAddress;
				(*stackElement)->instruction = instruction;
				(*stackElement)->type = ProcessFunctionStackFrame::ARGUMENT + ProcessFunctionStackFrame::VERIABLE + ProcessFunctionStackFrame::REGISTER;
				(*stackElement)->registerIndex = instructionAnalyse->arguments[0]->registerIndex;

				return 1;
			}
			else if (instructionAnalyse->arguments[1]->registerIndex == baseRegisterIndex && instructionAnalyse->arguments[1]->type == MnemonicsX64::REGISTER_VALUE)
			{
				*stackElement = new ProcessFunctionStackFrame::StackElement;
				(*stackElement)->address = *baseRegister + instructionAnalyse->arguments[1]->offsetAddress;
				(*stackElement)->instruction = instruction;
				(*stackElement)->type = ProcessFunctionStackFrame::ARGUMENT + ProcessFunctionStackFrame::VERIABLE;
				(*stackElement)->registerIndex = instructionAnalyse->arguments[0]->registerIndex;

				return 1;
			}
			else if (instructionAnalyse->arguments[0]->registerIndex == baseRegisterIndex && instructionAnalyse->arguments[1]->registerIndex == stackRegisterIndex)
			{
				*baseRegister = *stackRegister;

				return 1;
			}
		}
		else if (MnemonicsX64::REGISTER_VALUE == instructionAnalyse->arguments[0]->type)
		{
			if (instructionAnalyse->arguments[0]->registerIndex == stackRegisterIndex)
			{
				*stackElement = new ProcessFunctionStackFrame::StackElement;
				(*stackElement)->address = *stackRegister + instructionAnalyse->arguments[0]->offsetAddress;
				(*stackElement)->instruction = instruction;
				(*stackElement)->type = ProcessFunctionStackFrame::ARGUMENT + ProcessFunctionStackFrame::VERIABLE + ProcessFunctionStackFrame::REGISTER + ProcessFunctionStackFrame::PUSH_TO_STACK;
				(*stackElement)->registerIndex = instructionAnalyse->arguments[1]->registerIndex;

				return 1;

			}

		}

		if (MnemonicsX64::VALUE == instructionAnalyse->arguments[1]->type)
		{

		 if (MnemonicsX64::REGISTER_VALUE == instructionAnalyse->arguments[0]->type)
			{
				if (instructionAnalyse->arguments[0]->registerIndex == stackRegisterIndex)
				{
					*stackElement = new ProcessFunctionStackFrame::StackElement;
					(*stackElement)->address = *stackRegister + instructionAnalyse->arguments[0]->offsetAddress;
					(*stackElement)->instruction = instruction;
					(*stackElement)->type = ProcessFunctionStackFrame::ARGUMENT + ProcessFunctionStackFrame::VERIABLE + ProcessFunctionStackFrame::VALUE;
					(*stackElement)->registerIndex = instructionAnalyse->arguments[0]->registerIndex;

					return 1;
				}
				else if (instructionAnalyse->arguments[0]->registerIndex == baseRegisterIndex)
				{
					*stackElement = new ProcessFunctionStackFrame::StackElement;
					(*stackElement)->address = *baseRegister + instructionAnalyse->arguments[0]->offsetAddress;
					(*stackElement)->instruction = instruction;
					(*stackElement)->type = ProcessFunctionStackFrame::ARGUMENT + ProcessFunctionStackFrame::VERIABLE + ProcessFunctionStackFrame::VALUE;
					(*stackElement)->registerIndex = instructionAnalyse->arguments[0]->registerIndex;

					return 1;
				}
			}

		}



	}


	return 0;
}

