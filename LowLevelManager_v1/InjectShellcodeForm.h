#pragma once

#include <stdio.h>
#include <string>
#include <cstring> 
#include <comdef.h>
#include "MainController.h"
#include "InjectShellcodeController.h"
#include <vcclr.h>


namespace LowLevelManagerv1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for InjectShellcodeForm
	/// </summary>
	public ref class InjectShellcodeForm : public System::Windows::Forms::Form
	{
	public:
		InjectShellcodeForm(void)
		{
			InitializeComponent();

			isButtonClicked = false;
			xButtonClicked = NULL;
			yButtonClicked = NULL;
		}
	public:bool isButtonClicked;
	public:int xButtonClicked;
	public:int yButtonClicked;

	private: System::Windows::Forms::GroupBox^ injectTypeGroup;

	private: System::Windows::Forms::RadioButton^ bytesRadioButton;
	private: System::Windows::Forms::RadioButton^ assemblerRadioButton;

	//methods
	public: void injectShellcode();

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~InjectShellcodeForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ topPanel;
	protected:
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::RichTextBox^ dataTextBox;

	private: System::Windows::Forms::Button^ injectShellcodeButton;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(InjectShellcodeForm::typeid));
			this->topPanel = (gcnew System::Windows::Forms::Panel());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->dataTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->injectShellcodeButton = (gcnew System::Windows::Forms::Button());
			this->injectTypeGroup = (gcnew System::Windows::Forms::GroupBox());
			this->assemblerRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->bytesRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->topPanel->SuspendLayout();
			this->injectTypeGroup->SuspendLayout();
			this->SuspendLayout();
			// 
			// topPanel
			// 
			this->topPanel->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->topPanel->Controls->Add(this->button2);
			this->topPanel->Controls->Add(this->button1);
			this->topPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->topPanel->Location = System::Drawing::Point(0, 0);
			this->topPanel->Name = L"topPanel";
			this->topPanel->Size = System::Drawing::Size(498, 42);
			this->topPanel->TabIndex = 1;
			this->topPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &InjectShellcodeForm::topPanelMouseDown);
			this->topPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &InjectShellcodeForm::topPanelMouseMove);
			this->topPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &InjectShellcodeForm::topPanelMouseUp);
			// 
			// button2
			// 
			this->button2->FlatAppearance->BorderSize = 0;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.Image")));
			this->button2->Location = System::Drawing::Point(453, 0);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(45, 42);
			this->button2->TabIndex = 2;
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &InjectShellcodeForm::button2_Click);
			// 
			// button1
			// 
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.Image")));
			this->button1->Location = System::Drawing::Point(523, 0);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(45, 42);
			this->button1->TabIndex = 1;
			this->button1->UseVisualStyleBackColor = true;
			// 
			// dataTextBox
			// 
			this->dataTextBox->Location = System::Drawing::Point(33, 71);
			this->dataTextBox->Name = L"dataTextBox";
			this->dataTextBox->Size = System::Drawing::Size(327, 258);
			this->dataTextBox->TabIndex = 2;
			this->dataTextBox->Text = L"";
			// 
			// injectShellcodeButton
			// 
			this->injectShellcodeButton->Location = System::Drawing::Point(380, 349);
			this->injectShellcodeButton->Name = L"injectShellcodeButton";
			this->injectShellcodeButton->Size = System::Drawing::Size(106, 33);
			this->injectShellcodeButton->TabIndex = 3;
			this->injectShellcodeButton->Text = L"Inject";
			this->injectShellcodeButton->UseVisualStyleBackColor = true;
			this->injectShellcodeButton->Click += gcnew System::EventHandler(this, &InjectShellcodeForm::injectShellcodeButton_Click);
			// 
			// injectTypeGroup
			// 
			this->injectTypeGroup->Controls->Add(this->assemblerRadioButton);
			this->injectTypeGroup->Controls->Add(this->bytesRadioButton);
			this->injectTypeGroup->Location = System::Drawing::Point(380, 71);
			this->injectTypeGroup->Name = L"injectTypeGroup";
			this->injectTypeGroup->Size = System::Drawing::Size(106, 258);
			this->injectTypeGroup->TabIndex = 4;
			this->injectTypeGroup->TabStop = false;
			this->injectTypeGroup->Text = L"Inject Type";
			// 
			// assemblerRadioButton
			// 
			this->assemblerRadioButton->AutoSize = true;
			this->assemblerRadioButton->Location = System::Drawing::Point(6, 43);
			this->assemblerRadioButton->Name = L"assemblerRadioButton";
			this->assemblerRadioButton->Size = System::Drawing::Size(73, 17);
			this->assemblerRadioButton->TabIndex = 1;
			this->assemblerRadioButton->TabStop = true;
			this->assemblerRadioButton->Text = L"Assembler";
			this->assemblerRadioButton->UseVisualStyleBackColor = true;
			// 
			// bytesRadioButton
			// 
			this->bytesRadioButton->AutoSize = true;
			this->bytesRadioButton->Location = System::Drawing::Point(6, 19);
			this->bytesRadioButton->Name = L"bytesRadioButton";
			this->bytesRadioButton->Size = System::Drawing::Size(51, 17);
			this->bytesRadioButton->TabIndex = 0;
			this->bytesRadioButton->TabStop = true;
			this->bytesRadioButton->Text = L"Bytes";
			this->bytesRadioButton->UseVisualStyleBackColor = true;
			// 
			// InjectShellcodeForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(498, 406);
			this->Controls->Add(this->injectTypeGroup);
			this->Controls->Add(this->injectShellcodeButton);
			this->Controls->Add(this->dataTextBox);
			this->Controls->Add(this->topPanel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"InjectShellcodeForm";
			this->Text = L"InjectShellcodeForm";
			this->topPanel->ResumeLayout(false);
			this->injectTypeGroup->ResumeLayout(false);
			this->injectTypeGroup->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		this->Close();
	}

	private: System::Void topPanelMouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		this->isButtonClicked = false;
		this->xButtonClicked = NULL;
		this->yButtonClicked = NULL;
	}

	private: System::Void topPanelMouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		this->isButtonClicked = true;
		this->xButtonClicked = e->X;
		this->yButtonClicked = e->Y;
	}

	private: System::Void topPanelMouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (this->isButtonClicked == true)
		{
			int xDiffrence = e->X - this->xButtonClicked;
			int yDiffrence = e->Y - this->yButtonClicked;
			Point position = this->Location;
			this->Location = Point(position.X + xDiffrence, position.Y + yDiffrence);
		}
	}

	private: System::Void injectShellcodeButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		injectShellcode();
	}
};
}
