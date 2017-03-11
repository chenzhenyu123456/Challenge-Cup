
// CodeView.cpp : CCodeView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Code.h"
#endif

#include "CodeDoc.h"
#include "CodeView.h"
#include "ChooseDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCodeView

IMPLEMENT_DYNCREATE(CCodeView, CView)

BEGIN_MESSAGE_MAP(CCodeView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CCodeView::OnScreen)
	ON_COMMAND(ID_32772, &CCodeView::OnStation)
	ON_COMMAND(ID_32774, &CCodeView::OnTotal)
	ON_COMMAND(ID_32775, &CCodeView::OnFirstStep)
	ON_COMMAND(ID_32776, &CCodeView::OnSecond)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CCodeView 构造/析构

CCodeView::CCodeView()
{
	// TODO:  在此处添加构造代码
	Case = 0;
}

CCodeView::~CCodeView()
{
}

BOOL CCodeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCodeView 绘制
bool Middle;

void CCodeView::OnDraw(CDC* /*pDC*/)
{
	CCodeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// 清除颜色  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 绘制场景  
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	Work(); //为了更加明了，DrawPicture函数就是绘图的核心代码
	glPopMatrix();
	// 交换缓冲区  
	SwapBuffers(wglGetCurrentDC());
	// TODO:  在此处为本机数据添加绘制代码
	if (!Middle && Case) {
		SendMessage(WM_PAINT);
	}
}


// CCodeView 打印

BOOL CCodeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCodeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CCodeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CCodeView 诊断

#ifdef _DEBUG
void CCodeView::AssertValid() const
{
	CView::AssertValid();
}

void CCodeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCodeDoc* CCodeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCodeDoc)));
	return (CCodeDoc*)m_pDocument;
}
#endif //_DEBUG


// CCodeView 消息处理程序

Work_Station m_station;
Work_Total m_total;
Work_Screen m_screen;
Work_First m_first;
Work_Second m_second;
Show_State m_show;

void CCodeView::Work()
{
	/*CString FilePathName;
	CFileDialog dlg(FALSE);///TRUE为OPEN对话框，FALSE为SAVE AS对话框
	if (dlg.DoModal() == IDOK)
	FilePathName = dlg.GetPathName();
	MessageBox(FilePathName);*/
	CRect rc; GetWindowRect(&rc);
	int cx = rc.Width(); int cy = rc.Height();
	
	if (Case == 0) {
		m_show.Display(1);
		return;
	}
	else if(Middle) {
		m_show.Display(2);
		Middle = false;
		return;
	}
	switch (Case) {
	case 1:
		m_station.DirectoryList(InputPath); 
		m_show.Display(3);
		break;
	case 2:
		m_total.Work2_Init();
		m_total.DirectoryList(InputPath);
		m_show.Display(3);
		break;
	case 3:
		m_screen.DirectoryList(OutputPath);
		m_show.Display(3);
		break;
	case 4:
		m_first.DirectoryList(InputPath);
		m_show.Display(3);
		break;
	case 5:
		m_second.Last();
		m_show.Display(3);
		break;
	}
	Case = 0;
	start = false;
}


bool CCodeView::ChooseInputDirectory(char *szPath) 
{	   
	CString str;
	ZeroMemory(szPath, sizeof(szPath));
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "请选择需要读入的目录：";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	// 弹出选择目录对话框  
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	if (lp && SHGetPathFromIDList(lp, szPath)) {
		str.Format("选择的目录为 %s", szPath);
		AfxMessageBox(str);
		return true;
	}
	else {
		AfxMessageBox("无效的目录，请重新选择！");
		return false;
	}
}

bool CCodeView::ChooseOutputDirectory(char *szPath)
{
	CString str;
	ZeroMemory(szPath, sizeof(szPath));
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "请选择需要输出的目录：";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	// 弹出选择目录对话框  
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	if (lp && SHGetPathFromIDList(lp, szPath)) {
		str.Format("选择的目录为 %s", szPath);
		AfxMessageBox(str);
		return true;
	}
	else {
		AfxMessageBox("无效的目录，请重新选择！");
		return false;
	}
}

