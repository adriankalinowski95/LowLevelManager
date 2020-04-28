#include "InformationProcessController.h"

#include "stdio.h"
#include <string>

#define BASE_ADDRESS "Base address"
#define ENTRY_POINT_ADDRESS "Entry point address"
#define ARCHITECTURE "Architecture"


InformationProcessController::InformationProcessController(MainController* mainController) :mainController(mainController)
{

}


bool InformationProcessController::getInfromation(std::vector<CharInformationStruct>* processInfo)
{
	DWORD_PTR entryPointAddress = this->mainController->getProcessInformation()->getEntryPointAddress();
	DWORD_PTR baseAddress = (DWORD_PTR)this->mainController->getProcessInformation()->getProcessBaseAddress();
	std::string architecture = this->mainController->getProcessInformation()->getArchitectureString();
	struct CharInformationStruct charInfStruct1;
	struct CharInformationStruct charInfStruct2;
	struct CharInformationStruct charInfStruct3;

	char buffer[MAX_CHAR_ARRAY];
	sprintf(buffer, "0x%I64X", baseAddress);

	strcpy_s(charInfStruct1.information, BASE_ADDRESS);
	strcpy_s(charInfStruct1.value, buffer);

	processInfo->push_back(charInfStruct1);

	sprintf(buffer, "0x%I64X", entryPointAddress);

	strcpy_s(charInfStruct2.information, ENTRY_POINT_ADDRESS);
	strcpy_s(charInfStruct2.value, buffer);

	processInfo->push_back(charInfStruct2);

	strcpy_s(charInfStruct3.information, ARCHITECTURE);
	strcpy_s(charInfStruct3.value, architecture.c_str());

	processInfo->push_back(charInfStruct3);

	return true;
}