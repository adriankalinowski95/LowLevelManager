#pragma once
#include "stdio.h"
#include "Controller/MainController.h"
#include "OpenProcessForm.h"
#include "InformationForm.h"
#include "InjectShellcodeForm.h"
#include "JumpForm.h"
#include "SearchingForm.h"
#include "RecognizeFunctionForm.h"


namespace LowLevelManagerv1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			isButtonClicked = false;
			xButtonClicked = NULL;
			yButtonClicked = NULL;
			this->mainController = new MainController();

		}
	private: System::Windows::Forms::Button^ injectShellcodeButton;
	private: System::Windows::Forms::Panel^ panel3;





	private: System::Windows::Forms::ListView^ listView1;
	private: System::Windows::Forms::ColumnHeader^ columnHeader1;
	private: System::Windows::Forms::ColumnHeader^ columnHeader2;
	private: System::Windows::Forms::ColumnHeader^ columnHeader3;
	private: System::Windows::Forms::ColumnHeader^ columnHeader4;
	private: System::Windows::Forms::VScrollBar^ vScrollBar1;
	private: System::Windows::Forms::Button^ searchButton;
	private: System::Windows::Forms::Button^ recognizeFunctionButton;












	private: System::Windows::Forms::Button^ jumpButton;














	public:void callbackC(String ^str);
	private: MainController* mainController;
	public: MainController* getMainController();
	public:void loadProcessInstructions();
	public:void loadProcessInstructionsByIndex(unsigned long index);
	public:void setProcessName(const char* newProcessName);
	public:void cleanListView();
	public:void jumpToAddress(String^ operation);
	public:bool isButtonClicked;
	public:int xButtonClicked;
	public:int yButtonClicked;
	private: System::Windows::Forms::Panel^ panel2;
	public:


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Panel^ topPanel;


	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::Button^ openProcessButton;
	private: System::Windows::Forms::Button^ informationButton;



	private: System::Windows::Forms::Button^ closeButton;




	private: System::Windows::Forms::Label^ processName;
	private: System::Windows::Forms::Label^ label1;


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->recognizeFunctionButton = (gcnew System::Windows::Forms::Button());
			this->searchButton = (gcnew System::Windows::Forms::Button());
			this->jumpButton = (gcnew System::Windows::Forms::Button());
			this->injectShellcodeButton = (gcnew System::Windows::Forms::Button());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->informationButton = (gcnew System::Windows::Forms::Button());
			this->openProcessButton = (gcnew System::Windows::Forms::Button());
			this->topPanel = (gcnew System::Windows::Forms::Panel());
			this->processName = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->closeButton = (gcnew System::Windows::Forms::Button());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->vScrollBar1 = (gcnew System::Windows::Forms::VScrollBar());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->panel1->SuspendLayout();
			this->topPanel->SuspendLayout();
			this->panel3->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::WhiteSmoke;
			this->panel1->Controls->Add(this->recognizeFunctionButton);
			this->panel1->Controls->Add(this->searchButton);
			this->panel1->Controls->Add(this->jumpButton);
			this->panel1->Controls->Add(this->injectShellcodeButton);
			this->panel1->Controls->Add(this->panel2);
			this->panel1->Controls->Add(this->informationButton);
			this->panel1->Controls->Add(this->openProcessButton);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(126, 589);
			this->panel1->TabIndex = 1;
			// 
			// recognizeFunctionButton
			// 
			this->recognizeFunctionButton->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->recognizeFunctionButton->FlatAppearance->BorderSize = 5;
			this->recognizeFunctionButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->recognizeFunctionButton->Font = (gcnew System::Drawing::Font(L"Corbel", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->recognizeFunctionButton->Location = System::Drawing::Point(0, 325);
			this->recognizeFunctionButton->Name = L"recognizeFunctionButton";
			this->recognizeFunctionButton->Size = System::Drawing::Size(126, 58);
			this->recognizeFunctionButton->TabIndex = 7;
			this->recognizeFunctionButton->Text = L"Recognize Function";
			this->recognizeFunctionButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->recognizeFunctionButton->UseVisualStyleBackColor = true;
			this->recognizeFunctionButton->Click += gcnew System::EventHandler(this, &MainForm::recognizeFunctionButton_Click);
			// 
			// searchButton
			// 
			this->searchButton->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->searchButton->FlatAppearance->BorderSize = 5;
			this->searchButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->searchButton->Font = (gcnew System::Drawing::Font(L"Corbel", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->searchButton->Location = System::Drawing::Point(0, 270);
			this->searchButton->Name = L"searchButton";
			this->searchButton->Size = System::Drawing::Size(126, 58);
			this->searchButton->TabIndex = 6;
			this->searchButton->Text = L"Search";
			this->searchButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->searchButton->UseVisualStyleBackColor = true;
			this->searchButton->Click += gcnew System::EventHandler(this, &MainForm::searchButton_Click);
			// 
			// jumpButton
			// 
			this->jumpButton->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->jumpButton->FlatAppearance->BorderSize = 5;
			this->jumpButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->jumpButton->Font = (gcnew System::Drawing::Font(L"Corbel", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->jumpButton->Location = System::Drawing::Point(0, 222);
			this->jumpButton->Name = L"jumpButton";
			this->jumpButton->Size = System::Drawing::Size(126, 58);
			this->jumpButton->TabIndex = 5;
			this->jumpButton->Text = L" Jump";
			this->jumpButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->jumpButton->UseVisualStyleBackColor = true;
			this->jumpButton->Click += gcnew System::EventHandler(this, &MainForm::jumpButton_Click);
			// 
			// injectShellcodeButton
			// 
			this->injectShellcodeButton->BackColor = System::Drawing::Color::Transparent;
			this->injectShellcodeButton->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->injectShellcodeButton->FlatAppearance->BorderSize = 5;
			this->injectShellcodeButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->injectShellcodeButton->Font = (gcnew System::Drawing::Font(L"Corbel", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->injectShellcodeButton->Location = System::Drawing::Point(0, 167);
			this->injectShellcodeButton->Name = L"injectShellcodeButton";
			this->injectShellcodeButton->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->injectShellcodeButton->Size = System::Drawing::Size(126, 61);
			this->injectShellcodeButton->TabIndex = 4;
			this->injectShellcodeButton->Text = L"Inject Shellcode";
			this->injectShellcodeButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->injectShellcodeButton->UseVisualStyleBackColor = false;
			this->injectShellcodeButton->Click += gcnew System::EventHandler(this, &MainForm::injectShellcodeButton_Click);
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->panel2->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel2->Location = System::Drawing::Point(0, 0);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(126, 58);
			this->panel2->TabIndex = 3;
			// 
			// informationButton
			// 
			this->informationButton->BackColor = System::Drawing::Color::Transparent;
			this->informationButton->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->informationButton->FlatAppearance->BorderSize = 5;
			this->informationButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->informationButton->Font = (gcnew System::Drawing::Font(L"Corbel", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->informationButton->Location = System::Drawing::Point(0, 109);
			this->informationButton->Name = L"informationButton";
			this->informationButton->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->informationButton->Size = System::Drawing::Size(126, 61);
			this->informationButton->TabIndex = 1;
			this->informationButton->Text = L" Information";
			this->informationButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->informationButton->UseVisualStyleBackColor = false;
			this->informationButton->Click += gcnew System::EventHandler(this, &MainForm::informationButton_Click);
			// 
			// openProcessButton
			// 
			this->openProcessButton->BackColor = System::Drawing::Color::Transparent;
			this->openProcessButton->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->openProcessButton->FlatAppearance->BorderSize = 4;
			this->openProcessButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->openProcessButton->Font = (gcnew System::Drawing::Font(L"Corbel", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->openProcessButton->Location = System::Drawing::Point(0, 58);
			this->openProcessButton->Name = L"openProcessButton";
			this->openProcessButton->Size = System::Drawing::Size(126, 55);
			this->openProcessButton->TabIndex = 0;
			this->openProcessButton->Text = L" Open Process";
			this->openProcessButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->openProcessButton->UseVisualStyleBackColor = false;
			this->openProcessButton->Click += gcnew System::EventHandler(this, &MainForm::openProcessButton_Click);
			// 
			// topPanel
			// 
			this->topPanel->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->topPanel->Controls->Add(this->processName);
			this->topPanel->Controls->Add(this->label1);
			this->topPanel->Controls->Add(this->closeButton);
			this->topPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->topPanel->Location = System::Drawing::Point(126, 0);
			this->topPanel->Margin = System::Windows::Forms::Padding(0);
			this->topPanel->Name = L"topPanel";
			this->topPanel->Size = System::Drawing::Size(683, 58);
			this->topPanel->TabIndex = 2;
			this->topPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::topPanelMouseDown);
			this->topPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::topPanelMouseMove);
			this->topPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::topPanelMouseUp);
			// 
			// processName
			// 
			this->processName->AutoSize = true;
			this->processName->Location = System::Drawing::Point(122, 20);
			this->processName->Name = L"processName";
			this->processName->Size = System::Drawing::Size(42, 19);
			this->processName->TabIndex = 2;
			this->processName->Text = L"none";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(109, 19);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Process name : ";
			// 
			// closeButton
			// 
			this->closeButton->FlatAppearance->BorderSize = 0;
			this->closeButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->closeButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"closeButton.Image")));
			this->closeButton->Location = System::Drawing::Point(617, 0);
			this->closeButton->Name = L"closeButton";
			this->closeButton->Size = System::Drawing::Size(63, 58);
			this->closeButton->TabIndex = 0;
			this->closeButton->Text = L" ";
			this->closeButton->UseVisualStyleBackColor = true;
			this->closeButton->Click += gcnew System::EventHandler(this, &MainForm::closeButton_Click);
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::Color::WhiteSmoke;
			this->panel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel4->Location = System::Drawing::Point(742, 58);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(67, 531);
			this->panel4->TabIndex = 4;
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::Color::WhiteSmoke;
			this->panel3->Controls->Add(this->vScrollBar1);
			this->panel3->Controls->Add(this->listView1);
			this->panel3->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel3->Font = (gcnew System::Drawing::Font(L"Corbel", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->panel3->Location = System::Drawing::Point(126, 58);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(616, 531);
			this->panel3->TabIndex = 3;
			// 
			// vScrollBar1
			// 
			this->vScrollBar1->LargeChange = 1;
			this->vScrollBar1->Location = System::Drawing::Point(590, 26);
			this->vScrollBar1->Maximum = 0;
			this->vScrollBar1->Name = L"vScrollBar1";
			this->vScrollBar1->Size = System::Drawing::Size(17, 384);
			this->vScrollBar1->TabIndex = 5;
			this->vScrollBar1->ValueChanged += gcnew System::EventHandler(this, &MainForm::vScrollBar1_ValueChanged);
			// 
			// listView1
			// 
			this->listView1->AutoArrange = false;
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {
				this->columnHeader1, this->columnHeader2,
					this->columnHeader3, this->columnHeader4
			});
			this->listView1->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listView1->FullRowSelect = true;
			this->listView1->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->listView1->HideSelection = false;
			this->listView1->LabelEdit = true;
			this->listView1->Location = System::Drawing::Point(10, 26);
			this->listView1->Name = L"listView1";
			this->listView1->Scrollable = false;
			this->listView1->Size = System::Drawing::Size(577, 384);
			this->listView1->TabIndex = 4;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			this->listView1->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::listView1_SelectedIndexChanged);
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"Address";
			this->columnHeader1->Width = 160;
			// 
			// columnHeader2
			// 
			this->columnHeader2->Text = L"Instruction";
			this->columnHeader2->Width = 110;
			// 
			// columnHeader3
			// 
			this->columnHeader3->Text = L"Operation";
			this->columnHeader3->Width = 178;
			// 
			// columnHeader4
			// 
			this->columnHeader4->Text = L"Comment";
			this->columnHeader4->Width = 200;
			// 
			// MainForm
			// 
			this->AllowDrop = true;
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(809, 589);
			this->Controls->Add(this->panel4);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->topPanel);
			this->Controls->Add(this->panel1);
			this->Font = (gcnew System::Drawing::Font(L"Corbel", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->panel1->ResumeLayout(false);
			this->topPanel->ResumeLayout(false);
			this->topPanel->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void closeButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		this->Close();
	}
	private: System::Void openProcessButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		OpenProcessForm^ openProcessForm = gcnew OpenProcessForm();
		openProcessForm->setMainController(this->mainController);
		openProcessForm->loadProcesses();
		openProcessForm->ShowDialog();
		if (this->mainController->getInjector()->getInjectedProcessHandle() != NULL)
		{
			this->cleanListView();
			this->loadProcessInstructions();
		}

	}
	private: System::Void topPanelMouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		this->isButtonClicked = false;
		this->xButtonClicked = NULL;
		this->yButtonClicked = NULL;
	}
	private: System::Void topPanelMouseDown(System::Object^  sender,System::Windows::Forms::MouseEventArgs^  e)
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

	private: System::Void informationButton_Click(System::Object^ sender, System::EventArgs^ e)
	{

		if (this->mainController->getInjector()->getInjectedProcessHandle() != NULL)
		{
			InformationForm^ informationForm = gcnew InformationForm();
			informationForm->setMainController(this->mainController);
			informationForm->loadProcessInformation();
			informationForm->ShowDialog();
			
		}
	}
private: System::Void injectShellcodeButton_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (this->mainController->getInjector()->getInjectedProcessHandle() != NULL)
	{
		InjectShellcodeForm^ injectShellcodeForm = gcnew InjectShellcodeForm();
		injectShellcodeForm->ShowDialog();
	}
}
private: System::Void vScrollBar1_ValueChanged(System::Object^ sender, System::EventArgs^ e) 
{
	if (this->mainController->getInjector()->getInjectedProcessHandle() != NULL)
	{
		if (this->vScrollBar1->Value >= 0)
		{
			this->loadProcessInstructionsByIndex(this->vScrollBar1->Value);
		}
	}
	
}

private: System::Void vScrollBar1_DragDrop(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e) {
}
private: System::Void listView1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
{
	if (this->mainController->getInjector()->getInjectedProcessHandle() != NULL)
	{
		if (listView1->SelectedItems->Count > 0)
		{
			String^ address = this->listView1->SelectedItems[0]->SubItems[0]->Text;
			String^ instruction = this->listView1->SelectedItems[0]->SubItems[1]->Text;
			String^ operation = this->listView1->SelectedItems[0]->SubItems[2]->Text;

			printf("address: %s, instruction: %s, operation: %s \n", address, instruction, operation);

			if (instruction->CompareTo("CALL") == 0 || instruction->CompareTo("JMP") == 0)
			{
				this->jumpToAddress(operation);
			}
		}
	}
}
delegate void MyCallback(String^ str);

private: System::Void jumpButton_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (this->mainController->getInjector()->getInjectedProcessHandle() != NULL)
	{
		JumpForm^ jumpForm = gcnew JumpForm();
		jumpForm->setMainForm(this);
		jumpForm->ShowDialog();
	}
}

private: System::Void searchButton_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (this->mainController->getInjector()->getInjectedProcessHandle() != NULL)
	{
		SearchingForm^ searchForm = gcnew SearchingForm();
		searchForm->ShowDialog();
	}
}
private: System::Void recognizeFunctionButton_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (this->mainController->getInjector()->getInjectedProcessHandle() != NULL)
	{
		RecognizeFunctionForm^ recognizeFunctionForm = gcnew RecognizeFunctionForm();
		recognizeFunctionForm->ShowDialog();
	}
}

};
}
