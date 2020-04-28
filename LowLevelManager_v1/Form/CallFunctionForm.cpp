#include "CallFunctionForm.h"
#include "Controller/CallFunctionController.h"
#include "Service/MnemonicsX64.h"
#include "InfoForm.h"
#include <string> 


#define VALUE_COLUMN_INDEX 4

void LowLevelManagerv1::CallFunctionForm::loadProcessParameters()
{
	
	CallFunctionController callFunctionController;
	std::vector<ProcessFunction::FunctionParamter*>* parameters = callFunctionController.getFunctionParameters(this->functionAddress);


	if (parameters != NULL)
	{

		std::string registerMnemonic;


		MnemonicsX64* mnemonicInstance = &(MnemonicsX64::getInstance());


		if (parameters->size() > 0)
		{
		
			dataGridView1->Rows->Add(parameters->size());

			for (int i = 0; i < parameters->size(); i++)
			{
				dataGridView1->Rows[i]->Cells[0]->Value = gcnew String(std::to_string(i).c_str());
				dataGridView1->Rows[i]->Cells[1]->Value = gcnew String(gcnew String(ProcessFunction::parametTypeMnemonic[parameters->at(i)->type]));
				dataGridView1->Rows[i]->Cells[2]->Value = gcnew String(std::to_string(parameters->at(i)->size).c_str());


		//	if (parameters->at(i)->type == ProcessFunction::REGISTER)
		//	{
					int reason = mnemonicInstance->getRegisterByIndex(parameters->at(i)->registerIndex, &registerMnemonic);
					if (reason != -1)
					{
						dataGridView1->Rows[i]->Cells[3]->Value = gcnew String(registerMnemonic.c_str());
					}
					else
					{
						dataGridView1->Rows[i]->Cells[3]->Value = gcnew String("STACK");
					}
		
					dataGridView1->Rows[i]->Cells[4]->Value = gcnew String("");
			}
			InfoForm^ infoForm = gcnew InfoForm();
			infoForm->setText(std::string("Recognize function with ")+ std::to_string(parameters->size())+" parameters!");
			infoForm->ShowDialog();
			delete infoForm;
		}
		else
		{
			InfoForm^ infoForm = gcnew InfoForm();
			infoForm->setText(std::string("Recognize function without parameters!"));
			infoForm->ShowDialog();
			delete infoForm;
		}
		
	}
	else
	{
		InfoForm^ infoForm = gcnew InfoForm();
		infoForm->setText(std::string("Error! No recognize convention!"));
		infoForm->ShowDialog();
		delete infoForm;
	}
	

}

void LowLevelManagerv1::CallFunctionForm::callFunction()
{
	CallFunctionController callFunctionController;
	std::vector<ProcessFunction::FunctionParamter*>* parameters = callFunctionController.getFunctionParameters(this->functionAddress);
	if (parameters != NULL)
	{
		if (parameters->size() > 0)
		{
			int rowCount = dataGridView1->RowCount;
			if (rowCount > 0)
			{
				bool emptyFiled = false;
				for (int i = 0; i < parameters->size(); i++)
				{
					
					
					System::Windows::Forms::DataGridViewCell^ parameter = dataGridView1->Rows[i]->Cells[VALUE_COLUMN_INDEX];
					if (parameter->Value == nullptr)
					{
						InfoForm^ infoForm = gcnew InfoForm();
						infoForm->setText(std::string("Fill every fields!"));
						infoForm->ShowDialog();
						delete infoForm;
						emptyFiled = true;
						break;
					}
					
					String^ value = parameter->Value->ToString();
					if (value->Length == 0)
					{
						InfoForm^ infoForm = gcnew InfoForm();
						infoForm->setText(std::string("Fill every fields!"));
						infoForm->ShowDialog();
						delete infoForm;

						emptyFiled = true;
						break;
					}
					else
					{
						pin_ptr<const wchar_t> str1 = PtrToStringChars(value);
						_bstr_t bstrText(str1);
						const char* charText = bstrText;
						std::string stringValue(charText);
						if (stringValue.find(".") == std::string::npos)
						{
							int intValue = std::stoi(stringValue);
							parameters->at(i)->value = intValue;
						}
						else
						{
							float floatValue = std::stof(stringValue);
							parameters->at(i)->value = floatValue;
						}
					}
				}

				if (emptyFiled == false)
				{
					int status = callFunctionController.callFunction(parameters,this->functionAddress);
					if (status == 1)
					{
						InfoForm^ infoForm = gcnew InfoForm();
						infoForm->setText(std::string("Success!"));
						infoForm->ShowDialog();
						delete infoForm;
					}
					else
					{
						InfoForm^ infoForm = gcnew InfoForm();
						infoForm->setText(std::string("Error! No recognize convention!"));
						infoForm->ShowDialog();
						delete infoForm;
					}
				}

			}
		
		}
		else
		{
			int status = callFunctionController.callFunction(parameters, this->functionAddress);
			if (status == 1)
			{
				InfoForm^ infoForm = gcnew InfoForm();
				infoForm->setText(std::string("Success!"));
				infoForm->ShowDialog();
				delete infoForm;
			}
			else
			{
				InfoForm^ infoForm = gcnew InfoForm();
				infoForm->setText(std::string("Error! No recognize convention!"));
				infoForm->ShowDialog();
				delete infoForm;
			}
		}

		
	}
	else
	{
		InfoForm^ infoForm = gcnew InfoForm();
		infoForm->setText(std::string("Recognize parameters error!"));
		infoForm->ShowDialog();
		delete infoForm;
	}

}

void LowLevelManagerv1::CallFunctionForm::setFunctionAddress(const char* functionAddress)
{
	this->functionAddress = functionAddress;
}
