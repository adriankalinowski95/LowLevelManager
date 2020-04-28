#pragma once
#include "ProcessFunctionDAO.h"
#include <string>


class RecognizeFunctionController
{
public:
	RecognizeFunctionController();
	~RecognizeFunctionController();

public:
	ProcessFunction* getProcessFunction(std::string stringFunctionAddress);
	struct FunctionParamter* getParameters(ProcessFunction* processFunction);
};

