// MyDlg2.cpp: файл реализации
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MyDlg2.h"
#include "afxdialogex.h"
#include "stdlib.h"
#include <iostream>
#include <string>
using namespace std;


// Диалоговое окно MyDlg2
#define IDC_BN_1001		1001


IMPLEMENT_DYNAMIC(MyDlg2, CDialogEx)

MyDlg2::MyDlg2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

BOOL MyDlg2::OnInitDialog()
{
	CStatic *pStatic = new CStatic;
	pStatic->Create(_T("Matrix size"), WS_CHILD | WS_VISIBLE, CRect(5, 5, 100, 20), this, 108);
	CStatic *pStatic2 = new CStatic;
	pStatic2->Create(_T("*"), WS_CHILD | WS_VISIBLE, CRect(175, 5, 190, 20), this, 108);
	
	pEditMatrixSize1 = new CEdit;
	pEditMatrixSize1->Create(ES_MULTILINE | ES_AUTOVSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(95, 5, 125, 30), this, 108);
	pEditMatrixSize2 = new CEdit;
	pEditMatrixSize2->Create(ES_MULTILINE | ES_AUTOVSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(135, 5, 165, 30), this, 108);
	pEditMatrixSize3 = new CEdit;
	pEditMatrixSize3->Create(ES_MULTILINE | ES_AUTOVSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(190, 5, 220, 30), this, 108);
	pEditMatrixSize4 = new CEdit;
	pEditMatrixSize4->Create(ES_MULTILINE | ES_AUTOVSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(230, 5, 260, 30), this, 108);
	
	CMFCButton *pButton = new CMFCButton;
	pButton->Create(_T("OK"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(270, 5, 310, 30), this, 1001);
	pButton->EnableWindowsTheming(TRUE);

	return TRUE;
}


MyDlg2::~MyDlg2()
{
	if (vecMatrix1.size() != 0)
		deleteVecMatrix(vecMatrix1);
	if (vecMatrix2.size() != 0)
		deleteVecMatrix(vecMatrix2);
	if (vecMatrixSolution.size() != 0)
		deleteVecMatrix(vecMatrixSolution);
}

void MyDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MyDlg2, CDialogEx)
	ON_BN_CLICKED(1001, &MyDlg2::pre_drow_matrix)
	ON_BN_CLICKED(1002, &MyDlg2::draw_matrix_solution)
END_MESSAGE_MAP()


// Обработчики сообщений MyDlg2

void MyDlg2::pre_drow_matrix()
{	
	clearUI();

	int sizeM1row, sizeM1col, sizeM2row, sizeM2col;
	//чтение введенных размеров матрицы
	{
		CString sWindowText;
		pEditMatrixSize1->GetWindowText(sWindowText);
		sizeM1row = _ttoi(sWindowText);
		pEditMatrixSize2->GetWindowText(sWindowText);
		sizeM1col = _ttoi(sWindowText);
		pEditMatrixSize3->GetWindowText(sWindowText);
		sizeM2row = _ttoi(sWindowText);
		pEditMatrixSize4->GetWindowText(sWindowText);
		sizeM2col = _ttoi(sWindowText);
	}

	if (sizeM1row < 0)
		sizeM1row = 0;
	if (sizeM1col < 0)
		sizeM1col = 0;
	if (sizeM2row < 0)
		sizeM2row = 0;
	if (sizeM2col < 0)
		sizeM2col = 0;
	if (sizeM1col == sizeM2row) {
		draw_matrix_input(sizeM1row, sizeM1col, sizeM2row, sizeM2col);
	}
	else {
		OutputDebugStringA("PRINT");
		pStaticError = new CStatic;
		pStaticError->Create(_T("Wron matrix size. Cannot be multiplied."), WS_CHILD | WS_VISIBLE, CRect(5, 50, 300, 70), this, 108);
	}
}

void MyDlg2::draw_matrix_input(int sizeM1row, int sizeM1col, int sizeM2row, int sizeM2col)
{	
	clearUI();

	ASSERT(sizeM1col == sizeM2row);

	if (vecMatrix1.size() != 0)
		deleteVecMatrix(vecMatrix1);
	if (vecMatrix2.size() != 0)
		deleteVecMatrix(vecMatrix2);
	if (vecMatrixSolution.size() != 0)
		deleteVecMatrix(vecMatrixSolution);
	if (pStaticMultSign) { delete pStaticMultSign; pStaticMultSign = nullptr; }
	if (pButtonCalculate) { delete pButtonCalculate; pButtonCalculate = nullptr; }

	//отрисовка матрицы 1
	{
		vecMatrix1.resize(sizeM1row);
		int x = 10;
		int y = 50;
		int stap = 35;

		for (int i = 0; i < sizeM1row; i++)
		{
			int localY = y + i * stap;
			for (int j = 0; j < sizeM1col; j++) {
				int localX = x + j * stap;

				CEdit *pEdit;
				vecMatrix1.at(i).push_back(pEdit);
				vecMatrix1.at(i).at(j) = new CEdit;
				CRect rect(localX, localY, localX + 30, localY + 30);
				vecMatrix1.at(i).at(j)->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOVSCROLL, rect, this, 106);
				vecMatrix1.at(i).at(j)->SetWindowText(_T("0"));
			}
		}
	}

	// отрисовка значка уможения
	{
		if (sizeM1col > 0) {
			int x = 10 + (vecMatrix1.at(0).size() * 35);
			int y = 50 + ((vecMatrix1.size() * 35) / 2) - 35 / 2;
			pStaticMultSign = new CStatic;
			pStaticMultSign->Create(_T("X"), WS_CHILD | WS_VISIBLE, CRect(x, y, x + 20, y + 20), this, 108);
		}
	}

	//отрисовка второй матрицы 
	{
		vecMatrix2.resize(sizeM2row);
		int x = 10 + (vecMatrix1.at(0).size() * 35) + 20;
		int y = 50;
		int stap = 35;

		for (int i = 0; i < sizeM2row; i++)
		{
			int localY = y + i * stap;
			for (int j = 0; j < sizeM2col; j++) {
				int localX = x + j * stap;

				CEdit *pEdit;
				vecMatrix2.at(i).push_back(pEdit);
				vecMatrix2.at(i).at(j) = new CEdit;
				CRect rect(localX, localY, localX + 30, localY + 30);
				vecMatrix2.at(i).at(j)->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOVSCROLL, rect, this, 106);
				vecMatrix2.at(i).at(j)->SetWindowText(_T("0"));
			}
		}
	}

	//отрисовка книпки calculate
	{
		int x = 10 + (vecMatrix1.at(0).size() * 35) + 20 + (vecMatrix2.at(0).size() * 35) + 20;
		int y = 50 + ((vecMatrix1.size() * 35) / 2) - 35 * 0.75;
		pButtonCalculate = new CMFCButton;
		pButtonCalculate->Create(_T("Calculate"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(x, y, x+100, y+40), this, 1002);
		pButtonCalculate->EnableWindowsTheming(TRUE);
	}
}

