
// MFCApplication3Dlg.h: файл заголовка
//

#pragma once
#include <vector>
using namespace std;

// Диалоговое окно CMFCApplication3Dlg
class CMFCApplication3Dlg : public CDialogEx
{
// Создание
public:
	CMFCApplication3Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton44();
	afx_msg void OnBnClickedButtonTest();
	void clik_any_button(UINT nID);
	string s;
	CEdit *pEditOutput;
};
