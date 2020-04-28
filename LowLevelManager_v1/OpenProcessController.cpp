#include "OpenProcessController.h"
#include <comdef.h>


OpenProcessController::OpenProcessController(MainController* mainController):mainController(mainController)
{

}


bool OpenProcessController::loadProcess(std::vector<CharProcessStruct>* processes)
{
	this->processVector = new std::vector<ProcessStruct>();
	bool success = this->mainController->getInjector()->getProcessList(processVector);
	if (success == true)
	{
	
		char processPID[10];
		
		for (int i = 0; i < processVector->size(); i++)
		{
			_bstr_t processName(processVector->at(i).processName);
			sprintf(processPID, "%d", processVector->at(i).processPID);
			struct CharProcessStruct proc;
			strcpy_s(proc.processName , processName);
			strcpy_s(proc.processPID, processPID);
			processes->push_back(proc);
		}
	}
	return true;
}

bool OpenProcessController::selectProcess(int index)
{
	if (index >= 0)
	{
		bool success = this->mainController->loadProcessByPID(this->processVector->at(index).processPID);
		
		return success;
	}
	else
		return false;
	
}