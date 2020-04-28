#include "ProcessFunctionConvention.h"
#include "Service/ProcessInfo.h"
#include "Service/SearchSignature.h"
#include "Service/MnemonicsX64.h"
#include <algorithm>
#include <string>



//poprawic wyszukiwanie calla
//lista callow + sprawdzanie czy za nim i po nim nie ma ADD
#define PROCESS_FUNCTION_CONVENTION_START_ADDRESS 0 
#define PROCESS_FUNCTION_CONVENTION_INSTRUCTION_COUNT 100
#define MAX_CHAR_ARRAY_SIZE 255

ProcessFunctionConvention::ProcessFunctionConvention()
{

}

ProcessFunctionConvention::~ProcessFunctionConvention()
{

}

/*
//int ProcessFunctionConvention::recognizeConvention(_DecodedInst* instructions, int instructionsCount, _DecodedInst* afterCallInstruction)
int ProcessFunctionConvention::recognizeConvention(std::vector<AssemblerInstruction*> instructions, AssemblerInstruction* afterCallInstruction)
{

	ProcessInstructionReader* pir = &(ProcessInstructionReader::getInstrance());
	std::vector<AssemblerInstruction*> instructions;

	if (instructionsCount <= 0)
		return -1;

	//unsigned long long startFunctionAddress = instructions[0].offset;
	unsigned long long startFunctionAddress = instructions->getOffset();

	_DecodedInst callInstruction[PROCESS_FUNCTION_CONVENTION_INSTRUCTION_COUNT];

	int instructionCount = this->searchCallAddress(startFunctionAddress, callInstruction);
	
	if (instructionCount == 0)
		return -1;

	_DecodedInst instructionAfterCall;
	SearchSignature* searchSignature = &(SearchSignature::getInstance());

	std::string addMnemonic;
	std::string retMnemonic;


	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());
	int reason = mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_ADD, &addMnemonic);
	if (reason == -1)
		return -1;

	reason = mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_RET, &retMnemonic);
	if (reason == -1)
		return -1;

	int convention = -1;

	for (int i = 0; i < instructionCount; i++)
	{
		int reason = searchSignature->getInstructionByAddress((LPCVOID)(callInstruction[i].offset + callInstruction[i].size), &instructionAfterCall);

		if (reason == -1)
			return -1;

		std::string afterCallInstructionString((const char*)instructionAfterCall.mnemonic.p);
		
		if (afterCallInstructionString.find(addMnemonic) != std::string::npos)
		{
			memcpy(afterCallInstruction, &instructionAfterCall, sizeof(_DecodedInst));
			return ProcessFunctionConvention::CDECL_CONVENTION;
		}
	}

	std::string lastInstructionMnemonicString((const char*)instructions[instructionsCount - 1].mnemonic.p);

	if (lastInstructionMnemonicString.find(retMnemonic) != std::string::npos)
	{
		if (instructions[instructionsCount - 1].operands.length > 0)
		{
			return ProcessFunctionConvention::STDCALL_CONVENTION;
		}
		else
		{
			return ProcessFunctionConvention::OTHER_CONVENTION;
		}
	}

	return 0;
}
*/

