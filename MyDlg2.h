#pragma once

#include "stdafx.h"
#include "stdlib.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Диалоговое окно MyDlg2

class MyDlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(MyDlg2)

public:
	MyDlg2(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~MyDlg2();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION3_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();

	void draw_matrix_input();
	void draw_matrix_solution();
	void printInt(int a);
	void printMtx(vector<vector<int>> v);
	void deleteVecMatrix(vector<vector<CEdit*>> &v);

	CEdit *pEditMatrixSize = nullptr;

	CStatic *pStaticMultSign = nullptr;			//Multiplication Sign
	CMFCButton *pButtonCalculate = nullptr;
	vector<vector<CEdit*>> vecMatrix1;
	vector<vector<CEdit*>> vecMatrix2;
	vector<vector<CEdit*>> vecMatrixSolution;
};
