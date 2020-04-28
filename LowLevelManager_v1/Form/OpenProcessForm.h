#pragma once
#include <stdio.h>
#include "Controller/MainController.h"
#include "Controller/OpenProcessController.h"
namespace LowLevelManagerv1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for OpenProcessForm
	/// </summary>
	public ref class OpenProcessForm : public System::Windows::Forms::Form
	{
	public:
	OpenProcessForm(void)
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
	private: OpenProcessController* openProcessController;
	public: void setMainController(MainController* mainController);
	public: void loadProcesses();

	private: System::Windows::Forms::DataGridViewTextBoxColumn^ ProcessName;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ PID;



	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~OpenProcessForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ topPanel;
	protected:

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ selectButton;

	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::Panel^ panel1;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(OpenProcessForm::typeid));
			this->topPanel = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->selectButton = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->ProcessName = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->PID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->topPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// topPanel
			// 
			this->topPanel->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->topPanel->Controls->Add(this->button1);
			this->topPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->topPanel->Location = System::Drawing::Point(5, 5);
			this->topPanel->Name = L"topPanel";
			this->topPanel->Size = System::Drawing::Size(415, 42);
			this->topPanel->TabIndex = 0;
			this->topPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &OpenProcessForm::topPanelMouseDown);
			this->topPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &OpenProcessForm::topPanelMouseMove);
			this->topPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &OpenProcessForm::topPanelMouseUp);
			// 
			// button1
			// 
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.Image")));
			this->button1->Location = System::Drawing::Point(367, 0);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(45, 42);
			this->button1->TabIndex = 0;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &OpenProcessForm::button1_Click);
			// 
			// selectButton
			// 
			this->selectButton->Location = System::Drawing::Point(313, 341);
			this->selectButton->Name = L"selectButton";
			this->selectButton->Size = System::Drawing::Size(75, 36);
			this->selectButton->TabIndex = 1;
			this->selectButton->Text = L"Select";
			this->selectButton->UseVisualStyleBackColor = true;
			this->selectButton->Click += gcnew System::EventHandler(this, &OpenProcessForm::selectButton_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->ProcessName,
					this->PID
			});
			this->dataGridView1->Location = System::Drawing::Point(30, 28);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowTemplate->ReadOnly = true;
			this->dataGridView1->RowTemplate->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView1->Size = System::Drawing::Size(358, 294);
			this->dataGridView1->TabIndex = 2;
			// 
			// ProcessName
			// 
			this->ProcessName->HeaderText = L"Process Name";
			this->ProcessName->Name = L"ProcessName";
			this->ProcessName->ReadOnly = true;
			// 
			// PID
			// 
			this->PID->HeaderText = L"PID";
			this->PID->Name = L"PID";
			this->PID->ReadOnly = true;
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->dataGridView1);
			this->panel1->Controls->Add(this->selectButton);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(5, 47);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(415, 411);
			this->panel1->TabIndex = 3;
			// 
			// OpenProcessForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(425, 463);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->topPanel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"OpenProcessForm";
			this->Padding = System::Windows::Forms::Padding(5);
			this->Text = L"OpenProcessForm";
			this->Load += gcnew System::EventHandler(this, &OpenProcessForm::OpenProcessForm_Load);
			this->topPanel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void OpenProcessForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
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
	private: System::Void selectButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (this->dataGridView1->CurrentRow->Index >= 0)
		{
			this->openProcessController->selectProcess(this->dataGridView1->CurrentRow->Index);
			this->Close();
		}
	}
};
}
