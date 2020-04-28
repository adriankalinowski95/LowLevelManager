#pragma once

#include <string>
#include <distorm.h>


class Assembler
{
public:
	static Assembler& getInstance()
	{
		static Assembler assembler;
		return assembler;
	}

public:
	enum Architecture
	{
		X86Arch = 1,
		X64Arch = 2
	};

public:
	Assembler();
	~Assembler();

public:
	int convertAsmToByte(std::string asmString, uint8_t** asmByte,int arch);

private:
	int architecture;


};

