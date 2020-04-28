#pragma once
#include <Windows.h>
#include <string>
#include "distorm.h"


class ProcessFunctionReturnedValue
{
public:
	static ProcessFunctionReturnedValue& getInstance()
	{
		static ProcessFunctionReturnedValue instance;
		return instance;
	}

public:
	enum ReturnedValueType
	{
		REGISTER = 1,
		STACK = 2
	};

public:
	struct ReturnedValue
	{
		int type;
		int registerIndex;
		std::string registerMnemonic;
	};


public:
	ProcessFunctionReturnedValue();
	~ProcessFunctionReturnedValue();
	ReturnedValue* recognizeReturnedParameter(_DecodedInst* instructions,int instructionCount);
	

};

