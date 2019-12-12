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
	
	pEditMatrixSize = new CEdit;
	pEditMatrixSize->Create(ES_MULTILINE | ES_AUTOVSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(90, 5, 130, 30), this, 108);
	
	CMFCButton *pButton = new CMFCButton;
	pButton->Create(_T("OK"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(140, 5, 180, 30), this, 1001);
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
	ON_BN_CLICKED(1001, &MyDlg2::draw_matrix_input)
	ON_BN_CLICKED(1002, &MyDlg2::draw_matrix_solution)
END_MESSAGE_MAP()


// Обработчики сообщений MyDlg2

void MyDlg2::draw_matrix_input()
{	
	if (vecMatrix1.size() != 0)
		deleteVecMatrix(vecMatrix1);
	if (vecMatrix2.size() != 0)
		deleteVecMatrix(vecMatrix2);
	if (vecMatrixSolution.size() != 0)
		deleteVecMatrix(vecMatrixSolution);
	if (pStaticMultSign) { delete pStaticMultSign; pStaticMultSign = nullptr; }
	if (pButtonCalculate) { delete pButtonCalculate; pButtonCalculate = nullptr; }

	int sizeM = 0;
	printInt(sizeM);
	//чтение введенных размеров матрицы
	{
		CString sWindowText;
		pEditMatrixSize->GetWindowText(sWindowText);
		sizeM = _ttoi(sWindowText);
		TRACE("x = %d", sizeM);
	}

	if (sizeM < 0)
		sizeM = 0;

	//отрисовка матрицы 1
	{
		vecMatrix1.resize(sizeM);
		int x = 10;
		int y = 50;
		int stap = 35;

		for (int i = 0; i < sizeM; i++)
		{
			int localY = y + i * stap;
			for (int j = 0; j < sizeM; j++) {
				int localX = x + j * stap;
				
				//CEdit* &localEdit = cEditVec.at(i).at(j);
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
		if (sizeM > 0) {
			vecMatrix1.size();
			int x = 10 + (vecMatrix1.size() * 35);
			int y = 50 + ((vecMatrix1.size() * 35) / 2) - 35 / 2;
			pStaticMultSign = new CStatic;
			pStaticMultSign->Create(_T("X"), WS_CHILD | WS_VISIBLE, CRect(x, y, x + 20, y + 20), this, 108);
		}
	}

	//отрисовка второй матрицы 
	{
		vecMatrix2.resize(sizeM);
		int x = 10 + (vecMatrix1.size() * 35) + 20;
		int y = 50;
		int stap = 35;

		for (int i = 0; i < sizeM; i++)
		{
			int localY = y + i * stap;
			for (int j = 0; j < sizeM; j++) {
				int localX = x + j * stap;
				//CEdit* &localEdit = cEditVec.at(i).at(j);
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
		int x = 10 + (vecMatrix1.size() * 35) + 20 + (vecMatrix2.size() * 35) + 20;
		int y = 50 + ((vecMatrix1.size() * 35) / 2) - 35 * 0.75;
		pButtonCalculate = new CMFCButton;
		pButtonCalculate->Create(_T("Calculate"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(x, y, x+100, y+40), this, 1002);
		pButtonCalculate->EnableWindowsTheming(TRUE);
	}
}

void MyDlg2::draw_matrix_solution()
{
	// построение матрицы решений
	vector<vector<int>>  v (vecMatrix1.size());
	for (int i = 0; i < v.size(); i++)
	{
		v.at(i).resize(v.size());
	}
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v.size(); j++) {
			v.at(i).at(j) = 0;
			for (int k = 0; k < v.size(); k++) {
				CString str1;
				vecMatrix1.at(i).at(k)->GetWindowText(str1);
				int val1 = _ttoi(str1);

				CString str2;
				vecMatrix2.at(k).at(j)->GetWindowText(str2);
				int val2 = _ttoi(str2);
				v.at(i).at(j) += val1 * val2;
				//OutputDebugStringA("\n");
				//printInt(i); printInt(j); printInt(val1); printInt(val2);
				
				//m3[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}
	//printMtx(v);


	delete pButtonCalculate;
	pButtonCalculate = new CMFCButton;
	pButtonCalculate->Create(_T("Calculate"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(190, 5, 250, 30), this, 1002);

	{
		if (vecMatrixSolution.size() != 0)
			deleteVecMatrix(vecMatrixSolution);

		vecMatrixSolution.resize(vecMatrix1.size());
		int x = 10 + (vecMatrix1.size() * 35) + 20 + (vecMatrix2.size() * 35) + 20;
		int y = 50;
		int stap = 35;

		for (int i = 0; i < v.size(); i++)
		{
			int localY = y + i * stap;
			for (int j = 0; j < v.size(); j++) {
				int localX = x + j * stap;

				CEdit *pEdit;
				vecMatrixSolution.at(i).push_back(pEdit);
				vecMatrixSolution.at(i).at(j) = new CEdit;

				CString str;
				_itot_s(v.at(i).at(j), str.GetBufferSetLength(8), 8, 10);

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
		for (int j = 0; j < v.size(); j++)
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