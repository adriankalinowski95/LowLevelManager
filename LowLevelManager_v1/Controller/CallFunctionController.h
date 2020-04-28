#pragma once
#include "ProcessModel/ProcessFunction.h"

class CallFunctionController
{
public:
	CallFunctionController();
	~CallFunctionController();

public:
	std::vector<ProcessFunction::FunctionParamter*>* getFunctionParameters(const char* functionAddress);
	int callFunction(std::vector<ProcessFunction::FunctionParamter*>* parameters, const char* functionAddress);
};

