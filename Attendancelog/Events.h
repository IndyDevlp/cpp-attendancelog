#pragma once

#include "MyForm.h"
#include "globalvars.h"
#include "TableForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace Attendancelog;


void MyForm::button1_Click(Object^ sender, EventArgs^ e) //������ ��
{
	EventColor(button1->BackColor);
}

void MyForm::button2_Click(Object^ sender, EventArgs^ e) //������ ��
{
	EventColor(button2->BackColor);
}

void MyForm::button3_Click(Object^ sender, EventArgs^ e) //������ �
{
	EventColor(button3->BackColor);
}

void MyForm::button4_Click(Object^ sender, EventArgs^ e)
{
	if (textBox1->Text == "" || textBox2->Text == "")
		MessageBox::Show("��������� ��� ����!", "������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	else
	{
		if (dataGridView1[0, 0]->Value != nullptr)
		{
			auto result = MessageBox::Show(
				"�� ������� ��� ������ ������� ����� �������?\n������ ��������!",
				"�������������",
				MessageBoxButtons::YesNo,
				MessageBoxIcon::Question);
			if (result == System::Windows::Forms::DialogResult::Yes)
			{
				ClearAllTable();
				//CreateTable(sender, e);
				NulledCells();

				��������ToolStripMenuItem->Visible = true;
				����������ToolStripMenuItem->Visible = true;

				MessageBox::Show("������� ���� ������� ������������ � ������ � ������", "���������", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
		}

		else
		{
			//CreateTable();
			NulledCells();

			��������ToolStripMenuItem->Visible = true;
			����������ToolStripMenuItem->Visible = true;

			MessageBox::Show("������� ���� ������� ������������ � ������ � ������", "���������", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}

		groupBoxCreate->Visible = false;
	}
}

void MyForm::����������ToolStripMenuItem_Click(Object^ sender, EventArgs^ e)
{
	�ountMain();
}

void MyForm::��������ToolStripMenuItem_Click(Object^ sender, EventArgs^ e)
{
	auto result = MessageBox::Show(
		"�� �������, ��� ������ �������� �������?\n���� ������� ���������!",
		"�������������",
		MessageBoxButtons::YesNo,
		MessageBoxIcon::Question);
	if (result == System::Windows::Forms::DialogResult::Yes)
	{
		Cursor = System::Windows::Forms::Cursors::WaitCursor;
		for (short i = 0; i <= MAXCOLS; i++)
			for (short j = 0; j < AmountOfPeople; j++)
				if (getColorCell(i, j) != Color::FromArgb(0, 0, 0))
				{
					SetColor(i, j, Color::FromArgb(255, 255, 255));
					if (i > 1)
						SetNullCell(i, j);
				}

		label1->Text = "0";
		label2->Text = "0";
		label3->Text = "0";
		label4->Text = "0";
		Cursor = System::Windows::Forms::Cursors::Cross;
	}
}

void MyForm::button5_Click(Object^ sender, EventArgs^ e)
{
	groupBoxCreate->Visible = false;
}

void MyForm::����������������ToolStripMenuItem_Click(Object^ sender, EventArgs^ e)
{
	AmountOfPeople++;
	short rowind = dataGridView1->CurrentCell->RowIndex;
	dataGridView1->Rows->Insert(rowind);

	for (short j = rowind; j < AmountOfPeople; j++)
	{
		int index;
		index = j + 1;
		SetValueCell(0, j, index);
	}

	for (short i = 0; i < MAXCOLS + 1; i++)
	{
		if (getColorCell(i, rowind + 1) == Color::FromArgb(0, 0, 0))
		{
			SetColor(i, rowind, Color::FromArgb(0, 0, 0));
		}
		if (getColorCell(i, rowind) != Color::FromArgb(0, 0, 0))
		{
			SetColor(i, rowind, Color::FromArgb(255, 255, 255));
		}
	}

	for (short i = 1; i < MAXCOLS - 5; i++)
	{
		dataGridView1[i, dataGridView1->RowCount - 2]->ReadOnly = false;
		dataGridView1[i, dataGridView1->RowCount - 1]->ReadOnly = true;
	}
	dataGridView1_SelectionChanged(sender, e);
}

void MyForm::���������������ToolStripMenuItem_Click(Object^ sender, EventArgs^ e)
{
	AmountOfPeople--;
	short rowind = dataGridView1->CurrentCell->RowIndex;
	dataGridView1->Rows->RemoveAt(rowind);

	for (short j = rowind; j < AmountOfPeople; j++)
	{
		int index;
		index = j + 1;
		SetValueCell(0, j, index);
	}

	dataGridView1->CurrentCell = dataGridView1[0, 0];
	dataGridView1_SelectionChanged(sender, e);
}

void MyForm::���������ToolStripMenuItem1_Click(Object^ sender, EventArgs^ e)
{
	SaveAs();
}

void MyForm::dataGridView1_SelectionChanged(Object^ sender, EventArgs^ e)
{
	//��������� �������� ������ �� ������� � ������
	CurrColNew = dataGridView1->CurrentCell->ColumnIndex;
	CurrRowNew = dataGridView1->CurrentCell->RowIndex;

	short col = CurrColNew;
	short row = CurrRowNew;

	short colold = CurrColOld;
	short rowold = CurrRowOld;

	/*
	dataGridView1->Columns[33]->HeaderCell->Style->BackColor = Color::FromArgb(127, 118, 121);
	dataGridView1->Columns[34]->HeaderCell->Style->BackColor = Color::FromArgb(0, 190, 20);
	dataGridView1->Columns[35]->HeaderCell->Style->BackColor = Color::FromArgb(0, 162, 254);
	dataGridView1->Columns[36]->HeaderCell->Style->BackColor = Color::FromArgb(190, 0, 0);
	*/

	Color& rowheadbackcolornew = dataGridView1->Columns[CurrColNew]->HeaderCell->Style->BackColor;
	int stp = 65;

	if (CurrColOld != CurrColNew || CurrRowOld != CurrRowNew)
	{
		if (rowheadbackcolornew == Color::FromArgb(127, 118, 121))
			rowheadbackcolornew = Color::FromArgb(127, 118 + stp, 121);

		else if (rowheadbackcolornew == Color::FromArgb(0, 190, 20))
			rowheadbackcolornew = Color::FromArgb(0, 190 + stp, 20);

		else if (rowheadbackcolornew == Color::FromArgb(0, 162, 254))
			rowheadbackcolornew = Color::FromArgb(0, 162 + stp, 254);

		else if (rowheadbackcolornew == Color::FromArgb(190, 0, 0))
			rowheadbackcolornew = Color::FromArgb(190, 0 + stp, 0);
		else
			rowheadbackcolornew = Color::FromArgb(255, 245, 194);

		dataGridView1->Columns[CurrColNew]->HeaderCell->Style->BackColor = rowheadbackcolornew;

		short i = 0;
		while (i < colold)
		{
			if (getColorCell(i, rowold) == Color::FromArgb(255, 245, 194))
				SetColor(i, rowold, Color::FromArgb(255, 255, 255));
			i++;
		}

		short j = 0;
		while (j < rowold)
		{
			if (getColorCell(colold, j) == Color::FromArgb(255, 245, 194))
				SetColor(colold, j, Color::FromArgb(255, 255, 255));
			j++;
		}

		short _i = 0;
		while (_i < col)
		{

			if (getColorCell(_i, row) == Color::FromArgb(255, 255, 255))
				SetColor(_i, row, Color::FromArgb(255, 245, 194));
			_i++;
		}

		short _j = 0;
		while (_j < row)
		{
			if (getColorCell(col, _j) == Color::FromArgb(255, 255, 255))
				SetColor(col, _j, Color::FromArgb(255, 245, 194));
			_j++;

		}
	}

	Color& rowheadbackcolorold = dataGridView1->Columns[CurrColOld]->HeaderCell->Style->BackColor;

	if (rowheadbackcolorold == Color::FromArgb(127, 118 + stp, 121))
		rowheadbackcolorold = Color::FromArgb(127, 118, 121);

	else if (rowheadbackcolorold == Color::FromArgb(0, 190 + stp, 20))
		rowheadbackcolorold = Color::FromArgb(0, 190, 20);

	else if (rowheadbackcolorold == Color::FromArgb(0, 162 + stp, 254))
		rowheadbackcolorold = Color::FromArgb(0, 162, 254);

	else if (rowheadbackcolorold == Color::FromArgb(190, 0 + stp, 0))
		rowheadbackcolorold = Color::FromArgb(190, 0, 0);
	else
		rowheadbackcolorold = Color::FromArgb(255, 255, 255);

	if (CurrColOld == CurrColNew)
	{
		dataGridView1->Columns[CurrColOld]->HeaderCell->Style->BackColor = rowheadbackcolornew;
	}
	else
	{
		dataGridView1->Columns[CurrColOld]->HeaderCell->Style->BackColor = rowheadbackcolorold;
	}

	CurrRowOld = CurrRowNew;
	CurrColOld = CurrColNew;
}

void MyForm::������������������ToolStripMenuItem_Click(Object^ sender, EventArgs^ e)
{
	auto result = MessageBox::Show("�� �������, ��� ������ ������� ������ ������?", "�������������", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
	if (result == System::Windows::Forms::DialogResult::Yes)
	{
		short i = 0;
		while (i <= MAXCOLS)
		{
			short j = 0;
			while (j < AmountOfPeople)
			{
				if (getColorCell(i, j) == Color::FromArgb(204, 255, 153))
					SetColor(i, j, Color::FromArgb(255, 255, 255));
				j++;
			}
			i++;
		}
	}

	dataGridView1->CurrentCell = dataGridView1[0, 0];
	dataGridView1_SelectionChanged(sender, e);
}

void MyForm::�������ToolStripMenuItem_Click(Object^ sender, EventArgs^ e)
{
	TableForm^ createtable = gcnew TableForm(this);
	createtable->ShowDialog();
}

void MyForm::������ToolStripMenuItem_Click(Object^ sender, EventArgs^ e)
{
	return void();
}

void MyForm::dataGridView1_CellEndEdit(Object^ sender, DataGridViewCellEventArgs^ e)
{
	if (Convert::ToInt16(dataGridView1->CurrentCell->ColumnIndex) != 1)
	{
		try
		{
			//������� ��������������� �������� ������ � Int32
			Int32 result;
			result = System::Convert::ToInt32(this->dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value);

			if (result > 24)
			{
				MessageBox::Show("�������� <" + result + "> �����������!\n������� ����� ������ ���� ��� ������ 25\n\n������: [" + (dataGridView1->CurrentCell->ColumnIndex - 1) + ";" + (dataGridView1->CurrentCell->RowIndex + 1) + "]", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
				this->dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value = nullptr;
			}
		}
		catch (Exception^ ex)
		{
			//���� ��� ��������������� ��������� ������ - ���������� ���� ������ � ������� �������� ������
			MessageBox::Show(ex->Message + "\n������� ����� ������ ����\n\n������: [" + (dataGridView1->CurrentCell->ColumnIndex - 1) + ";" + (dataGridView1->CurrentCell->RowIndex + 1) + "]", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
			this->dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value = nullptr;
		}
	}
	/*
	if (Convert::ToInt16(dataGridView1->CurrentCell->ColumnIndex) > 1)
	{
		int value = Convert::ToInt16(dataGridView1->CurrentCell->Value);
		if (value > 24)
		{
			MessageBox::Show("�������� <" + value + "> �����������!\n������� ����� ������ ���� ��� ������ 25\n\n������: [" + (dataGridView1->CurrentCell->ColumnIndex - 1) + ";" + (dataGridView1->CurrentCell->RowIndex + 1) + "]", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
			this->dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value = nullptr;
		}
	}
	*/


	if (dataGridView1->CurrentCell->Style->BackColor == Color::FromArgb(204, 255, 153)) //���� ��������� ������ - (204, 255, 153)
	{
		for (int i = 0; i < dataGridView1->ColumnCount; i++)
		{
			if (dataGridView1[i, dataGridView1->CurrentCell->RowIndex]->Style->BackColor != Color::FromArgb(0, 0, 0))
				dataGridView1[i, dataGridView1->CurrentCell->RowIndex]->Style->BackColor = Color::FromArgb(255, 255, 255);
		}
	}
}

void MyForm::������ToolStripMenuItem_Click(Object^ sender, EventArgs^ e)
{
	MessageBox::Show("����������� ����������:\n����� ������ ����� ����, ����� ������� �������� (���� -> �������), ����� ������ ��� ����� � ��������������� ������.\n1)����� �������� �������������� ������� ����� ������ �� ������ � ������ �� ������ \"��\"(Ctrl + Q)\n2)�������� ������������ ������� \"��\"(Ctrl + W)\n3)�������� ������� �� ������� \"�\"(Ctrl + E)\n\n���������� ��������\n����� �������� �������� ���� ����� �������� �������(����) � ������ �� ����\"+\"(Ctrl + Space), ��������� ������ �������\n\n����� �������\n����� �������� ����� ������ ���������� ������ ( �������� - �������(F12) ), ���� �� ������� ������������, ��������� ��� �� ���� ������, ����� ������ � ������ ���� ���-�� �� ���", "������", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

void MyForm::textBox1_KeyPress(Object^ sender, KeyPressEventArgs^ e)
{
	if ((e->KeyChar <= 47 || e->KeyChar >= 58) && e->KeyChar != 8)
		e->Handled = true;
}

void MyForm::textBox3_KeyPress(Object^ sender, KeyPressEventArgs^ e)
{
	if ((e->KeyChar <= 47 || e->KeyChar >= 58) && e->KeyChar != 8)
		e->Handled = true;
}

void MyForm::MyForm_KeyDown(Object^ sender, KeyEventArgs^ e)
{
	if (e->KeyCode == Keys::Q && (e->Alt || e->Control))
		button1->PerformClick();

	else if (e->KeyCode == Keys::W && (e->Alt || e->Control))
		button2->PerformClick();

	else if (e->KeyCode == Keys::E && (e->Alt || e->Control))
		button3->PerformClick();

	else if (e->KeyCode == Keys::Delete)
		DeleteCell();

	else if (e->KeyCode == Keys::Space && e->Control)
		AddWeekend();

	else if (e->KeyCode == Keys::Delete && e->Control)
		DelWeekend();

	else if (e->KeyCode == Keys::F12)
		�ountMain();

	//else if (e->KeyCode == Keys::S && e->Control)
	//	Save();

	else if (e->KeyCode == Keys::S && e->Shift && e->Control)
		SaveAs();
}

void MyForm::����������������ToolStripMenuItem_Click(Object^ sender, EventArgs^ e)
{
	AddWeekend();
}

void MyForm::���������������ToolStripMenuItem_Click(Object^ sender, EventArgs^ e)
{
	DelWeekend();
}

void MyForm::MyForm_FormClosing(Object^ sender, FormClosingEventArgs^ e)
{
	if (changeamount >= 1)
	{
		System::Windows::Forms::DialogResult result;
		result = MessageBox::Show("�� ������ ��������� ���������?", "������ ������������", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Question);
		if (result == System::Windows::Forms::DialogResult::Yes)
			SaveAs();
		else if (result == System::Windows::Forms::DialogResult::No) Application::ExitThread();
		else if (result == System::Windows::Forms::DialogResult::Cancel) e->Cancel = true;
	}
}

void MyForm::MyForm_Load(Object^ sender, EventArgs^ e)
{
	for (int i = 0; i < 33; dataGridView1->Columns[i]->HeaderCell->Style->BackColor = Color::FromArgb(255, 255, 255), i++)
		changeamount = 0;
	PATH = nullptr;
	dataGridView1[0, 0]->Selected;
	CurrRowOld = CurrColOld = 0;
}

void MyForm::dataGridView1_CellValueChanged(Object^ sender, DataGridViewCellEventArgs^ e)
{
	changeamount++;
	if (changeamount == 1)
		MyForm::Text += "*";
}

void MyForm::����������ToolStripMenuItem_Click(Object^ sender, EventArgs^ e)
{
	MessageBox::Show("������ Attendancelog\n������ 1.5.1\n������ 08.04.2021\n� ��������� �.�.\n����� ������� ����������  \n\nvk.com/indydevlp", "� ���������", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

void MyForm::�������ToolStripMenuItem_Click(Object^ sender, EventArgs^ e)
{
	Stream^ mystr = nullptr;
	OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog();
	openFileDialog1->Filter = "������ (*.att)|*.att";

	PATH = nullptr;
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		ClearAllTable();	//������� ���� ������� ���� ���� �����-�� ������ � ���, ���� ���� � �� ����
		PATH = openFileDialog1->SafeFileName;
		textBox2->Text = PATH;
		if ((mystr = openFileDialog1->OpenFile()) != nullptr)
		{
			StreamReader^ myread = gcnew StreamReader(mystr);

			String^ str;		//������ � ������� ����� ����
			String^ tempstr;	//��������� ������ ��� ������ �� �������

			int lengthcellvalue = 1;		//����� �������� ������ �� ���������
			int col = 0; //���������� � ����� ������� �� ���������					//	  ������ ����� ������ �
			int j = 0;	 //���������� � ����� ������e �� ���������					//	  dataGridView1[0, 0], �.� � ������� ID dataGridView1[col, j]

			dataGridView1->Rows->Add();		//�������� �������, ������ ������ ������� 1 ��� (���������������)

			try
			{
				while ((str = myread->ReadLine()) != nullptr)	//������ ������ �� �����, ���� �� �������� �������
				{
					for (int k = 0; k < str->Length; k += 4)
					{
						int i = k;	//���������� ��������� ���������
						while (Convert::ToString(str[i + 1]) != "^")	//������� ����� �� ^ (�������� ������)
						{
							lengthcellvalue++;	//����� �������� ������ �� ^
							i++;	//����������� i, ����� ��������� ����� ^
						}

						int n = k; //���������� ������� ��� ������ �� ��������� ������
						for (int p = 0; p < lengthcellvalue; p++)
						{
							tempstr += str[n]; //���������� �������� ������(��������� �� 1 ������� � ������)
							n++; //���������� ������� ������������ k(���������) �� ^
						}
						lengthcellvalue = 1; //�������� ����� (������ � �� ��������� 1)

						if (col > 36) //���� ������ ��� ������� �� ������� �� ����� ������
						{
							j++; // ������� �� ����� ������
							col = 0;	//������� �� ����� ������ � ����� ������, �������� ����� [0, j
							dataGridView1->Rows->Add();	//�������� ������

							if (Convert::ToString(tempstr) == "_")	//�.�. ������ ( _ ) ������� ������ ������, ������ ��������
								dataGridView1[col, j]->Value = nullptr; //������� ������ ���� ��� ������ ( _ )
							else	//����� ���� �� ( _ ), �� ������� ������
								dataGridView1[col, j]->Value = Convert::ToString(tempstr); //������ �������� ������
						}
						else	//�� �� �����, ������ ���� col < 36
							if (Convert::ToString(tempstr) == "_")
								dataGridView1[col, j]->Value = nullptr;
							else
								dataGridView1[col, j]->Value = Convert::ToString(tempstr);


						//������ ������� � ������ (�������� ����� ^)
						if (Convert::ToString(str[i + 2]) == "1")	//���� id = 1, �� ������� �������
							dataGridView1[col, j]->Style->BackColor = Color::FromArgb(190, 0, 0);

						else if (Convert::ToString(str[i + 2]) == "2")	//�������
							dataGridView1[col, j]->Style->BackColor = Color::FromArgb(0, 162, 254);

						else if (Convert::ToString(str[i + 2]) == "3")	//������
							dataGridView1[col, j]->Style->BackColor = Color::FromArgb(0, 190, 20);

						else if (Convert::ToString(str[i + 2]) == "4")	//׸����
							dataGridView1[col, j]->Style->BackColor = Color::FromArgb(0, 0, 0);

						else if (Convert::ToString(str[i + 2]) == "5")	//����� (������� ������)
							dataGridView1[col, j]->Style->BackColor = Color::FromArgb(255, 255, 255);

						else if (Convert::ToString(str[i + 2]) == "6")	//������ (������� ������)
							dataGridView1[col, j]->Style->BackColor = Color::FromArgb(204, 255, 153);

						else if (Convert::ToString(str[i + 2]) == "0")	//������, ��������� ����
							dataGridView1[col, j]->Style->BackColor = Color::FromArgb(255, 128, 0);

						col++;				//������� � ��������� �������
						k = i;				//������ k � ������� ����� ^, ����� ����������� �� ����� �������� (+4)
						tempstr = "";		//������� ��������� ������
						AmountOfPeople = j;	//���������� ���������� �������
					}
				}
			}
<<<<<<< HEAD
			catch (...)
=======
			catch (InvalidCastException^ e)
>>>>>>> cf7c1418bc9edc2f16674abbd93826554292bfdb
			{
				auto result = MessageBox::Show("��������� ����������� ������", "������",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
				if (result == System::Windows::Forms::DialogResult::OK)
					Application::ExitThread();
				else
					Application::ExitThread();
			}
			finally
			{
				myread->Close();
				for (int i = 1; i < dataGridView1->ColumnCount - 5; i++)
					dataGridView1[i, dataGridView1->RowCount - 1]->ReadOnly = true;

				dataGridView1->Rows->RemoveAt(j);	//������� ��������������� ������
				MyForm::Text = "������ ������������ " + " [" + PATH + "]";
<<<<<<< HEAD
				DisplayTable();
=======
				DisplayTable();	//���������� �������
>>>>>>> cf7c1418bc9edc2f16674abbd93826554292bfdb
				label6->Visible = false;
				changeamount = 0;
			}
		}
	}
}

void TableForm::button1_Click(Object^ sender, EventArgs^ e)
{
<<<<<<< HEAD
	bool success = false;
	
	try
	{
		String^ name = textBox2->Text;
		int date = dateTimePicker1->Value.Month;
		int amount = Convert::ToInt16(textBox1->Text);
		success = true;
		if (success)
		{
			mainform->CreateTable(amount, name, date);
			TableForm::~TableForm();
		}
	}
	catch (...)
	{
		textBox1->Text = nullptr;

		MessageBox::Show("���������� ������� ������ ���� ����� ������!", "������",
			MessageBoxButtons::OK,
			MessageBoxIcon::Error);
	}	
}

void TableForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (textBox1->Text != "" || textBox2->Text != "")
	{
		auto result = MessageBox::Show("�� ����� ������, ������� ��� ������ �������� ��������?", "���������",
			MessageBoxButtons::YesNo,
			MessageBoxIcon::Question);

		if (result == System::Windows::Forms::DialogResult::Yes)
			TableForm::~TableForm();
	}
}

void Attendancelog::TableForm::TableForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
{
	if (textBox1->Text != "" || textBox2->Text != "")
	{
		//System::Windows::Forms::DialogResult result;
		auto result = MessageBox::Show("�� ����� ������, ������� ��� ������ �������� ��������?", "���������", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
		if (result == System::Windows::Forms::DialogResult::Yes)
			TableForm::~TableForm();
		else
			e->Cancel = true;
	}
=======
	int amount = Convert::ToInt16(textBox1->Text);
	String^ name = textBox2->Text;
	int date = dateTimePicker1->Value.Month;

	mainform->CreateTable(amount, name, date);

	TableForm::~TableForm();
}

void TableForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	TableForm::~TableForm();
>>>>>>> cf7c1418bc9edc2f16674abbd93826554292bfdb
}

