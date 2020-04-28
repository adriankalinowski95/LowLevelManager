#include "SearchingForm.h"
#include "Controller/SearchSignatureController.h"
#include "ProcessDataAccess/ProcessInstructionReader.h"
#include "Service/ProcessInfo.h"
#include "InfoForm.h"
#include <vcclr.h>
#include <comdef.h>


#define MAX_INSTRUCTION_ADDRESS 50
#define MAX_INSTRUCTIONS 9


void LowLevelManagerv1::SearchingForm::search(int startIndex)
{

	if (this->addressRadioButton->Checked == true)
	{
		char operationCStr[50] = { 0 };


		if (this->addressTextBox->Text->Length < sizeof(operationCStr))
		{
			sprintf(operationCStr, "%s", addressTextBox->Text);
			unsigned __int64 searchAddress = 0;
			sscanf(operationCStr, "%I64X", &searchAddress);
			if (strlen(operationCStr) > 0)
			{
				/*
				_DecodedInst decodedInstruction;
				SearchSignatureController searchSignatureController;
				int recognizeInstructions = searchSignatureController.getInstructionByAddress(searchAddress,&decodedInstruction);
				char instructionAddress[MAX_INSTRUCTION_ADDRESS];
				if (recognizeInstructions == 1)
				{
					this->cleanList();
					sprintf(instructionAddress, "0x%I64X", decodedInstruction.offset);
					ListViewItem^ element = this->listView1->Items->Add(gcnew String(instructionAddress));
					element->SubItems->Add(gcnew String((char*)decodedInstruction.mnemonic.p));
					element->SubItems->Add(gcnew String((char*)decodedInstruction.operands.p));

					this->vScrollBar1->Maximum = 0;
					this->vScrollBar1->Value = 0;
				}
				*/
				DWORD_PTR startAddress = (DWORD_PTR)(&ProcessInfo::getInstance())->getProcessBaseAddress();
				ProcessInstructionReader* pir = &(ProcessInstructionReader::getInstrance());
				unsigned long long processSize = pir->getProcessSize(startAddress);
				if (searchAddress >= startAddress && searchAddress <= (startAddress + processSize))
				{
					AssemblerInstruction* assemblerInstruction;
					int isRecognize = pir->getInstructionByAddress(searchAddress, &assemblerInstruction);

					if (isRecognize == 1)
					{
						this->cleanList();
						ListViewItem^ element = this->listView1->Items->Add(gcnew String(assemblerInstruction->getOffsetString().c_str()));
						element->SubItems->Add(gcnew String(assemblerInstruction->getMnemonic().c_str()));
						element->SubItems->Add(gcnew String(assemblerInstruction->getOperands().c_str()));

						this->vScrollBar1->Maximum = 0;
						this->vScrollBar1->Value = 0;

						delete assemblerInstruction;
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


	}
	if (this->instructionRadioButton->Checked == true)
	{
		String^ text = this->instructionTextBox->Text;
		pin_ptr<const wchar_t> str1 = PtrToStringChars(text);
		_bstr_t bstrText(str1);
		const char* charText = bstrText;
		if (strlen(charText) > 0)
		{
			/*
			_DecodedInst decodedInstruction[MAX_INSTRUCTIONS];
			SearchSignatureController searchSignatureController;
			int recognizeInstructions = searchSignatureController.getByInstruction(startIndex, MAX_INSTRUCTIONS, decodedInstruction, charText);
			char instructionAddress[MAX_INSTRUCTION_ADDRESS];
			if (recognizeInstructions >= MAX_INSTRUCTIONS)
			{
				this->cleanList();
				for (int i = 0; i < recognizeInstructions; i++)
				{
					sprintf(instructionAddress, "0x%I64X", decodedInstruction[i].offset);
					ListViewItem^ element = this->listView1->Items->Add(gcnew String(instructionAddress));
					element->SubItems->Add(gcnew String((char*)decodedInstruction[i].mnemonic.p));
					element->SubItems->Add(gcnew String((char*)decodedInstruction[i].operands.p));
				}
				unsigned long maxinstructions = searchSignatureController.getMaxInstruction(charText);
				this->vScrollBar1->Maximum = maxinstructions - MAX_INSTRUCTIONS;
				this->vScrollBar1->Value = startIndex;
			}
			*/
				ProcessInstructionReader* pir = &(ProcessInstructionReader::getInstrance());
				ProcessInfo* pi = &(ProcessInfo::getInstance());
				DWORD_PTR startAddress = (DWORD_PTR)pi->getProcessBaseAddress();
			
				std::vector<AssemblerInstruction*> instructions;
				int recognizeInstructions = pir->getByInstruction(startAddress, startIndex, MAX_INSTRUCTIONS, instructions, std::string(charText));
				if (recognizeInstructions == 1)
				{
					this->cleanList();
					for (int i = 0; i < instructions.size(); i++)
					{
						ListViewItem^ element = this->listView1->Items->Add(gcnew String(instructions.at(i)->getOffsetString().c_str()));
						element->SubItems->Add(gcnew String(instructions.at(i)->getMnemonic().c_str()));
						element->SubItems->Add(gcnew String(instructions.at(i)->getOperands().c_str()));
					}
					unsigned long maxinstructions = pir->getMaxByInstruction(startAddress, std::string(charText));

					if (maxinstructions > MAX_INSTRUCTIONS)
					{
						this->vScrollBar1->Maximum = maxinstructions;
						this->vScrollBar1->Value = startIndex;
					}
					else
					{
						this->vScrollBar1->Maximum = 0;
						this->vScrollBar1->Value = 0;
					}


					while (!instructions.empty()) {
						delete instructions.back();
						instructions.pop_back();
					}
				}
				else
				{
					InfoForm^ infoForm = gcnew InfoForm();
					infoForm->setText(std::string("No instruction!"));
					infoForm->ShowDialog();
					delete infoForm;
				}
		

		}
	}
	if (this->operationRadioButton->Checked == true)
	{
		String^ text = this->operationTextBox->Text;
		pin_ptr<const wchar_t> str1 = PtrToStringChars(text);
		_bstr_t bstrText(str1);
		const char* charText = bstrText;
		if (strlen(charText) > 0)
		{
			/*
			_DecodedInst decodedInstruction[MAX_INSTRUCTIONS];
			SearchSignatureController searchSignatureController;
			int recognizeInstructions = searchSignatureController.getByOpearnd(startIndex, MAX_INSTRUCTIONS, decodedInstruction, charText);
			char instructionAddress[MAX_INSTRUCTION_ADDRESS];

			this->cleanList();
			for (int i = 0; i < recognizeInstructions; i++)
			{
				sprintf(instructionAddress, "0x%I64X", decodedInstruction[i].offset);
				ListViewItem^ element = this->listView1->Items->Add(gcnew String(instructionAddress));
				element->SubItems->Add(gcnew String((char*)decodedInstruction[i].mnemonic.p));
				element->SubItems->Add(gcnew String((char*)decodedInstruction[i].operands.p));
			}
			unsigned long maxinstructions = searchSignatureController.getMaxOperands(charText);

			if (maxinstructions > MAX_INSTRUCTIONS)
			{
				this->vScrollBar1->Maximum = maxinstructions - MAX_INSTRUCTIONS;
				this->vScrollBar1->Value = startIndex;
			}
			else
			{
				this->vScrollBar1->Maximum = 0;
				this->vScrollBar1->Value = 0;
			}
			*/

			ProcessInstructionReader* pir = &(ProcessInstructionReader::getInstrance());
			ProcessInfo* pi = &(ProcessInfo::getInstance());
			DWORD_PTR startAddress = (DWORD_PTR)pi->getProcessBaseAddress();

			std::vector<AssemblerInstruction*> instructions;
			int recognizeInstructions = pir->getByOperand(startAddress, startIndex, MAX_INSTRUCTIONS, instructions, std::string(charText));

			if (recognizeInstructions == 1)
			{
				this->cleanList();
				for (int i = 0; i < instructions.size(); i++)
				{
					ListViewItem^ element = this->listView1->Items->Add(gcnew String(instructions.at(i)->getOffsetString().c_str()));
					element->SubItems->Add(gcnew String(instructions.at(i)->getMnemonic().c_str()));
					element->SubItems->Add(gcnew String(instructions.at(i)->getOperands().c_str()));
				}
				unsigned long maxinstructions = pir->getMaxByOperand(startAddress, std::string(charText));

				if (maxinstructions > MAX_INSTRUCTIONS)
				{
					this->vScrollBar1->Maximum = maxinstructions;
					this->vScrollBar1->Value = startIndex;
				}
				else
				{
					this->vScrollBar1->Maximum = 0;
					this->vScrollBar1->Value = 0;
				}

				while (!instructions.empty()) {
					delete instructions.back();
					instructions.pop_back();
				}
			}
			else
			{
				InfoForm^ infoForm = gcnew InfoForm();
				infoForm->setText(std::string("No instruction!"));
				infoForm->ShowDialog();
				delete infoForm;
			}
		}
	}
}

void LowLevelManagerv1::SearchingForm::cleanList()
{
	this->listView1->Items->Clear();
}

void LowLevelManagerv1::SearchingForm::scrollValueChanged()
{	
	if (this->vScrollBar1->Value >= 0)
	{
		if (this->vScrollBar1->Maximum > 0 && (this->vScrollBar1->Maximum - MAX_INSTRUCTIONS) > 0)
		{
			this->search(vScrollBar1->Value);
		}
	}
}