int ProcessFunctionConvention::recognizeConvention(std::vector<AssemblerInstruction*>&instructions, AssemblerInstruction& afterCallInstruction)
{

	ProcessInstructionReader* pir = &(ProcessInstructionReader::getInstrance());
	std::vector<AssemblerInstruction*> callInstructions;
	if (instructions.size() <= 0)
		return -1;

	unsigned long long startFunctionAddress = instructions.at(0)->getOffset();

	int instructionCount = this->searchCallAddress(startFunctionAddress, callInstructions);

	if (instructionCount <= 0)
		return -1;

	std::string addMnemonic;
	std::string retMnemonic;


	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());
	int reason = mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_ADD, &addMnemonic);
	if (reason == -1)
		return -1;

	reason = mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_RET, &retMnemonic);
	if (reason == -1)
		return -1;

	int convention = -1;

	
	for (int i = 0; i < callInstructions.size(); i++)
	{
		
		//int reason = searchSignature->getInstructionByAddress((LPCVOID)(callInstruction[i].offset + callInstruction[i].size), &instructionAfterCall);
		//int reason = pir->getInstructionByAddress((LPCVOID)(instructions.at(i)->getOffset() + instructions.at(i)->getSize()),&instructionAfterCall);
		AssemblerInstruction* instructionAfterCall;

		int reason = pir->getInstructionByAddress((callInstructions.at(i)->getOffset() + callInstructions.at(i)->getSize()), &instructionAfterCall);

		if (reason == -1)
			return -1;

		if (instructionAfterCall->getMnemonic().find(addMnemonic) != std::string::npos)
		{

		
			//	_DecodedInst
			_DecodedInst* newDecodedInst = new _DecodedInst;
			 memcpy(newDecodedInst, instructionAfterCall->getDecodedInst(), sizeof(_DecodedInst));
			 afterCallInstruction.lazyInit(instructionAfterCall->getArchitecture(), newDecodedInst);
			 
			 delete instructionAfterCall;

			return ProcessFunctionConvention::CDECL_CONVENTION;
		}

		delete instructionAfterCall;
	}

	std::string lastInstructionMnemonicString(instructions.at(instructions.size() -1 )->getMnemonic());

	if (lastInstructionMnemonicString.find(retMnemonic) != std::string::npos)
	{
		if (instructions.at(instructions.size() - 1)->getOperandsLength() > 0)
		{
			return ProcessFunctionConvention::STDCALL_CONVENTION;
		}
		else
		{
			return ProcessFunctionConvention::OTHER_CONVENTION;
		}
	}

	return 0;
}


/*
//int ProcessFunctionConvention::searchCallAddress(unsigned long long startFunctionAddress, _DecodedInst* callInstruction)
int ProcessFunctionConvention::searchCallAddress(unsigned long long startFunctionAddress, AssemblerInstruction* callInstruction)
{
	
	if (SearchSignature::getInstance().getProcessHandle() == 0)
	{
		return -1;
	}
	
	//if(ProcessInstructionReader::get)
	if (ProcessInfo::getInstance().getProcessHandle() == 0)
	{
		return -1;
	}
	
	int reason = -1;

	char charHexAddress[MAX_CHAR_ARRAY_SIZE];
	
	sprintf(charHexAddress, "0X%I64X", startFunctionAddress);

	std::string hexAddress(charHexAddress);
	std::string callMnemonic;
	std::string jmpMnemonic;

	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());
	reason =  mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_CALL, &callMnemonic);

	if (reason == -1)
		return -1;

	reason = mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_JMP, &jmpMnemonic);

	if (reason == -1)
		return -1;

	//int instructionCount = SearchSignature::getInstance().getByOperand(ProcessInfo::getInstance().getProcessBaseAddress(), PROCESS_FUNCTION_CONVENTION_START_ADDRESS,
	//															PROCESS_FUNCTION_CONVENTION_INSTRUCTION_COUNT, callInstruction, hexAddress);

	ProcessInstructionReader* pir = &(ProcessInstructionReader::getInstrance());
	std::vector<AssemblerInstruction*> instructions;

	int success = pir->getByOperand((unsigned long long)ProcessInfo::getInstance().getProcessBaseAddress(), PROCESS_FUNCTION_CONVENTION_START_ADDRESS,
											PROCESS_FUNCTION_CONVENTION_INSTRUCTION_COUNT,instructions, hexAddress);


	if (success == ProcessInstructionReader::PROCESS_INSTRUCTION_READER_SUCESS && instructions.size() > 0)
	{
		//if (callMnemonic.compare((const char*)callInstruction[0].mnemonic.p) == 0)
		//	return instructionCount;

		if (callMnemonic.compare(instructions.at(0)->getMnemonic()) == 0)
			return instructions.size();

		//else if (jmpMnemonic.compare((const char*)callInstruction[0].mnemonic.p) == 0)
		else if (jmpMnemonic.compare(instructions.at(0)->getMnemonic()) == 0)
		{
			//char charHexAddress2[MAX_CHAR_ARRAY_SIZE];
			//sprintf(charHexAddress2, "0X%I64X", callInstruction[0].offset);
			//std::string hexAddress2(charHexAddress2);
			//int secondInstructionCount = SearchSignature::getInstance().getByOperand(ProcessInfo::getInstance().getProcessBaseAddress(), PROCESS_FUNCTION_CONVENTION_START_ADDRESS,
			//																			PROCESS_FUNCTION_CONVENTION_INSTRUCTION_COUNT, callInstruction, hexAddress2);
			
			std::string hexAddress = instructions.at(0)->getOffsetString();
			
			while (!instructions.empty()) {
				delete instructions.back();
				instructions.pop_back();
			}

			int success = pir->getByOperand((unsigned long long)ProcessInfo::getInstance().getProcessBaseAddress(), PROCESS_FUNCTION_CONVENTION_START_ADDRESS,
											PROCESS_FUNCTION_CONVENTION_INSTRUCTION_COUNT, instructions, hexAddress);
			
			//if (success > 0)
			//{
		//		return secondInstructionCount;
		//	}

			if (success == ProcessInstructionReader::PROCESS_INSTRUCTION_READER_SUCESS && instructions.size() > 0)
			{
				return instructions.size();
			}
		}
	}
	
	return 0;

}

*/

