#include "RecognizeFunctionForm.h"
#include "Controller/RecognizeFunctionController.h"
#include "ProcessDataAccess/ProcessInstructionReader.h"
#include "InfoForm.h"
#include <string>
#include "CallFunctionForm.h"
#include <vcclr.h>
#include <comdef.h>
#define INSTURCTION_ADDRESS_SIZE 100

void LowLevelManagerv1::RecognizeFunctionForm::loadFunction()
{
	String^ address = this->functionAddressTextBox->Text;
	if (address->Length > 0)
	{
		/*
		pin_ptr<const wchar_t> str1 = PtrToStringChars(text);
		_bstr_t bstrText(str1);
		const char* charText = bstrText;
		*/
		char operationCStr[50] = { 0 };
		sprintf(operationCStr, "%s", address);
		unsigned __int64 addressToJump = 0;
		sscanf(operationCStr, "%I64X", &addressToJump);
		DWORD_PTR startAddress = (DWORD_PTR)(&ProcessInfo::getInstance())->getProcessBaseAddress();
		ProcessInstructionReader* pir = &(ProcessInstructionReader::getInstrance());
		unsigned long long processSize = pir->getProcessSize(startAddress);

		if (addressToJump >= startAddress && addressToJump <= (startAddress + processSize))
		{

			RecognizeFunctionController recognizeFunctionController;
			ProcessFunction* process = recognizeFunctionController.getProcessFunction(operationCStr);
			if (process != NULL)
			{

				char instructionAddress[INSTURCTION_ADDRESS_SIZE];
				int instructionCount = process->getInstructionCount();

				this->listView1->Items->Clear();

				for (int i = 0; i < instructionCount; i++)
				{
					//sprintf(instructionAddress, "0x%I64X", process->instructions[i].offset);
					//ListViewItem^ element = this->listView1->Items->Add(gcnew String(instructionAddress));
					//element->SubItems->Add(gcnew String((char*)process->instructions[i].mnemonic.p));
					//element->SubItems->Add(gcnew String((char*)process->instructions[i].operands.p));
					sprintf(instructionAddress, "0x%I64X", process->instructions->at(i)->getOffset());
					ListViewItem^ element = this->listView1->Items->Add(gcnew String(instructionAddress));
					element->SubItems->Add(gcnew String(process->instructions->at(i)->getMnemonic().c_str()));
					element->SubItems->Add(gcnew String(process->instructions->at(i)->getOperands().c_str()));
				}
			}
			else
			{
				InfoForm^ infoForm = gcnew InfoForm();
				infoForm->setText(std::string("No function at this address!"));
				infoForm->ShowDialog();
				delete infoForm;
			}


		}
		else
		{
			InfoForm^ infoForm = gcnew InfoForm();
			infoForm->setText(std::string("Bad address!"));
			infoForm->ShowDialog();
			delete infoForm;
		}
	}
}

void LowLevelManagerv1::RecognizeFunctionForm::callFunction()
{
	String^ address = this->functionAddressTextBox->Text;

	if (address->Length > 0)
	{
		char operationCStr[50] = { 0 };
		sprintf(operationCStr, "%s", address);
		unsigned __int64 addressToJump = 0;
		sscanf(operationCStr, "%I64X", &addressToJump);
		DWORD_PTR startAddress = (DWORD_PTR)(&ProcessInfo::getInstance())->getProcessBaseAddress();
		ProcessInstructionReader* pir = &(ProcessInstructionReader::getInstrance());
		unsigned long long processSize = pir->getProcessSize(startAddress);

		if (addressToJump >= startAddress && addressToJump <= (startAddress + processSize))
		{
		
			CallFunctionForm^ callFunction = gcnew CallFunctionForm();
			callFunction->setFunctionAddress(operationCStr);
			callFunction->loadProcessParameters();
			callFunction->ShowDialog();
		}
		else
		{
			InfoForm^ infoForm = gcnew InfoForm();
			infoForm->setText(std::string("No function at this address!"));
			infoForm->ShowDialog();
			delete infoForm;
		}

	}
	else
	{
		InfoForm^ infoForm = gcnew InfoForm();
		infoForm->setText(std::string("Bad address!"));
		infoForm->ShowDialog();
		delete infoForm;
	}
}


