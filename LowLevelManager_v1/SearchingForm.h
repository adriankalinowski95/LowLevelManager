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
	/// Summary for SearchingForm
	/// </summary>
	public ref class SearchingForm : public System::Windows::Forms::Form
	{
	public:
		SearchingForm(void)
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
		~SearchingForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ closeButton;
	protected:

	protected:
	private: System::Windows::Forms::Panel^ topPanel;



	private: System::Windows::Forms::Button^ searchButton;
	private: System::Windows::Forms::TextBox^ addressTextBox;


	private: System::Windows::Forms::Button^ jumpButton;
	private: System::Windows::Forms::TextBox^ instructionTextBox;
	private: System::Windows::Forms::TextBox^ operationTextBox;



	private: System::Windows::Forms::GroupBox^ searchGroupBox;


	private: System::Windows::Forms::RadioButton^ operationRadioButton;

	private: System::Windows::Forms::RadioButton^ instructionRadioButton;

	private: System::Windows::Forms::RadioButton^ addressRadioButton;
	private: System::Windows::Forms::ListView^ listView1;

	private: System::Windows::Forms::VScrollBar^ vScrollBar1;

	//custom fileds
	public:bool isButtonClicked;
	public:int xButtonClicked;
	private: System::Windows::Forms::ColumnHeader^ columnHeader1;
	public:
	private: System::Windows::Forms::ColumnHeader^ columnHeader2;
	private: System::Windows::Forms::ColumnHeader^ columnHeader3;
	private: System::Windows::Forms::ColumnHeader^ columnHeader4;
	public:int yButtonClicked;

	//custom methods


	private:void search(int startIndex);
	private:void cleanList();
	private:void scrollValueChanged();


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(SearchingForm::typeid));
			this->closeButton = (gcnew System::Windows::Forms::Button());
			this->topPanel = (gcnew System::Windows::Forms::Panel());
			this->searchButton = (gcnew System::Windows::Forms::Button());
			this->addressTextBox = (gcnew System::Windows::Forms::TextBox());
			this->jumpButton = (gcnew System::Windows::Forms::Button());
			this->instructionTextBox = (gcnew System::Windows::Forms::TextBox());
			this->operationTextBox = (gcnew System::Windows::Forms::TextBox());
			this->searchGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->operationRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->instructionRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->addressRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->vScrollBar1 = (gcnew System::Windows::Forms::VScrollBar());
			this->topPanel->SuspendLayout();
			this->searchGroupBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// closeButton
			// 
			this->closeButton->FlatAppearance->BorderSize = 0;
			this->closeButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->closeButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"closeButton.Image")));
			this->closeButton->Location = System::Drawing::Point(515, 0);
			this->closeButton->Name = L"closeButton";
			this->closeButton->Size = System::Drawing::Size(45, 42);
			this->closeButton->TabIndex = 1;
			this->closeButton->UseVisualStyleBackColor = true;
			this->closeButton->Click += gcnew System::EventHandler(this, &SearchingForm::closeButton_Click);
			// 
			// topPanel
			// 
			this->topPanel->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->topPanel->Controls->Add(this->closeButton);
			this->topPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->topPanel->Location = System::Drawing::Point(0, 0);
			this->topPanel->Name = L"topPanel";
			this->topPanel->Size = System::Drawing::Size(560, 42);
			this->topPanel->TabIndex = 1;
			this->topPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SearchingForm::topPanelMouseDown);
			this->topPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &SearchingForm::topPanelMouseMove);
			this->topPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &SearchingForm::topPanelMouseUp);
			// 
			// searchButton
			// 
			this->searchButton->Location = System::Drawing::Point(450, 331);
			this->searchButton->Name = L"searchButton";
			this->searchButton->Size = System::Drawing::Size(98, 23);
			this->searchButton->TabIndex = 2;
			this->searchButton->Text = L"Search";
			this->searchButton->UseVisualStyleBackColor = true;
			this->searchButton->Click += gcnew System::EventHandler(this, &SearchingForm::searchButton_Click);
			// 
			// addressTextBox
			// 
			this->addressTextBox->ForeColor = System::Drawing::SystemColors::GrayText;
			this->addressTextBox->Location = System::Drawing::Point(36, 69);
			this->addressTextBox->Name = L"addressTextBox";
			this->addressTextBox->Size = System::Drawing::Size(399, 20);
			this->addressTextBox->TabIndex = 3;
			this->addressTextBox->Text = L"Address...";
			this->addressTextBox->Enter += gcnew System::EventHandler(this, &SearchingForm::addressTextBox_Enter);
			this->addressTextBox->Leave += gcnew System::EventHandler(this, &SearchingForm::addressTextBox_Leave);
			// 
			// jumpButton
			// 
			this->jumpButton->Location = System::Drawing::Point(450, 360);
			this->jumpButton->Name = L"jumpButton";
			this->jumpButton->Size = System::Drawing::Size(98, 23);
			this->jumpButton->TabIndex = 4;
			this->jumpButton->Text = L"Jump";
			this->jumpButton->UseVisualStyleBackColor = true;
			this->jumpButton->Click += gcnew System::EventHandler(this, &SearchingForm::jumpButton_Click);
			// 
			// instructionTextBox
			// 
			this->instructionTextBox->ForeColor = System::Drawing::SystemColors::GrayText;
			this->instructionTextBox->Location = System::Drawing::Point(36, 98);
			this->instructionTextBox->Name = L"instructionTextBox";
			this->instructionTextBox->Size = System::Drawing::Size(399, 20);
			this->instructionTextBox->TabIndex = 5;
			this->instructionTextBox->Text = L"Instruction...";
			this->instructionTextBox->Enter += gcnew System::EventHandler(this, &SearchingForm::instructionTextBox_Enter);
			this->instructionTextBox->Leave += gcnew System::EventHandler(this, &SearchingForm::instructionTextBox_Leave);
			// 
			// operationTextBox
			// 
			this->operationTextBox->ForeColor = System::Drawing::SystemColors::GrayText;
			this->operationTextBox->Location = System::Drawing::Point(36, 124);
			this->operationTextBox->Name = L"operationTextBox";
			this->operationTextBox->Size = System::Drawing::Size(399, 20);
			this->operationTextBox->TabIndex = 6;
			this->operationTextBox->Text = L"Operation...";
			this->operationTextBox->Enter += gcnew System::EventHandler(this, &SearchingForm::operationTextBox_Enter);
			this->operationTextBox->Leave += gcnew System::EventHandler(this, &SearchingForm::operationTextBox_Leave);
			// 
			// searchGroupBox
			// 
			this->searchGroupBox->Controls->Add(this->operationRadioButton);
			this->searchGroupBox->Controls->Add(this->instructionRadioButton);
			this->searchGroupBox->Controls->Add(this->addressRadioButton);
			this->searchGroupBox->Location = System::Drawing::Point(450, 69);
			this->searchGroupBox->Name = L"searchGroupBox";
			this->searchGroupBox->Size = System::Drawing::Size(98, 94);
			this->searchGroupBox->TabIndex = 7;
			this->searchGroupBox->TabStop = false;
			this->searchGroupBox->Text = L"Search";
			// 
			// operationRadioButton
			// 
			this->operationRadioButton->AutoSize = true;
			this->operationRadioButton->Location = System::Drawing::Point(7, 68);
			this->operationRadioButton->Name = L"operationRadioButton";
			this->operationRadioButton->Size = System::Drawing::Size(71, 17);
			this->operationRadioButton->TabIndex = 2;
			this->operationRadioButton->TabStop = true;
			this->operationRadioButton->Text = L"Operation";
			this->operationRadioButton->UseVisualStyleBackColor = true;
			// 
			// instructionRadioButton
			// 
			this->instructionRadioButton->AutoSize = true;
			this->instructionRadioButton->Location = System::Drawing::Point(7, 44);
			this->instructionRadioButton->Name = L"instructionRadioButton";
			this->instructionRadioButton->Size = System::Drawing::Size(74, 17);
			this->instructionRadioButton->TabIndex = 1;
			this->instructionRadioButton->TabStop = true;
			this->instructionRadioButton->Text = L"Instruction";
			this->instructionRadioButton->UseVisualStyleBackColor = true;
			// 
			// addressRadioButton
			// 
			this->addressRadioButton->AutoSize = true;
			this->addressRadioButton->Location = System::Drawing::Point(7, 20);
			this->addressRadioButton->Name = L"addressRadioButton";
			this->addressRadioButton->Size = System::Drawing::Size(63, 17);
			this->addressRadioButton->TabIndex = 0;
			this->addressRadioButton->TabStop = true;
			this->addressRadioButton->Text = L"Address";
			this->addressRadioButton->UseVisualStyleBackColor = true;
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
			this->listView1->Location = System::Drawing::Point(36, 150);
			this->listView1->Name = L"listView1";
			this->listView1->Scrollable = false;
			this->listView1->Size = System::Drawing::Size(379, 233);
			this->listView1->TabIndex = 8;
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
			this->columnHeader3->Width = 136;
			// 
			// columnHeader4
			// 
			this->columnHeader4->Text = L"Comment";
			// 
			// vScrollBar1
			// 
			this->vScrollBar1->LargeChange = 1;
			this->vScrollBar1->Location = System::Drawing::Point(418, 150);
			this->vScrollBar1->Maximum = 0;
			this->vScrollBar1->Name = L"vScrollBar1";
			this->vScrollBar1->Size = System::Drawing::Size(17, 236);
			this->vScrollBar1->TabIndex = 10;
			this->vScrollBar1->ValueChanged += gcnew System::EventHandler(this, &SearchingForm::vScrollBar1_ValueChanged);
			// 
			// SearchingForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(560, 395);
			this->Controls->Add(this->vScrollBar1);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->searchGroupBox);
			this->Controls->Add(this->operationTextBox);
			this->Controls->Add(this->instructionTextBox);
			this->Controls->Add(this->jumpButton);
			this->Controls->Add(this->addressTextBox);
			this->Controls->Add(this->searchButton);
			this->Controls->Add(this->topPanel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"SearchingForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"SearchingForm";
			this->topPanel->ResumeLayout(false);
			this->searchGroupBox->ResumeLayout(false);
			this->searchGroupBox->PerformLayout();
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
#pragma endregion
	private: System::Void addressTextBox_Enter(System::Object^ sender, System::EventArgs^ e) 
	{
		this->addressTextBox->Text = "";
		this->addressTextBox->ForeColor = System::Drawing::Color::Black;
	}
private: System::Void addressTextBox_Leave(System::Object^ sender, System::EventArgs^ e) 
{
	if (!(this->addressTextBox->Text->Length > 0))
	{
		this->addressTextBox->Text = "Address...";
		this->addressTextBox->ForeColor = System::Drawing::Color::Gray;
	}
}
private: System::Void closeButton_Click(System::Object^ sender, System::EventArgs^ e) 
{
	this->Close();
}
private: System::Void instructionTextBox_Enter(System::Object^ sender, System::EventArgs^ e) 
{
	this->instructionTextBox->Text = "";
	this->instructionTextBox->ForeColor = System::Drawing::Color::Black;
}
private: System::Void instructionTextBox_Leave(System::Object^ sender, System::EventArgs^ e)
{
	if (!(this->instructionTextBox->Text->Length > 0))
	{
		this->instructionTextBox->Text = "Instruction...";
		this->instructionTextBox->ForeColor = System::Drawing::Color::Gray;
	}
}
private: System::Void operationTextBox_Enter(System::Object^ sender, System::EventArgs^ e) 
{
	this->operationTextBox->Text = "";
	this->operationTextBox->ForeColor = System::Drawing::Color::Black;
}
private: System::Void operationTextBox_Leave(System::Object^ sender, System::EventArgs^ e) 
{
	if (!(this->operationTextBox->Text->Length > 0))
	{
		this->operationTextBox->Text = "Operation...";
		this->operationTextBox->ForeColor = System::Drawing::Color::Gray;
	}
}

private: System::Void searchButton_Click(System::Object^ sender, System::EventArgs^ e) 
{
	this->search(0);

}
private: System::Void jumpButton_Click(System::Object^ sender, System::EventArgs^ e) {
}

private: System::Void vScrollBar1_ValueChanged(System::Object^ sender, System::EventArgs^ e) 
{
	this->scrollValueChanged();
}
};
}
