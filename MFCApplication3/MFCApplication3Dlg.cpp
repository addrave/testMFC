
// MFCApplication3Dlg.cpp: файл реализации
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"
#include "afxbutton.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdint.h>
#include "MyDlg2.h"
#include "Calculatecpp.cpp"
using namespace std;


// Диалоговое окно CMFCApplication3Dlg

CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION3_DIALOG, pParent)
{

}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON44, &CMFCApplication3Dlg::OnBnClickedButton44)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CMFCApplication3Dlg::OnBnClickedButtonTest)
	ON_COMMAND_RANGE(1000, 1100, &CMFCApplication3Dlg::clik_any_button)
END_MESSAGE_MAP()


// Обработчики сообщений CMFCApplication3Dlg

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//Создание интерфейса калькулятора
	{
		CMFCButton *n1 = new CMFCButton;
		n1->Create(_T("1"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(100, 300, 130, 330), this, 1001);
		n1->SetFaceColor(RGB(0, 255, 255), true);
		CMFCButton *n2 = new CMFCButton;
		n2->Create(_T("2"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(140, 300, 170, 330), this, 1002);
		n2->SetFaceColor(RGB(16, 255, 239), true);
		CMFCButton *n3 = new CMFCButton;
		n3->Create(_T("3"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(180, 300, 210, 330), this, 1003);
		n3->SetFaceColor(RGB(32, 255, 223), true);
		CMFCButton *n4 = new CMFCButton;
		n4->Create(_T("4"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(100, 260, 130, 290), this, 1004);
		n4->SetFaceColor(RGB(48, 255, 207), true);
		CMFCButton *n5 = new CMFCButton;
		n5->Create(_T("5"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(140, 260, 170, 290), this, 1005);
		n5->SetFaceColor(RGB(54, 255, 191), true);
		CMFCButton *n6 = new CMFCButton;
		n6->Create(_T("6"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(180, 260, 210, 290), this, 1006);
		n6->SetFaceColor(RGB(70, 255, 175), true);
		CMFCButton *n7 = new CMFCButton;
		n7->Create(_T("7"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(100, 220, 130, 250), this, 1007);
		n7->SetFaceColor(RGB(86, 255, 159), true);
		CMFCButton *n8 = new CMFCButton;
		n8->Create(_T("8"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(140, 220, 170, 250), this, 1008);
		n8->SetFaceColor(RGB(102, 255, 143), true);
		CMFCButton *n9 = new CMFCButton;
		n9->Create(_T("9"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(180, 220, 210, 250), this, 1009);
		n9->SetFaceColor(RGB(118, 255, 127), true);
		CMFCButton *n0 = new CMFCButton;
		n0->Create(_T("0"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(140, 340, 170, 370), this, 1000);
		n0->SetFaceColor(RGB(230, 255, 16), true);
		CMFCButton *opMinus = new CMFCButton;
		opMinus->Create(_T("—"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(220, 300, 280, 330), this, 1091);
		opMinus->SetFaceColor(RGB(182, 255, 63), true);
		CMFCButton *opPlus = new CMFCButton;
		opPlus->Create(_T("+"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(220, 340, 280, 370), this, 1092);
		opPlus->SetFaceColor(RGB(198, 255, 47), true);
		CMFCButton *opMlt = new CMFCButton;
		opMlt->Create(_T("X"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(220, 260, 280, 290), this, 1093);
		opMlt->SetFaceColor(RGB(166, 255, 79), true);
		CMFCButton *opDiv = new CMFCButton;
		opDiv->Create(_T("/"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(220, 220, 280, 250), this, 1094);
		opDiv->SetFaceColor(RGB(150, 255, 95), true);
		CMFCButton *opAC = new CMFCButton;
		opAC->Create(_T("AC"), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(220, 180, 280, 210), this, 1095);
		opAC->SetFaceColor(RGB(134, 255, 111), true);
		CMFCButton *opEql = new CMFCButton;
		opEql->Create(_T("="), WS_CHILD | WS_VISIBLE | BS_ICON, CRect(180, 340, 210, 370), this, 1096);
		opEql->SetFaceColor(RGB(214, 255, 31), true);
		pEditOutput = new CEdit;
		pEditOutput->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_READONLY | ES_AUTOVSCROLL | WS_BORDER, CRect(100, 180, 210, 210), this, 900);
	}
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMFCApplication3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
		CDialogEx::OnSysCommand(nID, lParam);
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMFCApplication3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplication3Dlg::OnBnClickedButton44()
{
	MyDlg2 *dlg1 = new MyDlg2;
	dlg1->Create(IDD_DIALOG1, this);
	dlg1->ShowWindow(SW_SHOW);
}

void CMFCApplication3Dlg::clik_any_button(UINT nID)
{
	// Обработка нажатой клавиши калькулятор
	switch (nID)
	{
		case 1000: { s.push_back('0'); wstring path_wstr(s.begin(), s.end()); pEditOutput->SetWindowText(path_wstr.c_str()); break; }
		case 1001: { s.push_back('1'); wstring path_wstr(s.begin(), s.end()); pEditOutput->SetWindowText(path_wstr.c_str()); break; }
		case 1002: { s.push_back('2'); wstring path_wstr(s.begin(), s.end()); pEditOutput->SetWindowText(path_wstr.c_str()); break; }
		case 1003: { s.push_back('3'); wstring path_wstr(s.begin(), s.end()); pEditOutput->SetWindowText(path_wstr.c_str()); break; }
		case 1004: { s.push_back('4'); wstring path_wstr(s.begin(), s.end()); pEditOutput->SetWindowText(path_wstr.c_str()); break; }
		case 1005: { s.push_back('5'); wstring path_wstr(s.begin(), s.end()); pEditOutput->SetWindowText(path_wstr.c_str()); break; }
		case 1006: { s.push_back('6'); wstring path_wstr(s.begin(), s.end()); pEditOutput->SetWindowText(path_wstr.c_str()); break; }
		case 1007: { s.push_back('7'); wstring path_wstr(s.begin(), s.end()); pEditOutput->SetWindowText(path_wstr.c_str()); break; }
		case 1008: { s.push_back('8'); wstring path_wstr(s.begin(), s.end()); pEditOutput->SetWindowText(path_wstr.c_str()); break; }
		case 1009: { s.push_back('9'); wstring path_wstr(s.begin(), s.end()); pEditOutput->SetWindowText(path_wstr.c_str()); break; }
		case 1091: { s.push_back('-'); wstring path_wstr(s.begin(), s.end()); pEditOutput->SetWindowText(path_wstr.c_str()); break; }
		case 1092: { s.push_back('+'); wstring path_wstr(s.begin(), s.end()); pEditOutput->SetWindowText(path_wstr.c_str()); break; }
		case 1093: { s.push_back('*'); wstring path_wstr(s.begin(), s.end()); pEditOutput->SetWindowText(path_wstr.c_str()); break; }
		case 1094: { s.push_back('/'); wstring path_wstr(s.begin(), s.end()); pEditOutput->SetWindowText(path_wstr.c_str()); break; }
		case 1095: { s.clear(); wstring path_wstr(s.begin(), s.end()); pEditOutput->SetWindowText(path_wstr.c_str()); break; }
		case 1096: 
		{ 
			try
			{
				// Внешняя библиотека считает результат операции
				int result = calculator::eval(s);
				s = to_string(result);
			}
			catch (calculator::error& e)
			{
				//std::cerr << e.what() << std::endl;
			}
			wstring path_wstr(s.begin(), s.end()); pEditOutput->SetWindowText(path_wstr.c_str()); break; 
		}
	}
}


void CMFCApplication3Dlg::OnBnClickedButtonTest()	// Unit-tests
{
	MyDlg2 test;
	{
		vector<vector<int>> v1(2);
		v1.at(0) = { 1, 2 };
		v1.at(1) = { 3, 4 };

		vector<vector<int>> v2(2);
		v2.at(0) = { 5, 6 };
		v2.at(1) = { 7, 8 };

		vector<vector<int>> vRes(2);
		vRes.at(0) = { 19, 22 };
		vRes.at(1) = { 43, 50 };

		vector<vector<int>> vRes2(2);
		vRes2.at(0) = { 23, 34 };
		vRes2.at(1) = { 31, 46 };

		ASSERT(vRes  == test.multMatrices(v1, v2));
		ASSERT(vRes2 == test.multMatrices(v2, v1));
	}
	{
		vector<vector<int>> v1(1);
		v1.at(0) = { 1, 2, 3 };

		vector<vector<int>> v2(3);
		v2.at(0) = { 5 };
		v2.at(1) = { 6 };
		v2.at(2) = { 7 };

		vector<vector<int>> vRes(1);
		vRes.at(0) = { 38 };

		vector<vector<int>> vRes2(3);
		vRes2.at(0) = { 5, 10, 15 };
		vRes2.at(1) = { 6, 12, 18 };
		vRes2.at(2) = { 7, 14, 21 };

		ASSERT(vRes  == test.multMatrices(v1, v2));
		ASSERT(vRes2 == test.multMatrices(v2, v1));
	}
	{
		vector<vector<int>> v1(1);
		v1.at(0) = { 5 };

		vector<vector<int>> v2(1);
		v2.at(0) = { 1, 2, 3, 4 };

		vector<vector<int>> vRes(1);
		vRes.at(0) = { 5, 10, 15, 20 };

		ASSERT(vRes == test.multMatrices(v1, v2));
	}
	{
		vector<vector<int>> v1(3);
		v1.at(0) = { 5 };
		v1.at(1) = { -6 };
		v1.at(2) = { 7 };

		vector<vector<int>> v2(1);
		v2.at(0) = { -8 };

		vector<vector<int>> vRes(3);
		vRes.at(0) = {-40 };
		vRes.at(1) = { 48 };
		vRes.at(2) = {-56 };

		ASSERT(vRes == test.multMatrices(v1, v2));
	}
	{
		vector<vector<int>> v1(1);
		v1.at(0) = { 41 };

		vector<vector<int>> v2(1);
		v2.at(0) = { -81 };

		vector<vector<int>> vRes(1);
		vRes.at(0) = { -3321 };

		ASSERT(vRes == test.multMatrices(v1, v2));
	}
	{
		vector<vector<int>> v1(1);
		v1.at(0) = { -0, -0, 0 };

		vector<vector<int>> v2(3);
		v2.at(0) = { 0 };
		v2.at(1) = { -0 };
		v2.at(2) = { 0 };

		vector<vector<int>> vRes(1);
		vRes.at(0) = { 0 };

		vector<vector<int>> vRes2(3);
		vRes2.at(0) = { 0, 0, 0 };
		vRes2.at(1) = { 0, 0, 0 };
		vRes2.at(2) = { 0, 0, 0 };

		ASSERT(vRes == test.multMatrices(v1, v2));
		ASSERT(vRes2 == test.multMatrices(v2, v1));
	}
	{
		vector<vector<int>> v1(1);
		v1.at(0) = { -0, 0, -3 };

		vector<vector<int>> v2(3);
		v2.at(0) = { -5 };
		v2.at(1) = { 0 };
		v2.at(2) = { -7 };

		vector<vector<int>> vRes(1);
		vRes.at(0) = { 21 };

		vector<vector<int>> vRes2(3);
		vRes2.at(0) = { 0, 0, 15 };
		vRes2.at(1) = { 0, 0, 0 };
		vRes2.at(2) = { 0, 0, 21 };

		ASSERT(vRes == test.multMatrices(v1, v2));
		ASSERT(vRes2 == test.multMatrices(v2, v1));
	}

	OutputDebugStringA("All Unit Tests success");
}
