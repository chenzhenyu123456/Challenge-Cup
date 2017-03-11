#pragma once
#include "afxwin.h"



// CChooseDialog �Ի���

class CChooseDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CChooseDialog)

public:
	CChooseDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChooseDialog();

// �Ի�������
	enum { IDD = IDD_Choose };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOK();
	afx_msg void OnBnClickedCancle();
	bool ChooseInputFile(char *szPath);
	bool ChooseOutputFile(char *szPath);
	afx_msg void OnBnClickedInput();
	afx_msg void OnBnClickedOutput();
	CButton m_input;
	CButton m_output;
	afx_msg void OnBnClickedYearOk();
	virtual BOOL OnInitDialog();
	CString m_year;
};
