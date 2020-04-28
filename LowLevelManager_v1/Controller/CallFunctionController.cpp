#include "CallFunctionController.h"
#include "ProcessDataAccess/ProcessFunctionDAO.h"



CallFunctionController::CallFunctionController()
{

}

CallFunctionController::~CallFunctionController()
{

}

std::vector<ProcessFunction::FunctionParamter*>* CallFunctionController::getFunctionParameters(const char* functionAddress)
{
	unsigned long long address = 0;
	sscanf(functionAddress, "%I64X", &address);

	ProcessFunctionDAO* processFunctionDAO = &(ProcessFunctionDAO::getInstance());

	ProcessFunction* processFunction = processFunctionDAO->getProcessFunctionByAddress(address);

	std::vector<ProcessFunction::FunctionParamter*>* parameters = processFunction->getFuncionParameters();

	return parameters;
}

int CallFunctionController::callFunction(std::vector<ProcessFunction::FunctionParamter*>* parameters, const char* functionAddress)
{
	unsigned long long address = 0;
	sscanf(functionAddress, "%I64X", &address);

	ProcessFunctionDAO* processFunctionDAO = &(ProcessFunctionDAO::getInstance());

	ProcessFunction* processFunction = processFunctionDAO->getProcessFunctionByAddress(address);

	return processFunction->callFunction(parameters);

}
