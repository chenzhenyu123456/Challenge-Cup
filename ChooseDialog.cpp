// ChooseDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Code.h"
#include "ChooseDialog.h"
#include "afxdialogex.h"

// CChooseDialog �Ի���

IMPLEMENT_DYNAMIC(CChooseDialog, CDialogEx)

CChooseDialog::CChooseDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChooseDialog::IDD, pParent)
	, m_year(_T(""))
{

}

CChooseDialog::~CChooseDialog()
{
}

void CChooseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON3, m_input);
	DDX_Control(pDX, IDC_BUTTON4, m_output);
	DDX_Text(pDX, IDC_EDIT1, m_year);
}


BEGIN_MESSAGE_MAP(CChooseDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CChooseDialog::OnBnClickedOK)
	ON_BN_CLICKED(IDC_BUTTON2, &CChooseDialog::OnBnClickedCancle)
	ON_BN_CLICKED(IDC_BUTTON3, &CChooseDialog::OnBnClickedInput)
	ON_BN_CLICKED(IDC_BUTTON4, &CChooseDialog::OnBnClickedOutput)
	ON_BN_CLICKED(IDC_BUTTON5, &CChooseDialog::OnBnClickedYearOk)
END_MESSAGE_MAP()

bool flag_input;
bool flag_output;

// CChooseDialog ��Ϣ�������

void CChooseDialog::OnBnClickedOK()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (flag_input && flag_output) {
		start = true;
		SendMessage(WM_CLOSE);
	}
	else {
		if (!flag_input) {
			MessageBox("��ѡ������·����");
		}
		else {
			MessageBox("��ѡ�����·����");
		}
	}
}


void CChooseDialog::OnBnClickedCancle()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	start = false;
	flag_input = flag_output = false;
	SendMessage(WM_CLOSE);
}

bool CChooseDialog::ChooseInputFile(char *szPath)
{
	CString str;
	ZeroMemory(szPath, sizeof(szPath));
	BROWSEINFO bi;
	bi.hwndOwner = 0;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "��ѡ����Ҫ������ļ����ļ���·����";
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	// ����ѡ��Ŀ¼�Ի���  
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	if (lp && SHGetPathFromIDList(lp, szPath)) {
		str.Format("ѡ����ļ����ļ���Ϊ��\n%s", szPath);
		MessageBox(str, "��ʾ");
		return true;
	}
	else {
		MessageBox("��Ч���ļ����ļ��У�������ѡ��", "��ʾ");
		return false;
	}
}


bool CChooseDialog::ChooseOutputFile(char *szPath)
{
	CString str;
	ZeroMemory(szPath, sizeof(szPath));
	BROWSEINFO bi;
	bi.hwndOwner = 0;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "��ѡ����Ҫ������ļ����ļ���·����";
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	// ����ѡ��Ŀ¼�Ի���  
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	if (lp && SHGetPathFromIDList(lp, szPath)) {
		str.Format("ѡ����ļ����ļ���Ϊ��\n%s", szPath);
		MessageBox(str, "��ʾ");
		return true;
	}
	else {
		MessageBox("��Ч���ļ����ļ��У�������ѡ��", "��ʾ");
		return false;
	}
}


void CChooseDialog::OnBnClickedInput()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	flag_input = ChooseInputFile(InputPath);
}


void CChooseDialog::OnBnClickedOutput()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	flag_output = ChooseInputFile(OutputPath);
}


void CChooseDialog::OnBnClickedYearOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);

	year = 0;

	int len = m_year.GetLength();
	for (int i = 0; i < len; i++) {
		if (m_year[i] >= '0' && m_year[i] <= '9') {
			year = year * 10 + (m_year[i] - '0');
		}
		else {
			MessageBox("������2015~4000��������", "��ʾ");
			return;
		}
	}

	if (year < 2015 || year > 4000) {
		MessageBox("������2015~4000��������", "��ʾ");
		return;
	}
	m_input.EnableWindow(true);
	m_output.EnableWindow(true);
}


BOOL CChooseDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_input.EnableWindow(false);
	m_output.EnableWindow(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
