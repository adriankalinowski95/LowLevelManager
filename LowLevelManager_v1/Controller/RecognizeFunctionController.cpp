#include "RecognizeFunctionController.h"

RecognizeFunctionController::RecognizeFunctionController()
{

}

RecognizeFunctionController::~RecognizeFunctionController()
{

}

ProcessFunction* RecognizeFunctionController::getProcessFunction(std::string stringFunctionAddress)
{
	unsigned long long functionAddress = 0;
	sscanf(stringFunctionAddress.c_str(), "%I64X", &functionAddress);

	ProcessFunctionDAO* processFunctionDAO = &(ProcessFunctionDAO::getInstance());

	ProcessFunction* function = processFunctionDAO->getProcessFunctionByAddress(functionAddress);

	return function;
}

FunctionParamter* RecognizeFunctionController::getParameters(ProcessFunction* processFunction)
{
	processFunction->getFuncionParameters();
	return nullptr;
}
