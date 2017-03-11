// ChooseDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Code.h"
#include "ChooseDialog.h"
#include "afxdialogex.h"

// CChooseDialog 对话框

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

// CChooseDialog 消息处理程序

void CChooseDialog::OnBnClickedOK()
{
	// TODO:  在此添加控件通知处理程序代码

	if (flag_input && flag_output) {
		start = true;
		SendMessage(WM_CLOSE);
	}
	else {
		if (!flag_input) {
			MessageBox("请选择输入路径！");
		}
		else {
			MessageBox("请选择输出路径！");
		}
	}
}


void CChooseDialog::OnBnClickedCancle()
{
	// TODO:  在此添加控件通知处理程序代码
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
	bi.lpszTitle = "请选择需要输入的文件或文件夹路径：";
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	// 弹出选择目录对话框  
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	if (lp && SHGetPathFromIDList(lp, szPath)) {
		str.Format("选择的文件或文件夹为：\n%s", szPath);
		MessageBox(str, "提示");
		return true;
	}
	else {
		MessageBox("无效的文件或文件夹，请重新选择！", "提示");
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
	bi.lpszTitle = "请选择需要输出的文件或文件夹路径：";
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	// 弹出选择目录对话框  
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	if (lp && SHGetPathFromIDList(lp, szPath)) {
		str.Format("选择的文件或文件夹为：\n%s", szPath);
		MessageBox(str, "提示");
		return true;
	}
	else {
		MessageBox("无效的文件或文件夹，请重新选择！", "提示");
		return false;
	}
}


void CChooseDialog::OnBnClickedInput()
{
	// TODO:  在此添加控件通知处理程序代码
	flag_input = ChooseInputFile(InputPath);
}


void CChooseDialog::OnBnClickedOutput()
{
	// TODO:  在此添加控件通知处理程序代码
	flag_output = ChooseInputFile(OutputPath);
}


void CChooseDialog::OnBnClickedYearOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);

	year = 0;

	int len = m_year.GetLength();
	for (int i = 0; i < len; i++) {
		if (m_year[i] >= '0' && m_year[i] <= '9') {
			year = year * 10 + (m_year[i] - '0');
		}
		else {
			MessageBox("请输入2015~4000的整数！", "提示");
			return;
		}
	}

	if (year < 2015 || year > 4000) {
		MessageBox("请输入2015~4000的整数！", "提示");
		return;
	}
	m_input.EnableWindow(true);
	m_output.EnableWindow(true);
}


BOOL CChooseDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_input.EnableWindow(false);
	m_output.EnableWindow(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
