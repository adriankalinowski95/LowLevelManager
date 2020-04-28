#include "ProcessFunctionReturnedValue.h"
#include "ProcessFunctionConvention.h"
#include "MnemonicsX64.h"

ProcessFunctionReturnedValue::ProcessFunctionReturnedValue()
{
}

ProcessFunctionReturnedValue::~ProcessFunctionReturnedValue()
{
}

ProcessFunctionReturnedValue::ReturnedValue* ProcessFunctionReturnedValue::recognizeReturnedParameter(_DecodedInst* instructions, int instructionCount)
{
	/*
	_DecodedInst instAfterCall;
	ProcessFunctionConvention* processFunctionConvention = &(ProcessFunctionConvention::getInstance());

	int functionConvention =  processFunctionConvention->recognizeConvention(instructions, instructionCount,&instAfterCall);

	if (functionConvention == -1)
	{
		return nullptr;
	}

	std::string registerMnemonic;
	MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());
	int reason = -1;

	if(functionConvention == ProcessFunctionConvention::CDECL_CONVENTION)
	{
		int reason = mnemonicInstance->getInstructionByIndex(MnemonicsX64::R_EAX, &registerMnemonic);
		ReturnedValue* newReturnedValue = new ReturnedValue;
		newReturnedValue->registerMnemonic = registerMnemonic;
		newReturnedValue->registerIndex = MnemonicsX64::R_EAX;
		newReturnedValue->type = ProcessFunctionReturnedValue::REGISTER;
		return newReturnedValue;
	}
	if (functionConvention == ProcessFunctionConvention::STDCALL_CONVENTION)
	{

	}
	if (functionConvention == ProcessFunctionConvention::OTHER_CONVENTION)
	{

	}
	*/
	return 0;
}
