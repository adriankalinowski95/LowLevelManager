#include "SearchSignatureController.h"
#include "ProcessInfo.h"
#include "SearchSignature.h"


SearchSignatureController::SearchSignatureController()
{
}

SearchSignatureController::~SearchSignatureController()
{
}

int SearchSignatureController::getByInstruction(int startIndex, int instructionCount, _DecodedInst instructions[], std::string mnemonic)
{
	if (SearchSignature::getInstance().getProcessHandle() == 0)
	{
		return -1;
	}
	if (ProcessInfo::getInstance().getProcessHandle() == 0)
	{
		return -1;
	}
	int count = SearchSignature::getInstance().getByInstruction(ProcessInfo::getInstance().getProcessBaseAddress(),startIndex,instructionCount,instructions,mnemonic);

	return count;
}

unsigned long SearchSignatureController::getMaxInstruction(std::string mnemonic)
{
	if (SearchSignature::getInstance().getProcessHandle() == 0)
	{
		return -1;
	}
	if (ProcessInfo::getInstance().getProcessHandle() == 0)
	{
		return -1;
	}
	unsigned long count = SearchSignature::getInstance().getMaxByInstruction(ProcessInfo::getInstance().getProcessBaseAddress(), mnemonic);

	return count;
}

int SearchSignatureController::getInstructionByAddress(unsigned long long address, _DecodedInst* instruction)
{

	if (SearchSignature::getInstance().getProcessHandle() == 0)
	{
		return -1;
	}
	if (ProcessInfo::getInstance().getProcessHandle() == 0)
	{
		return -1;
	}

	int count = SearchSignature::getInstance().getInstructionByAddress((LPCVOID)address, instruction);

	return count;

}

int SearchSignatureController::getByOpearnd(int startIndex, int instructionCount, _DecodedInst instructions[], std::string mnemonic)
{
	if (SearchSignature::getInstance().getProcessHandle() == 0)
	{
		return -1;
	}
	if (ProcessInfo::getInstance().getProcessHandle() == 0)
	{
		return -1;
	}
	int count = SearchSignature::getInstance().getByOperand(ProcessInfo::getInstance().getProcessBaseAddress(), startIndex, instructionCount, instructions, mnemonic);

	return count;
}

unsigned long SearchSignatureController::getMaxOperands(std::string mnemonic)
{
	if (SearchSignature::getInstance().getProcessHandle() == 0)
	{
		return -1;
	}
	if (ProcessInfo::getInstance().getProcessHandle() == 0)
	{
		return -1;
	}
	unsigned long count = SearchSignature::getInstance().getMaxByOperand(ProcessInfo::getInstance().getProcessBaseAddress(), mnemonic);

	return count;
}



