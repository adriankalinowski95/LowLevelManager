#include "Assembler.h"

#include <asmtk/asmtk.h>

using namespace asmjit;
using namespace asmtk;

#include <stdio.h>
#include <stdlib.h>




Assembler::Assembler()
{

}

Assembler::~Assembler()
{

}


int Assembler::convertAsmToByte(std::string asmString, uint8_t** asmByte,int arch)
{
	
	if (asmString.length() <= 0)
	{
		return -1;
	}


	CodeHolder code;

	if (arch == Assembler::X64Arch)
	{
		code.init(CodeInfo(ArchInfo::kIdX64));
	}
	else
	{
		code.init(CodeInfo(ArchInfo::kIdX86));
	}
	
	x86::Assembler assembler(&code);

	
	AsmParser parser(&assembler);

	Error errorCheck = parser.parse(asmString.c_str());

	if (errorCheck) {
		printf("ERROR: %08x (%s)\n", errorCheck, DebugUtils::errorAsString(errorCheck));
		return -1;
	}

	CodeBuffer & buffer = code.sections().at(0)->buffer();

	*asmByte = new uint8_t[buffer.size()];
	memcpy(*asmByte, buffer.data(), buffer.size());

	return buffer.size();

}