void MyDlg2::draw_matrix_solution()
{
	// Перемножаем матрицы
	vector<vector<int>> vSol = multMatrices(fromVecEditToVecInt(vecMatrix1), fromVecEditToVecInt(vecMatrix2));

	// Пререместим кнопку
	delete pButtonCalculate;
	pButtonCalculate = new CMFCButton;
	pButtonCalculate->Create(_T("Calculate"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(320, 5, 380, 30), this, 1002);

	// Рисуем матрицу решений.
	{
		if (vecMatrixSolution.size() != 0)
			deleteVecMatrix(vecMatrixSolution);

		vecMatrixSolution.resize(vSol.size());
		int x = 10 + (vecMatrix1.at(0).size() * 35) + 20 + (vecMatrix2.at(0).size() * 35) + 20;
		int y = 50;
		int stap = 35;

		for (int i = 0; i < vSol.size(); i++)
		{
			int localY = y + i * stap;
			for (int j = 0; j < vSol.at(i).size(); j++) {
				int localX = x + j * stap;

				CEdit *pEdit;
				vecMatrixSolution.at(i).push_back(pEdit);
				vecMatrixSolution.at(i).at(j) = new CEdit;

				CString str;
				_itot_s(vSol.at(i).at(j), str.GetBufferSetLength(8), 8, 10);

				CRect rect(localX, localY, localX + 30, localY + 30);
				vecMatrixSolution.at(i).at(j)->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_READONLY | ES_AUTOVSCROLL | WS_BORDER, rect, this, 1011);
				vecMatrixSolution.at(i).at(j)->SetWindowText(str);
			}
		}
	}
}

void MyDlg2::printInt(int a)
{
	string s;
	s = to_string(a);
	OutputDebugStringA(s.c_str());
	OutputDebugStringA(" ");
}

void MyDlg2::printMtx(vector<vector<int>> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		OutputDebugStringA("\n");
		for (int j = 0; j < v.at(i).size(); j++)
		{
			printInt(v.at(i).at(j));
		}	
	}
}


void MyDlg2::deleteVecMatrix(vector<vector<CEdit*>> &v) {
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v.at(i).size(); j++) {
			delete v.at(i).at(j);
			v.at(i).at(j) = nullptr;
		}
	}
	v.clear();
}

vector<vector<int>> MyDlg2::fromVecEditToVecInt(vector<vector<CEdit*>> v)
{
	vector<vector<int>> vInt(v.size());

	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v.at(i).size(); j++) {

			CString str1;
			v.at(i).at(j)->GetWindowText(str1);
			int val = _ttoi(str1);
			
			vInt.at(i).push_back(val);
		}
	}
	return vInt;
}

vector<vector<int>> MyDlg2::multMatrices(vector<vector<int>> v1, vector<vector<int>> v2)
{
	{
		//Мактрицы перемножить возможно
		ASSERT(v1.at(0).size() == v2.size());

		// Убеждаемся что все строки одинаковой длинны
		for (int i = 0; i < v1.size(); i++)
			ASSERT(v1.at(0).size() == v1.at(i).size());
		for (int i = 0; i < v2.size(); i++)
			ASSERT(v2.at(0).size() == v2.at(i).size());
	}

	vector<vector<int>> vRes(v1.size());

	for (int i = 0; i < vRes.size(); i++)
	{
		vRes.at(i).resize(v2.at(0).size());
	}
	for (int i = 0; i < v1.size(); i++) {
		for (int j = 0; j < v2.at(0).size(); j++) {
			vRes.at(i).at(j) = 0;
			for (int k = 0; k < v1.at(0).size(); k++) {

				vRes.at(i).at(j) += v1.at(i).at(k) * v2.at(k).at(j);
				//m3[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}

	return vRes;
}


void MyDlg2::clearUI()
{
	OutputDebugStringA("WHAAAT");
	delete pStaticError;
	pStaticError = nullptr;
	delete pStaticMultSign;
	pStaticMultSign = nullptr;
	delete pButtonCalculate;
	pButtonCalculate = nullptr;
	deleteVecMatrix(vecMatrix1);
	deleteVecMatrix(vecMatrix2);
	deleteVecMatrix(vecMatrixSolution);
}