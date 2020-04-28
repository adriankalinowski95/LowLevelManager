#pragma once
#include <stdio.h>

namespace LowLevelManagerv1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for RecognizeFunctionForm
	/// </summary>
	public ref class RecognizeFunctionForm : public System::Windows::Forms::Form
	{
	public:
		RecognizeFunctionForm(void)
		{
			InitializeComponent();
			isButtonClicked = false;
			xButtonClicked = NULL;
			yButtonClicked = NULL;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~RecognizeFunctionForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ closeButton;
	protected:
	private: System::Windows::Forms::Panel^ topPanel;
	



	//custom fileds
	public:bool isButtonClicked;
	public:int xButtonClicked;
	public:int yButtonClicked;
	private: System::Windows::Forms::Button^ callFunctionButton;
	
	//custom methods
	public: void loadFunction();
	public: void callFunction();

	public:
	private: System::Windows::Forms::ListView^ listView1;
	private: System::Windows::Forms::ColumnHeader^ columnHeader1;
	private: System::Windows::Forms::ColumnHeader^ columnHeader2;
	private: System::Windows::Forms::ColumnHeader^ columnHeader3;
	private: System::Windows::Forms::ColumnHeader^ columnHeader4;
	private: System::Windows::Forms::TextBox^ functionAddressTextBox;

	private: System::Windows::Forms::Button^ recognizeButton;


	


	//private:void search(int startIndex);


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(RecognizeFunctionForm::typeid));
			this->closeButton = (gcnew System::Windows::Forms::Button());
			this->topPanel = (gcnew System::Windows::Forms::Panel());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->functionAddressTextBox = (gcnew System::Windows::Forms::TextBox());
			this->recognizeButton = (gcnew System::Windows::Forms::Button());
			this->callFunctionButton = (gcnew System::Windows::Forms::Button());
			this->topPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// closeButton
			// 
			this->closeButton->FlatAppearance->BorderSize = 0;
			this->closeButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->closeButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"closeButton.Image")));
			this->closeButton->Location = System::Drawing::Point(396, 0);
			this->closeButton->Name = L"closeButton";
			this->closeButton->Size = System::Drawing::Size(45, 42);
			this->closeButton->TabIndex = 1;
			this->closeButton->UseVisualStyleBackColor = true;
			this->closeButton->Click += gcnew System::EventHandler(this, &RecognizeFunctionForm::closeButton_Click);
			// 
			// topPanel
			// 
			this->topPanel->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->topPanel->Controls->Add(this->closeButton);
			this->topPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->topPanel->Location = System::Drawing::Point(0, 0);
			this->topPanel->Name = L"topPanel";
			this->topPanel->Size = System::Drawing::Size(441, 42);
			this->topPanel->TabIndex = 2;
			this->topPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &RecognizeFunctionForm::topPanelMouseDown);
			this->topPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &RecognizeFunctionForm::topPanelMouseMove);
			this->topPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &RecognizeFunctionForm::topPanelMouseUp);
			// 
			// listView1
			// 
			this->listView1->AutoArrange = false;
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {
				this->columnHeader1, this->columnHeader2,
					this->columnHeader3, this->columnHeader4
			});
			this->listView1->Font = (gcnew System::Drawing::Font(L"Arial", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->listView1->FullRowSelect = true;
			this->listView1->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->listView1->HideSelection = false;
			this->listView1->Location = System::Drawing::Point(22, 172);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(399, 196);
			this->listView1->TabIndex = 11;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"Address";
			this->columnHeader1->Width = 110;
			// 
			// columnHeader2
			// 
			this->columnHeader2->Text = L"Instruction";
			this->columnHeader2->Width = 71;
			// 
			// columnHeader3
			// 
			this->columnHeader3->Text = L"Opeartion";
			this->columnHeader3->Width = 133;
			// 
			// columnHeader4
			// 
			this->columnHeader4->Text = L"Comment";
			// 
			// functionAddressTextBox
			// 
			this->functionAddressTextBox->ForeColor = System::Drawing::SystemColors::GrayText;
			this->functionAddressTextBox->Location = System::Drawing::Point(22, 70);
			this->functionAddressTextBox->Name = L"functionAddressTextBox";
			this->functionAddressTextBox->Size = System::Drawing::Size(287, 20);
			this->functionAddressTextBox->TabIndex = 13;
			this->functionAddressTextBox->Text = L"Function address...";
			this->functionAddressTextBox->Enter += gcnew System::EventHandler(this, &RecognizeFunctionForm::functionAddressTextBox_Enter);
			this->functionAddressTextBox->Leave += gcnew System::EventHandler(this, &RecognizeFunctionForm::functionAddressTextBox_Leave);
			// 
			// recognizeButton
			// 
			this->recognizeButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->recognizeButton->Location = System::Drawing::Point(315, 70);
			this->recognizeButton->Name = L"recognizeButton";
			this->recognizeButton->Size = System::Drawing::Size(106, 20);
			this->recognizeButton->TabIndex = 14;
			this->recognizeButton->Text = L"Recognize";
			this->recognizeButton->UseVisualStyleBackColor = true;
			this->recognizeButton->Click += gcnew System::EventHandler(this, &RecognizeFunctionForm::recognizeButton_Click);
			// 
			// callFunctionButton
			// 
			this->callFunctionButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->callFunctionButton->Location = System::Drawing::Point(315, 97);
			this->callFunctionButton->Name = L"callFunctionButton";
			this->callFunctionButton->Size = System::Drawing::Size(106, 21);
			this->callFunctionButton->TabIndex = 15;
			this->callFunctionButton->Text = L"Call function";
			this->callFunctionButton->UseVisualStyleBackColor = true;
			this->callFunctionButton->Click += gcnew System::EventHandler(this, &RecognizeFunctionForm::callFunctionButton_Click);
			// 
			// RecognizeFunctionForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(441, 380);
			this->Controls->Add(this->callFunctionButton);
			this->Controls->Add(this->recognizeButton);
			this->Controls->Add(this->functionAddressTextBox);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->topPanel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"RecognizeFunctionForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"RecognizeFunctionForm";
			this->topPanel->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

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
	private: System::Void closeButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->Close();
	}
#pragma endregion

	private: System::Void functionAddressTextBox_Enter(System::Object^ sender, System::EventArgs^ e) 
	{
		this->functionAddressTextBox->Text = "";
		this->functionAddressTextBox->ForeColor = System::Drawing::Color::Black;
	}
	private: System::Void functionAddressTextBox_Leave(System::Object^ sender, System::EventArgs^ e) 
	{
		if (!(this->functionAddressTextBox->Text->Length > 0))
		{
			this->functionAddressTextBox->Text = "Function address...";
			this->functionAddressTextBox->ForeColor = System::Drawing::Color::Gray;
		}
	}

	private: System::Void recognizeButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		loadFunction();
	}
	private: System::Void callFunctionButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		callFunction();
	}
};
}
