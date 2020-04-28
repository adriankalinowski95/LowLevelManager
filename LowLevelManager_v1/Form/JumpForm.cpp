#include "JumpForm.h"
#include "MainForm.h"
#include "ProcessDataAccess/ProcessInstructionReader.h"
#include "Service/ProcessInfo.h"
#include "InfoForm.h"

void LowLevelManagerv1::JumpForm::jumpToAddress()
{
	String^ jumpAddress = this->jumpAddressEditText->Text;
	char operationCStr[50] = { 0 };
	if (jumpAddress->Length > 0)
	{
		

		sprintf(operationCStr, "%s", jumpAddress);
		unsigned __int64 addressToJump = 0;
		sscanf(operationCStr, "%I64X", &addressToJump);
		DWORD_PTR startAddress = (DWORD_PTR)(&ProcessInfo::getInstance())->getProcessBaseAddress();
		ProcessInstructionReader* pir = &(ProcessInstructionReader::getInstrance());
		unsigned long long processSize = pir->getProcessSize(startAddress);
		if (addressToJump >= startAddress && addressToJump <= (startAddress + processSize))
		{
			this->mainForm->jumpToAddress(jumpAddress);
			this->Close();
		}
		else
		{
			this->Close();
			InfoForm^ infoForm = gcnew InfoForm();
			infoForm->setText(std::string("Bad address!"));
			infoForm->ShowDialog();
			delete infoForm;
		}
	}
}

void LowLevelManagerv1::JumpForm::setMainForm(MainForm^ mainForm)
{
	this->mainForm = mainForm;
}