void CCodeView::OnScreen() // 筛选数据
{	
	// TODO:  在此添加命令处理程序代码
	CChooseDialog dlg;
	dlg.DoModal();
	if (start) {
		Case = 3;
		Middle = true;
		SendMessage(WM_PAINT);
	}
}


void CCodeView::OnStation()
{
	// TODO:  在此添加命令处理程序代码
	CChooseDialog dlg;
	dlg.DoModal();
	if (start) {
		Case = 1;
		Middle = true;
		SendMessage(WM_PAINT);
	}
}


void CCodeView::OnTotal()
{
	// TODO:  在此添加命令处理程序代码
	CChooseDialog dlg;
	dlg.DoModal();
	if (start) {
		Case = 2;
		Middle = true;
		SendMessage(WM_PAINT);
	}
}


bool CCodeView::ChooseInputFile(char *szPath)
{
	CString str;
	ZeroMemory(szPath, sizeof(szPath));
	BROWSEINFO bi;
	bi.hwndOwner = 0;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "请选择需要输入的文件：";
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	// 弹出选择目录对话框  
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	if (lp && SHGetPathFromIDList(lp, szPath)) {
		str.Format("选择的文件为 %s", szPath);
		AfxMessageBox(str);
		return true;
	}
	else {
		AfxMessageBox("无效的文件，请重新选择！");
		return false;
	}
}


bool CCodeView::ChooseOutputFile(char *szPath)
{
	CString str;
	ZeroMemory(szPath, sizeof(szPath));
	BROWSEINFO bi;
	bi.hwndOwner = 0;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "请选择需要输出的文件：";
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	// 弹出选择目录对话框  
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	if (lp && SHGetPathFromIDList(lp, szPath)) {
		str.Format("选择的文件为 %s", szPath);
		AfxMessageBox(str);
		return true;
	}
	else {
		AfxMessageBox("无效的文件，请重新选择！");
		return false;
	}
	return false;
}



void CCodeView::OnFirstStep()
{
	// TODO:  在此添加命令处理程序代码
	CChooseDialog dlg;
	dlg.DoModal();
	if (start) {
		Case = 4;
		Middle = true;
		SendMessage(WM_PAINT);
	}
}


void CCodeView::OnSecond()
{
	// TODO:  在此添加命令处理程序代码
	CChooseDialog dlg;
	dlg.DoModal();
	if (start) {
		Case = 5;
		Middle = true;
		SendMessage(WM_PAINT);
	}
}


bool CCodeView::bSetDCPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), // 结构的大小  
		1, // 结构的版本  
		PFD_DRAW_TO_WINDOW | // 在窗口(而不是位图)中绘图  
		PFD_SUPPORT_OPENGL | // 支持在窗口中进行OpenGL调用  
		PFD_DOUBLEBUFFER, // 双缓冲模式  
		PFD_TYPE_RGBA, // RGBA颜色模式  
		32, // 需要32位颜色  
		0, 0, 0, 0, 0, 0, // 不用于选择模式  
		0, 0, // 不用于选择模式  
		0, 0, 0, 0, 0, // 不用于选择模式  
		16, // 深度缓冲区的大小  
		0, // 在此不使用  
		0, // 在此不使用  
		0, // 在此不使用  
		0, // 在此不使用  
		0, 0, 0 // 在此不使用  
	};
	// 选择一种与pfd所描述的最匹配的像素格式  
	// 为设备环境设置像素格式  
	int pixelformat;
	if ((pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0) {
		MessageBox("ChoosePixelFormat failed");
		return FALSE;
	}
	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE) {
		MessageBox("SetPixelFormat failed");
		return FALSE;
	}
	return TRUE;
}


int CCodeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	// 创建DC  

	m_pDC = new CClientDC(this);
	ASSERT(m_pDC != NULL);
	// 选择像素格式  
	if (!bSetDCPixelFormat()) return -1;
	// 创建渲染环境, 并使它成为当前渲染环境  
	m_hRC = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	return 0;
}


void CCodeView::OnDestroy()
{
	CView::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
	// 释放资源  
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hRC);
	delete m_pDC;
}


void CCodeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	glClearColor(0, 0, 0, 0);
}


void CCodeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	glViewport(0, 0, (GLsizei)cx, (GLsizei)cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 10, 0, 10);
}
