#include "InfoForm.h"
#include <string>


void LowLevelManagerv1::InfoForm::setText(std::string text)
{
	std::wstring wide_string(text.begin(), text.end());
	const wchar_t* result = wide_string.c_str();
	this->label1->Text = gcnew String(result);
	//this->richTextBox1->Text = gcnew String(result);

	//this->richTextBox1->SelectAll();
	//this->richTextBox1->SelectionAlignment = System::Windows::Forms::HorizontalAlignment::Center;
	//this->richTextBox1->DeselectAll();


}
