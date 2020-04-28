#pragma once
#include <stdio.h>
#include <vcclr.h>
#include <comdef.h>
#define VALUE_COLUMN_INDEX 4

namespace LowLevelManagerv1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for CallFunctionForm
	/// </summary>

	public ref class CallFunctionForm : public System::Windows::Forms::Form
	{
	public:
		CallFunctionForm(void)
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
		~CallFunctionForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ closeButton;
	protected:
	private: System::Windows::Forms::Panel^ topPanel;
	///deklaracje wlasnych pol


	public:bool isButtonClicked;
	public:int xButtonClicked;
	public:int yButtonClicked;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column5;





	public:





	public:const char* functionAddress;

	//deklaracje wlasnych metod
	public: void loadProcessParameters();
	public: void callFunction();
	public: void setFunctionAddress(const char* functionAddress);

	public:

	private: System::Windows::Forms::Button^ callFunctionButton;


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(CallFunctionForm::typeid));
			this->closeButton = (gcnew System::Windows::Forms::Button());
			this->topPanel = (gcnew System::Windows::Forms::Panel());
			this->callFunctionButton = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->topPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
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
			this->closeButton->Click += gcnew System::EventHandler(this, &CallFunctionForm::closeButton_Click);
			// 
			// topPanel
			// 
			this->topPanel->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->topPanel->Controls->Add(this->closeButton);
			this->topPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->topPanel->Location = System::Drawing::Point(0, 0);
			this->topPanel->Name = L"topPanel";
			this->topPanel->Size = System::Drawing::Size(560, 42);
			this->topPanel->TabIndex = 3;
			this->topPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &CallFunctionForm::topPanelMouseDown);
			this->topPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &CallFunctionForm::topPanelMouseMove);
			this->topPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &CallFunctionForm::topPanelMouseUp);
			// 
			// callFunctionButton
			// 
			this->callFunctionButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8));
			this->callFunctionButton->Location = System::Drawing::Point(424, 288);
			this->callFunctionButton->Name = L"callFunctionButton";
			this->callFunctionButton->Size = System::Drawing::Size(106, 31);
			this->callFunctionButton->TabIndex = 16;
			this->callFunctionButton->Text = L"Call function";
			this->callFunctionButton->UseVisualStyleBackColor = true;
			this->callFunctionButton->Click += gcnew System::EventHandler(this, &CallFunctionForm::callFunctionButton_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->AllowUserToResizeColumns = false;
			this->dataGridView1->AllowUserToResizeRows = false;
			this->dataGridView1->BackgroundColor = System::Drawing::SystemColors::Window;
			this->dataGridView1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
				this->Column1,
					this->Column2, this->Column3, this->Column4, this->Column5
			});
			this->dataGridView1->EditMode = System::Windows::Forms::DataGridViewEditMode::EditOnEnter;
			this->dataGridView1->Location = System::Drawing::Point(28, 72);
			this->dataGridView1->MultiSelect = false;
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->dataGridView1->Size = System::Drawing::Size(502, 196);
			this->dataGridView1->TabIndex = 17;
			this->dataGridView1->CellEnter += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &CallFunctionForm::dataGridView1_CellEnter);
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"Index";
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Type";
			this->Column2->Name = L"Column2";
			this->Column2->ReadOnly = true;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"Size";
			this->Column3->Name = L"Column3";
			this->Column3->ReadOnly = true;
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"Register (Optional)";
			this->Column4->Name = L"Column4";
			this->Column4->ReadOnly = true;
			// 
			// Column5
			// 
			this->Column5->HeaderText = L"Value";
			this->Column5->Name = L"Column5";
			// 
			// CallFunctionForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(560, 331);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->callFunctionButton);
			this->Controls->Add(this->topPanel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"CallFunctionForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"CallFunctionForm";
			this->topPanel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

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
	private: System::Void callFunctionButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		this->callFunction();
	}

private: System::Void dataGridView1_CellEnter(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) 
{
	if (e->ColumnIndex == VALUE_COLUMN_INDEX)
	{
		if (this->dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value != NULL)
		{
			/*
			pin_ptr<const wchar_t> str1 = PtrToStringChars(this->dataGridView1->Rows[e->ColumnIndex]->Cells[e->ColumnIndex]->Value->ToString());
			_bstr_t bstrText(str1);
			const char* charText = bstrText;
			int value = strlen(bstrText);
			if (value > 0)
			{

			}
			*/
		}
	}
}
};
}
