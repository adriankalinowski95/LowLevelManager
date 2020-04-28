#pragma once
#include "ProcessDataAccess/ProcessFunctionDAO.h"
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

