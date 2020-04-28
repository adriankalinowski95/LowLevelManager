#include "OpenProcessForm.h"
using namespace System;
using namespace System::Windows::Forms;


#define COL_1_NAME "Process name"
#define COL_1_NUMBER 0

#define COL_2_NAME "PID"
#define COL_2_NUMBER 1


void LowLevelManagerv1::OpenProcessForm::setMainController(MainController* mainController)
{
	this->mainController = mainController;
	this->openProcessController = new OpenProcessController(mainController);
}


void LowLevelManagerv1::OpenProcessForm::loadProcesses()
{
	std::vector<CharProcessStruct> processVector;
	bool success = this->openProcessController->loadProcess(&processVector);

	if (success == true)
	{
		for (int i = 0; i < processVector.size(); i++)
		{
			this->dataGridView1->Rows->Add(gcnew String(processVector[i].processName), gcnew String(processVector[i].processPID));
		}
	}
}

