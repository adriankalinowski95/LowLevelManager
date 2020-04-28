#include "InformationForm.h"
using namespace System;
using namespace System::Windows::Forms;

void LowLevelManagerv1::InformationForm::setMainController(MainController* mainController)
{
	this->mainController = mainController;
	this->informationProcessController = new InformationProcessController(mainController);
}


void LowLevelManagerv1::InformationForm::loadProcessInformation()
{
	std::vector<CharInformationStruct> processInformationVector;
	bool success = this->informationProcessController->getInfromation(&processInformationVector);

	if (success == true)
	{
		for (int i = 0; i < processInformationVector.size(); i++)
		{
			this->dataGridView1->Rows->Add(gcnew String(processInformationVector[i].information), gcnew String(processInformationVector[i].value));
		}
	}
}