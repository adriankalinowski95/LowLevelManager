#pragma once
#include "windows.h"


class TextConverter
{
public:
	TextConverter();
	~TextConverter();
	static BYTE convertSingToByte(const char sign);
	static bool convertCStrToLPBYTE(const char* shellcodeAsCstr, BYTE* output, int* output_size);

private:

};

