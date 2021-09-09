#pragma once
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

using namespace Attendancelog;

/*----GETTERS---*/
Color MyForm::getColorCell(int i, int j)
{
	return dataGridView1[i, j]->Style->BackColor;
}

Color MyForm::getColorCell()
{
	return dataGridView1->CurrentCell->Style->BackColor;
}

int MyForm::getValueCell(int i, int j)
{
	return Convert::ToInt16(dataGridView1[i, j]->Value);
}

int MyForm::getValueCell()
{
	return Convert::ToInt16(dataGridView1->CurrentCell->Value);
}

String^ MyForm::getMonth(const int date)
{
	String^ month = "";
	switch (date)
	{
	case 1:
		month = "������";
		break;
	case 2:
		month = "�������";
		break;
	case 3: 
		month = "����";
		break;
	case 4:
		month = "������";
		break;
	case 5:
		month = "���";
		break;
	case 6: 
		month = "����";
		break;
	case 7:
		month = "����";
		break;
	case 8:
		month = "������";
		break;
	case 9:
		month = "��������";
		break;
	case 10:
		month = "�������";
		break;
	case 11:
		month = "������";
		break;
	case 12:
		month = "�������";
		break;

	default:
		month = "������";
		break;
	}

	return month;
}
/*----GETTERS---*/

/*----SETTERS---*/
void MyForm::SetColor(int i, int j, const Color& newColor)
{
	dataGridView1[i, j]->Style->BackColor = newColor;
}

void MyForm::SetColor(const Color& newColor)
{
	dataGridView1->CurrentCell->Style->BackColor = newColor;
}

void MyForm::SetValueCell(const int& newValue)
{
	dataGridView1->CurrentCell->Value = newValue;
}

void MyForm::SetValueCell(int i, int j, const int& newValue)
{
	dataGridView1[i, j]->Value = newValue;
}

void MyForm::SetNullCell()
{
	dataGridView1->CurrentCell->Value = nullptr;
}

void MyForm::SetNullCell(int i, int j)
{
	dataGridView1[i, j]->Value = nullptr;
}
/*----SETTERS---*/
#pragma endregion