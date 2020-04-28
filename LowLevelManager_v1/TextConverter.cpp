#include "TextConverter.h"

TextConverter::TextConverter()
{
}

TextConverter::~TextConverter()
{
}

BYTE TextConverter::convertSingToByte(const char sign)
{
	BYTE value = 0;
	if ((BYTE)sign >= 48 && (BYTE)sign <= 57)
	{	
		value = (BYTE)sign - 48;
	}
	else if ((BYTE)sign >= 65 && (BYTE)sign <= 70)
	{
		value = (BYTE)sign - 65 + 10;
	}
	else if ((BYTE)sign >= 97 && (BYTE)sign <= 102)
	{
		value = (BYTE)sign - 97 + 10;
	}
	else
		value = -1;

	return value;
}

bool TextConverter::convertCStrToLPBYTE(const char* shellcodeAsCstr, BYTE* output, int* output_size)
{
	int smallCounter = 0;
	BYTE workByte = 0;
	BYTE valueInto = 0;
	for (int i = 0; i < strlen(shellcodeAsCstr); i++)
	{
		if (smallCounter == 0)
		{
			if (shellcodeAsCstr[i] != ' ')
			{
				workByte = convertSingToByte(shellcodeAsCstr[i]);
				if (workByte != -1)
				{
					valueInto = workByte << 4;
					smallCounter = 1;
				}
			}
		}
		else if (smallCounter == 1)
		{
			if (shellcodeAsCstr[i] != ' ')
			{
				workByte = convertSingToByte(shellcodeAsCstr[i]);
				if (workByte != -1)
				{
					valueInto |= workByte;
					output[*output_size] = valueInto;
					(*output_size)++;
					smallCounter = 0;
				}
			}
		}
	}
	if (smallCounter == 1)
	{
		return false;
	}

	return true;
}
