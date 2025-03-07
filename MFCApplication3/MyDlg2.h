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
public:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
public:
	void pre_drow_matrix();
	void clearUI();
	void draw_matrix_input(int sizeM1row, int sizeM1col, int sizeM2row, int sizeM2col);
	void draw_matrix_solution();
	void printInt(int a);
	void printMtx(vector<vector<int>> v);
	void deleteVecMatrix(vector<vector<CEdit*>> &v);
	vector<vector<int>> fromVecEditToVecInt(vector<vector<CEdit*>> v);
	vector<vector<int>> multMatrices(vector<vector<int>> v1, vector<vector<int>> v2);

	CEdit *pEditMatrixSize1 = nullptr;
	CEdit *pEditMatrixSize2 = nullptr;
	CEdit *pEditMatrixSize3 = nullptr;
	CEdit *pEditMatrixSize4 = nullptr;

	CStatic *pStaticError = nullptr;
	CStatic *pStaticMultSign = nullptr;			//Multiplication Sign
	CMFCButton *pButtonCalculate = nullptr;
	vector<vector<CEdit*>> vecMatrix1;
	vector<vector<CEdit*>> vecMatrix2;
	vector<vector<CEdit*>> vecMatrixSolution;
};
