#include "MainController.h"
#include "SearchSignature.h"
#include "InjectShellcode.h"
#include "ProcessFunctionDAO.h"
#include <string>


using namespace std;





MainController::MainController()
{
	this->processInjector = new Injector();
}

MainController::~MainController()
{
	
}

void MainController::getProcessList()
{
	vector<ProcessStruct> processesList;
	bool isSuccess = this->processInjector->getProcessList(&processesList);

	for (int i = 0; i < processesList.size(); i++)
	{
		printf("get process list : %S  (PID: %u)\n", processesList[i].processName, processesList[i].processPID);
	}
}
/*
* Nie uzywane.
*/
HANDLE MainController::loadProcessByName(LPWSTR processName)
{
	HANDLE processHandle = this->processInjector->loadProcessByName(processName);

	if (processHandle == NULL)
		return NULL;

	this->processInformation = &(ProcessInfo::getInstance());
	bool success = this->processInformation->loadProcessBaseInformation();

	if (success == false)
		return NULL;

	//this->processReader = new PEReader(processHandle, (LPCVOID)this->processInformation->getEntryPointAddress());

	this->processWriter = new PEWrite(processHandle);


	//this->processReader->readProcess((LPCVOID)this->processInformation->getEntryPointAddress());

	return processHandle;
}

bool MainController::loadProcessByPID(DWORD pid)
{
	HANDLE processHandle = this->processInjector->loadProcessByPID(pid);
	if (processHandle == NULL)
		return false;

	this->processInformation = &(ProcessInfo::getInstance());
	this->processInformation->setProcessHandle(processHandle);
	this->processInformation->recognizeArchitecture();

	if (this->processInformation->recognizeArchitecture() == ProcessInfo::X64Arch || this->processInformation->recognizeArchitecture() == ProcessInfo::X86Arch)
	{
		bool success = this->processInformation->loadProcessBaseInformation64();
		if (success == false)
			return false;
	}
	/*
	if (this->processInformation->recognizeArchitecture() == ProcessInfo::X86Arch)
	{
		bool success = this->processInformation->loadProcessBaseInformation64();
		if (success == false)
			return false;
	}
	*/

	//this->processReader = new PEReader(processHandle,(LPCVOID)this->processInformation->getEntryPointAddress());

	PEReader* processReader = &(PEReader::getInstance());
	
	processReader->setProcessHandle(processHandle);

	this->processReader = processReader;

	this->processWriter = new PEWrite(processHandle);
	
	SearchSignature* searchSignature = &(SearchSignature::getInstance());

	searchSignature->setProcessHandle(processHandle);

	InjectShellcode* injectShellcode = &(InjectShellcode::getInstance());

	injectShellcode->setProcessHandle(processHandle);

	ProcessFunctionDAO* processFunctionDAO = &(ProcessFunctionDAO::getInstance());

	processFunctionDAO->setProcessHandle(processHandle);


	printf("process size: %d \n", this->processReader->getProcessSize(this->processInformation->getProcessBaseAddress()));

	//this->processReader->readProcess();

	return true;
}

int MainController::getInstructions(LPCVOID startAddress, _DecodedInst instructions[], int byteSize)
{
	if (this->processReader != NULL)
	{
		return this->processReader->getInstructions(startAddress, instructions, byteSize);
	}
	else
	{
		return -1;
	}
}

int MainController::getInstructionsByIndex(LPCVOID startAddress, _DecodedInst instructions[], unsigned long startIndex, int instructionCount)
{
	if (this->processReader != NULL)
	{
		return this->processReader->getInstructionsByIndex(startAddress, instructions, startIndex, instructionCount);
	}
	else
	{
		return -1;
	}
}

unsigned long MainController::getInstructionIndex(LPCVOID startAddress, LPCVOID instructionAddress)
{
	if (this->processReader != NULL)
	{
		return this->processReader->getInstructionIndex(startAddress, instructionAddress);
	}
	else
	{
		return -1;
	}
}

ProcessInfo* MainController::getProcessInformation()
{
	return this->processInformation;
}

Injector* MainController::getInjector()
{
	return this->processInjector;
}

PEWrite* MainController::getPEWrtie()
{
	return this->processWriter;
}

PEReader* MainController::getPEReader()
{
	return this->processReader;
}
