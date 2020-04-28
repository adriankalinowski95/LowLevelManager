#pragma once
#include <stdio.h>
#include "Controller/MainController.h"
#include "Controller/InformationProcessController.h"
namespace LowLevelManagerv1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for InformationForm
	/// </summary>
	public ref class InformationForm : public System::Windows::Forms::Form
	{
	public:
		InformationForm(void)
		{
			InitializeComponent();
			isButtonClicked = false;
			xButtonClicked = NULL;
			yButtonClicked = NULL;
		}

	public:bool isButtonClicked;
	public:int xButtonClicked;
	public:int yButtonClicked;
	private: MainController* mainController;
	private: InformationProcessController * informationProcessController;
	public:void setMainController(MainController* mainController);
	public:void loadProcessInformation();

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~InformationForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ topPanel;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ ProcessName;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ PID;
	protected:

	protected:

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(InformationForm::typeid));
			this->topPanel = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->ProcessName = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->PID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->topPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// topPanel
			// 
			this->topPanel->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->topPanel->Controls->Add(this->button1);
			this->topPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->topPanel->Location = System::Drawing::Point(0, 0);
			this->topPanel->Name = L"topPanel";
			this->topPanel->Size = System::Drawing::Size(568, 42);
			this->topPanel->TabIndex = 0;
			this->topPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &InformationForm::topPanelMouseDown);
			this->topPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &InformationForm::topPanelMouseMove);
			this->topPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &InformationForm::topPanelMouseUp);
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
			this->button1->Click += gcnew System::EventHandler(this, &InformationForm::button1_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView1->ClipboardCopyMode = System::Windows::Forms::DataGridViewClipboardCopyMode::EnableAlwaysIncludeHeaderText;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->ProcessName,
					this->PID
			});
			this->dataGridView1->Location = System::Drawing::Point(32, 70);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowTemplate->ReadOnly = true;
			this->dataGridView1->RowTemplate->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView1->Size = System::Drawing::Size(500, 356);
			this->dataGridView1->TabIndex = 3;
			// 
			// ProcessName
			// 
			this->ProcessName->HeaderText = L"Information";
			this->ProcessName->Name = L"ProcessName";
			this->ProcessName->ReadOnly = true;
			// 
			// PID
			// 
			this->PID->HeaderText = L"Value";
			this->PID->Name = L"PID";
			this->PID->ReadOnly = true;
			// 
			// InformationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(568, 456);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->topPanel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"InformationForm";
			this->Text = L"InformationForm";
			this->topPanel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
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

};
}
