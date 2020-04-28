#pragma once
#include <stdio.h>
#include "Controller/MainController.h"
namespace LowLevelManagerv1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for JumpForm
	/// </summary>
	ref class MainForm;


	public ref class JumpForm : public System::Windows::Forms::Form
	{
		
	public:
		JumpForm(void)
		{
			InitializeComponent();
			isButtonClicked = false;
			xButtonClicked = NULL;
			yButtonClicked = NULL;
		}
	public: bool isButtonClicked;
	public: int xButtonClicked;
	public: void jumpToAddress();
	public: MainForm^ mainForm;
	public: void setMainForm(MainForm^ mainForm);
	private: System::Windows::Forms::Panel^ topPanel;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::TextBox^ jumpAddressEditText;


	private: System::Windows::Forms::Button^ jumpButton;

	public:int yButtonClicked;



	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~JumpForm()
		{
			if (components)
			{
				delete components;
			}
		}

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(JumpForm::typeid));
			this->topPanel = (gcnew System::Windows::Forms::Panel());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->jumpAddressEditText = (gcnew System::Windows::Forms::TextBox());
			this->jumpButton = (gcnew System::Windows::Forms::Button());
			this->topPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// topPanel
			// 
			this->topPanel->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->topPanel->Controls->Add(this->button3);
			this->topPanel->Controls->Add(this->button2);
			this->topPanel->Controls->Add(this->button1);
			this->topPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->topPanel->Location = System::Drawing::Point(0, 0);
			this->topPanel->Name = L"topPanel";
			this->topPanel->Size = System::Drawing::Size(284, 42);
			this->topPanel->TabIndex = 2;
			this->topPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &JumpForm::topPanelMouseDown);
			this->topPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &JumpForm::topPanelMouseMove);
			this->topPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &JumpForm::topPanelMouseUp);
			// 
			// button3
			// 
			this->button3->FlatAppearance->BorderSize = 0;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button3.Image")));
			this->button3->Location = System::Drawing::Point(239, 0);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(45, 42);
			this->button3->TabIndex = 3;
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &JumpForm::button3_Click);
			// 
			// button2
			// 
			this->button2->FlatAppearance->BorderSize = 0;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(453, 0);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(45, 42);
			this->button2->TabIndex = 2;
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &JumpForm::button2_Click);
			// 
			// button1
			// 
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(523, 0);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(45, 42);
			this->button1->TabIndex = 1;
			this->button1->UseVisualStyleBackColor = true;
			// 
			// jumpAddressEditText
			// 
			this->jumpAddressEditText->Location = System::Drawing::Point(43, 84);
			this->jumpAddressEditText->Name = L"jumpAddressEditText";
			this->jumpAddressEditText->Size = System::Drawing::Size(202, 20);
			this->jumpAddressEditText->TabIndex = 3;
			// 
			// jumpButton
			// 
			this->jumpButton->Location = System::Drawing::Point(170, 207);
			this->jumpButton->Name = L"jumpButton";
			this->jumpButton->Size = System::Drawing::Size(75, 23);
			this->jumpButton->TabIndex = 4;
			this->jumpButton->Text = L"Jump";
			this->jumpButton->UseVisualStyleBackColor = true;
			this->jumpButton->Click += gcnew System::EventHandler(this, &JumpForm::jumpButton_Click);
			// 
			// JumpForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->jumpButton);
			this->Controls->Add(this->jumpAddressEditText);
			this->Controls->Add(this->topPanel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"JumpForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"JumpForm";
			this->topPanel->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
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

#pragma endregion
	private: System::Void jumpButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		this->jumpToAddress();
		this->Close();
	}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) 
{
	this->Close();
}
};
}
