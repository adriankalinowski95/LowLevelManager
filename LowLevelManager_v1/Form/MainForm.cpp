#include "MainForm.h"
#include "ProcessDataAccess/ProcessInstructionReader.h"
#include "InfoForm.h"

#define MAX_INSTRUCTIONS (2000)
#define BUFFER_SIZE 8000
#define INSTURCTION_ADDRESS_SIZE 200
#define ITEMS_IN_LIST_VIEW 16
using namespace System;
using namespace System::Windows::Forms;


[STAThreadAttribute]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	LowLevelManagerv1::MainForm form;
	Application::Run(% form);
}



void LowLevelManagerv1::MainForm::callbackC(String^ str)
{
	throw gcnew System::NotImplementedException();
}

MainController* LowLevelManagerv1::MainForm::getMainController()
{
	return this->mainController;
}

void LowLevelManagerv1::MainForm::setProcessName(const char* newProcessName)
{
	System::String^ stringNewProcessName = gcnew String(newProcessName);
	this->processName->Text = stringNewProcessName;
}
void LowLevelManagerv1::MainForm::loadProcessInstructions()
{
	
	/*
	DWORD_PTR startAddress = (DWORD_PTR)this->mainController->getProcessInformation()->getProcessBaseAddress();
	unsigned long offset = 0;

	_DecodedInst decodedInstructions[MAX_INSTRUCTIONS];
	int readedInstructions;
	_DecodedInst* decodeInstructionPtr = decodedInstructions;
	char instructionAddress[INSTURCTION_ADDRESS_SIZE];
	char instructionMnemonic[INSTURCTION_ADDRESS_SIZE];
	readedInstructions = this->mainController->getInstructions((LPVOID)(startAddress), decodedInstructions, BUFFER_SIZE);
	if (ITEMS_IN_LIST_VIEW <= (readedInstructions - 1))
	{
		for (int i = 0; i < ITEMS_IN_LIST_VIEW; i++)
		{
			sprintf(instructionAddress, "0x%I64X", decodedInstructions[i].offset);
			ListViewItem^ element = this->listView1->Items->Add(gcnew String(instructionAddress));
			element->SubItems->Add(gcnew String((char*)decodedInstructions[i].mnemonic.p));
			element->SubItems->Add(gcnew String((char*)decodedInstructions[i].operands.p));
		}
	}
	//	this->vScrollBar1->Maximum = this->mainController->getPEReader()->getProcessInstructionsCount((LPCVOID)startAddress);
	*/

	DWORD_PTR startAddress = (DWORD_PTR)this->mainController->getProcessInformation()->getProcessBaseAddress();
	ProcessInstructionReader* pir = &(ProcessInstructionReader::getInstrance());
	std::vector<AssemblerInstruction*> instructions;

	int success = pir->getInstructionByIndex(startAddress,0, ITEMS_IN_LIST_VIEW,instructions);

	if (instructions.size() >= ITEMS_IN_LIST_VIEW && success == 1)
	{
		for (int i = 0; i < instructions.size(); i++)
		{
			ListViewItem^ element = this->listView1->Items->Add(gcnew String(instructions.at(i)->getOffsetString().c_str()));
			element->SubItems->Add(gcnew String(instructions.at(i)->getMnemonic().c_str()));
			element->SubItems->Add(gcnew String(instructions.at(i)->getOperands().c_str()));
		}

		while (!instructions.empty()) {
			delete instructions.back();
			instructions.pop_back();
		}
	}

	success = pir->getProcessInstructionCount(startAddress);
	if (success != -1)
		this->vScrollBar1->Maximum = success;

	processName->Text = gcnew String(this->mainController->getInjector()->getInjectedProcessName());

}

void LowLevelManagerv1::MainForm::cleanListView() 
{
	this->listView1->Items->Clear();
}