int ProcessFunctionConvention::searchCallAddress(unsigned long long startFunctionAddress, std::vector<AssemblerInstruction*>& callInstructions)
{

	if (ProcessInfo::getInstance().getProcessHandle() == 0)
	{
		return -1;
	}

	int reason = -1;

	char charHexAddress[MAX_CHAR_ARRAY_SIZE];

	sprintf(charHexAddress, "0X%I64X", startFunctionAddress);

	std::string hexAddress(charHexAddress);
	std::string callMnemonic;
	std::string jmpMnemonic;

	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());
	reason = mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_CALL, &callMnemonic);

	if (reason == -1)
		return -1;

	reason = mnemonicInstance->getInstructionByIndex(MnemonicsX64::I_JMP, &jmpMnemonic);

	if (reason == -1)
		return -1;

	ProcessInstructionReader* pir = &(ProcessInstructionReader::getInstrance());

	std::vector<AssemblerInstruction*> tempCallInstructions;
	std::vector<AssemblerInstruction*> temp2CallInstructions;

	int success = pir->getByOperand((unsigned long long)ProcessInfo::getInstance().getProcessBaseAddress(), PROCESS_FUNCTION_CONVENTION_START_ADDRESS,
		PROCESS_FUNCTION_CONVENTION_INSTRUCTION_COUNT, tempCallInstructions, hexAddress);

	bool itWasCall = false;
	if (success == ProcessInstructionReader::PROCESS_INSTRUCTION_READER_SUCESS && tempCallInstructions.size() > 0)
	{
		for (int i = 0; i < tempCallInstructions.size(); i++)
		{
			if (callMnemonic.compare(tempCallInstructions.at(i)->getMnemonic()) == 0)
			{
				callInstructions.push_back(tempCallInstructions.at(i));
				itWasCall = true;
			}
		}
		if (itWasCall == true)
		{
			return callInstructions.size();
		}

		for (int i = 0; i < tempCallInstructions.size(); i++)
		{
			if (jmpMnemonic.compare(tempCallInstructions.at(i)->getMnemonic()) == 0)
			{
				std::string hexAddress = tempCallInstructions.at(i)->getOffsetString();

				int success = pir->getByOperand((unsigned long long)ProcessInfo::getInstance().getProcessBaseAddress(), PROCESS_FUNCTION_CONVENTION_START_ADDRESS,
					PROCESS_FUNCTION_CONVENTION_INSTRUCTION_COUNT, callInstructions, hexAddress);
				
			
				
				if (success == ProcessInstructionReader::PROCESS_INSTRUCTION_READER_SUCESS && callInstructions.size() > 0)
				{
					while (!tempCallInstructions.empty()) {
						delete tempCallInstructions.back();
						tempCallInstructions.pop_back();
					}
					return callInstructions.size();
				}
			}
		}
		
	}

	return 0;
}