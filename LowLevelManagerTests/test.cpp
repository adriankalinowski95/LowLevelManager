#include "pch.h"
#include "Assembler.h"
#include "Disassembler.h"


const char x86AssemblerTestInstruction[] = "MOV EAX, EBX";
const uint8_t x86AssemblerTestOutput[] = { 0x8B, 0xC3 };

const char x64AssemblerTestInstruction[] = "MOV RAX, RBX";
const uint8_t x64AssemblerTestOutput[] = { 0x48, 0x8B, 0xC3 };

const int ARRAY_SIZE = 100;


TEST(AssemblerTest, Assembling86)
{	
	uint8_t* testPointer;
	int bytesCount = 0, status = 0;

	Assembler* assemblerPointer = &(Assembler::getInstance());
	status = assemblerPointer->convertAsmToByte(std::string(x86AssemblerTestInstruction),&testPointer,Assembler::X86Arch);

	if (status == -1) 	FAIL();

	for (int i = 0; i < status; i++)
	{
		if (testPointer[i] != x86AssemblerTestOutput[i]) FAIL();
	}
	
	SUCCEED();
}

TEST(AssemblerTest, Assembling64)
{
	uint8_t* testPointer;
	int bytesCount = 0, status = 0;

	Assembler* assemblerPointer = &(Assembler::getInstance());
	status = assemblerPointer->convertAsmToByte(std::string(x64AssemblerTestInstruction), &testPointer, Assembler::X64Arch);

	if (status == -1) 	FAIL();

	for (int i = 0; i < status; i++)
	{
		if (testPointer[i] != x64AssemblerTestOutput[i]) FAIL();
	}

	SUCCEED();

}

TEST(DisassemblerTest, Dissembling86)
{
	uint8_t* testPointer;
	int bytesCount = 0, status = 0;
	std::vector<AssemblerInstruction*> assemblerInstructions;
	Disassembler* disassemblerPointer = &(Disassembler::getInstance());

	status = disassemblerPointer->dissassembly(0, x86AssemblerTestOutput,sizeof(x86AssemblerTestOutput), Disassembler::X86Arch, assemblerInstructions);

	if (status == -1) 	FAIL();

	std::string instruction(assemblerInstructions[0]->getMnemonic());
	instruction +=" "+ assemblerInstructions[0]->getOperands();

	if (instruction.compare(x86AssemblerTestInstruction) == 0)
		SUCCEED();
	else
		FAIL();

}

TEST(DisassemblerTest, Dissembling64)
{
	uint8_t* testPointer;
	int bytesCount = 0, status = 0;
	std::vector<AssemblerInstruction*> assemblerInstructions;
	Disassembler* disassemblerPointer = &(Disassembler::getInstance());

	status = disassemblerPointer->dissassembly(0, x64AssemblerTestOutput, sizeof(x64AssemblerTestOutput), Disassembler::X64Arch, assemblerInstructions);

	if (status == -1) 	FAIL();

	std::string instruction(assemblerInstructions[0]->getMnemonic());
	instruction += " " + assemblerInstructions[0]->getOperands();

	if (instruction.compare(x64AssemblerTestInstruction) == 0)
		SUCCEED();
	else
		FAIL();

}