#include "InjectShellcodeForm.h"
#include "InfoForm.h"
using namespace System;
using namespace System::Windows::Forms;

void LowLevelManagerv1::InjectShellcodeForm::injectShellcode() 
{
	if (this->bytesRadioButton->Checked)
	{

		String^ text = this->dataTextBox->Text;
		pin_ptr<const wchar_t> str1 = PtrToStringChars(text);
		_bstr_t bstrText(str1);
		const char* charText = bstrText;

		if (strlen(charText) > 0)
		{
			InjectShellcodeController injectShellcodeController;
			injectShellcodeController.injectBytesShellcode(charText);
		}
		
	}
	if (this->assemblerRadioButton->Checked)
	{
		String^ text = this->dataTextBox->Text;
		pin_ptr<const wchar_t> str1 = PtrToStringChars(text);
		_bstr_t bstrText(str1);
		const char* charText = bstrText;

		if (strlen(charText) > 0)
		{
			InjectShellcodeController injectShellcodeController;
			bool status = injectShellcodeController.injectAsmShellcode(charText);

			if (status == true)
			{
				InfoForm^ infoForm = gcnew InfoForm();
				infoForm->setText(std::string("Success!"));
				infoForm->ShowDialog();
				delete infoForm;
			}
			else
			{
				InfoForm^ infoForm = gcnew InfoForm();
				infoForm->setText(std::string("Something wrong!"));
				infoForm->ShowDialog();
				delete infoForm;
			}

		}
	}
}