#pragma once
#include "ProcessFunction.h"
#include "AssemblerInstruction.h"
#include <vector>

class ProcessFunctionCaller
{

public:
	static ProcessFunctionCaller& getInstance()
	{
		static ProcessFunctionCaller processFunctionCaller;
		return processFunctionCaller;
	}

public:
	ProcessFunctionCaller();
	~ProcessFunctionCaller();
	/*
public:
	int callFunction(std::vector<ProcessFunction::FunctionParamter*>* parameters, _DecodedInst* instructions, int instructionsCount);
	std::string setParameterByStack(const ProcessFunction::FunctionParamter* parameter,std::string stackRegister,int* stackOffset);
	std::string setParamterByRegister(const ProcessFunction::FunctionParamter* parameter,int* stackOffset);

private:
	std::string conventionInstrucions(std::vector<ProcessFunction::FunctionParamter*>* parameters, _DecodedInst* instructions, int instructionsCount, int* stackOffset);
	std::string cdeclConventionInstructions(const ProcessFunction::FunctionParamter* parameter);
	std::string stdcallConventionInstructions(const ProcessFunction::FunctionParamter* parameter);
	std::string	otherConventionInstructions(const ProcessFunction::FunctionParamter* parameter,int* stackOffset);

private:
	std::string callingEpilog(std::vector<ProcessFunction::FunctionParamter*>* parameters, _DecodedInst* instructions, 
							int instructionsCount,unsigned long long functionAddress, int stackOffset);
	std::string cdcelCallingEpilog(unsigned long long functionAddress,int stackOffset);
	std::string stdcallCallingEpilog(unsigned long long functionAddress, int stackOffset);
	std::string otherCallingEpilog(unsigned long long functionAddress, int stackOffset);

private:
	std::string callingProlog(std::vector<ProcessFunction::FunctionParamter*>* parameters, _DecodedInst* instructions, int instructionsCount, int stackOffset);
	std::string cdcelCallingProlog(int stackOffset);
	std::string stdcallCallingProlog(int stackOffset);
	std::string otherCallingProlog(int stackOffset);
	*/

public:
	int callFunction(std::vector<ProcessFunction::FunctionParamter*>* parameters,std::vector<AssemblerInstruction*>& instructions);

public:
	std::string getInstructionsToCall(std::vector<ProcessFunction::FunctionParamter*>* parameters, std::vector<AssemblerInstruction*>& instructions);
	std::string putParamByStack(const ProcessFunction::FunctionParamter* parameter, std::string stackRegister, int* stackOffset);
	std::string putParametersByRegister(const ProcessFunction::FunctionParamter* parameter, std::string& assemblerVeriables,int* veriableCount);
	std::string putCallInstructions(unsigned long long functionAddress);
	std::string putFunctionEpilog(std::vector<AssemblerInstruction*>& instructions, int convention, int stackOffset,int paramByRegisterCount);


private:
	int architectureOffset;
};