void LowLevelManagerv1::MainForm::loadProcessInstructionsByIndex(unsigned long index)
{
	/*
	_DecodedInst decodedInstructions[ITEMS_IN_LIST_VIEW];
	int readedInstructions;
	char instructionAddress[INSTURCTION_ADDRESS_SIZE];
	char instructionMnemonic[INSTURCTION_ADDRESS_SIZE];

	DWORD_PTR startAddress = (DWORD_PTR)this->mainController->getProcessInformation()->getProcessBaseAddress();

	readedInstructions = this->mainController->getInstructionsByIndex((LPVOID)(startAddress), decodedInstructions,index, ITEMS_IN_LIST_VIEW);

	if (ITEMS_IN_LIST_VIEW <= readedInstructions)
	{
		this->cleanListView();
		for (int i = 0; i < ITEMS_IN_LIST_VIEW; i++)
		{
			sprintf(instructionAddress, "0x%I64X", decodedInstructions[i].offset);
			ListViewItem^ element = this->listView1->Items->Add(gcnew String(instructionAddress));
			element->SubItems->Add(gcnew String((char*)decodedInstructions[i].mnemonic.p));
			element->SubItems->Add(gcnew String((char*)decodedInstructions[i].operands.p));

		}
	}
	*/

	DWORD_PTR startAddress = (DWORD_PTR)this->mainController->getProcessInformation()->getProcessBaseAddress();
	ProcessInstructionReader* pir = &(ProcessInstructionReader::getInstrance());
	std::vector<AssemblerInstruction*> instructions;

	int success = pir->getInstructionByIndex(startAddress, index, ITEMS_IN_LIST_VIEW, instructions);

	if (instructions.size() >= ITEMS_IN_LIST_VIEW && success == 1)
	{
		this->cleanListView();
		for (int i = 0; i < instructions.size(); i++)
		{
			ListViewItem^ element = this->listView1->Items->Add(gcnew String(instructions.at(i)->getOffsetString().c_str()));
			element->SubItems->Add(gcnew String(instructions.at(i)->getMnemonic().c_str()));
			element->SubItems->Add(gcnew String(instructions.at(i)->getOperands().c_str()));
		}

		while (!instructions.empty()) {
			delete instructions.back();
			instructions.pop_back();
		}
	}
}


void LowLevelManagerv1::MainForm::jumpToAddress(String^ operation)
{
	char operationCStr[50] = { 0 };
	if (operation->Length < sizeof(operationCStr))
	{
		
		sprintf(operationCStr, "%s", operation);
		unsigned __int64 jumpAddress = 0;
		sscanf(operationCStr, "%I64X", &jumpAddress);
		DWORD_PTR startAddress = (DWORD_PTR)this->mainController->getProcessInformation()->getProcessBaseAddress();
		ProcessInstructionReader* pir = &(ProcessInstructionReader::getInstrance());
		unsigned long long processSize = pir->getProcessSize(startAddress);

		if (jumpAddress != 0 && jumpAddress >= startAddress && jumpAddress <= (processSize+startAddress))
		{
			/*
			_DecodedInst decodedInstructions[MAX_INSTRUCTIONS];
			int readedInstructions;
			char instructionAddress[INSTURCTION_ADDRESS_SIZE];
			char instructionMnemonic[INSTURCTION_ADDRESS_SIZE];

			readedInstructions = this->mainController->getInstructions((LPCVOID)jumpAddress, decodedInstructions, BUFFER_SIZE);

			if (ITEMS_IN_LIST_VIEW <= (readedInstructions - 1))
			{
				this->cleanListView();
				for (int i = 0; i < ITEMS_IN_LIST_VIEW; i++)
				{
					sprintf(instructionAddress, "0x%I64X", decodedInstructions[i].offset);
					ListViewItem^ element = this->listView1->Items->Add(gcnew String(instructionAddress));
					element->SubItems->Add(gcnew String((char*)decodedInstructions[i].mnemonic.p));
					element->SubItems->Add(gcnew String((char*)decodedInstructions[i].operands.p));

				}
			}
			unsigned long instructionIndex = this->mainController->getInstructionIndex((LPCVOID)startAddress, (LPCVOID)jumpAddress);
			
			if (instructionIndex != -1)
			{
				this->vScrollBar1->Value = instructionIndex;
			}
			*/

			ProcessInstructionReader* pir = &(ProcessInstructionReader::getInstrance());
			std::vector<AssemblerInstruction*> instructions;

			int success = pir->getInstructionByAddress(jumpAddress, ITEMS_IN_LIST_VIEW, instructions);

			if (instructions.size() >= ITEMS_IN_LIST_VIEW && success == 1)
			{
				this->cleanListView();
				for (int i = 0; i < instructions.size(); i++)
				{
					ListViewItem^ element = this->listView1->Items->Add(gcnew String(instructions.at(i)->getOffsetString().c_str()));
					element->SubItems->Add(gcnew String(instructions.at(i)->getMnemonic().c_str()));
					element->SubItems->Add(gcnew String(instructions.at(i)->getOperands().c_str()));
				}

				while (!instructions.empty()) {
					delete instructions.back();
					instructions.pop_back();
				}

				unsigned long instructionIndex = pir->getInstructionIndex(startAddress,jumpAddress);

				if (instructionIndex != -1)
				{
					this->vScrollBar1->Value = instructionIndex;
				}

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

