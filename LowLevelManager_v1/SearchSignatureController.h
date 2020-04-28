#pragma once
#include "distorm.h"
#include <string>

class SearchSignatureController
{
public:
	SearchSignatureController();
	~SearchSignatureController();
	int getByInstruction(int startIndex,int instructionCount, _DecodedInst instructions[], std::string mnemonic);
	unsigned long getMaxInstruction(std::string mnemonic);
	int getInstructionByAddress(unsigned long long address, _DecodedInst* instruction);
	int getByOpearnd(int startIndex, int instructionCount, _DecodedInst instructions[], std::string mnemonic);
	unsigned long getMaxOperands(std::string mnemonic);
};

