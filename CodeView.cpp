
// CodeView.cpp : CCodeView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CCodeView ����/����

CCodeView::CCodeView()
{
	// TODO:  �ڴ˴���ӹ������
	Case = 0;
}

CCodeView::~CCodeView()
{
}

BOOL CCodeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCodeView ����
bool Middle;

void CCodeView::OnDraw(CDC* /*pDC*/)
{
	CCodeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// �����ɫ  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ���Ƴ���  
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	Work(); //Ϊ�˸������ˣ�DrawPicture�������ǻ�ͼ�ĺ��Ĵ���
	glPopMatrix();
	// ����������  
	SwapBuffers(wglGetCurrentDC());
	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	if (!Middle && Case) {
		SendMessage(WM_PAINT);
	}
}


// CCodeView ��ӡ

BOOL CCodeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CCodeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCodeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CCodeView ���

#ifdef _DEBUG
void CCodeView::AssertValid() const
{
	CView::AssertValid();
}

void CCodeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCodeDoc* CCodeView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCodeDoc)));
	return (CCodeDoc*)m_pDocument;
}
#endif //_DEBUG


// CCodeView ��Ϣ�������

Work_Station m_station;
Work_Total m_total;
Work_Screen m_screen;
Work_First m_first;
Work_Second m_second;
Show_State m_show;

void CCodeView::Work()
{
	/*CString FilePathName;
	CFileDialog dlg(FALSE);///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
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
	bi.lpszTitle = "��ѡ����Ҫ�����Ŀ¼��";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	// ����ѡ��Ŀ¼�Ի���  
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	if (lp && SHGetPathFromIDList(lp, szPath)) {
		str.Format("ѡ���Ŀ¼Ϊ %s", szPath);
		AfxMessageBox(str);
		return true;
	}
	else {
		AfxMessageBox("��Ч��Ŀ¼��������ѡ��");
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
	bi.lpszTitle = "��ѡ����Ҫ�����Ŀ¼��";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	// ����ѡ��Ŀ¼�Ի���  
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	if (lp && SHGetPathFromIDList(lp, szPath)) {
		str.Format("ѡ���Ŀ¼Ϊ %s", szPath);
		AfxMessageBox(str);
		return true;
	}
	else {
		AfxMessageBox("��Ч��Ŀ¼��������ѡ��");
		return false;
	}
}

void CCodeView::OnScreen() // ɸѡ����
{	
	// TODO:  �ڴ���������������
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
	// TODO:  �ڴ���������������
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
	// TODO:  �ڴ���������������
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
	bi.lpszTitle = "��ѡ����Ҫ������ļ���";
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	// ����ѡ��Ŀ¼�Ի���  
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	if (lp && SHGetPathFromIDList(lp, szPath)) {
		str.Format("ѡ����ļ�Ϊ %s", szPath);
		AfxMessageBox(str);
		return true;
	}
	else {
		AfxMessageBox("��Ч���ļ���������ѡ��");
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
	bi.lpszTitle = "��ѡ����Ҫ������ļ���";
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	// ����ѡ��Ŀ¼�Ի���  
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	if (lp && SHGetPathFromIDList(lp, szPath)) {
		str.Format("ѡ����ļ�Ϊ %s", szPath);
		AfxMessageBox(str);
		return true;
	}
	else {
		AfxMessageBox("��Ч���ļ���������ѡ��");
		return false;
	}
	return false;
}



void CCodeView::OnFirstStep()
{
	// TODO:  �ڴ���������������
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
	// TODO:  �ڴ���������������
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
		sizeof(PIXELFORMATDESCRIPTOR), // �ṹ�Ĵ�С  
		1, // �ṹ�İ汾  
		PFD_DRAW_TO_WINDOW | // �ڴ���(������λͼ)�л�ͼ  
		PFD_SUPPORT_OPENGL | // ֧���ڴ����н���OpenGL����  
		PFD_DOUBLEBUFFER, // ˫����ģʽ  
		PFD_TYPE_RGBA, // RGBA��ɫģʽ  
		32, // ��Ҫ32λ��ɫ  
		0, 0, 0, 0, 0, 0, // ������ѡ��ģʽ  
		0, 0, // ������ѡ��ģʽ  
		0, 0, 0, 0, 0, // ������ѡ��ģʽ  
		16, // ��Ȼ������Ĵ�С  
		0, // �ڴ˲�ʹ��  
		0, // �ڴ˲�ʹ��  
		0, // �ڴ˲�ʹ��  
		0, // �ڴ˲�ʹ��  
		0, 0, 0 // �ڴ˲�ʹ��  
	};
	// ѡ��һ����pfd����������ƥ������ظ�ʽ  
	// Ϊ�豸�����������ظ�ʽ  
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

	// TODO:  �ڴ������ר�õĴ�������
	// ����DC  

	m_pDC = new CClientDC(this);
	ASSERT(m_pDC != NULL);
	// ѡ�����ظ�ʽ  
	if (!bSetDCPixelFormat()) return -1;
	// ������Ⱦ����, ��ʹ����Ϊ��ǰ��Ⱦ����  
	m_hRC = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	return 0;
}


void CCodeView::OnDestroy()
{
	CView::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
	// �ͷ���Դ  
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hRC);
	delete m_pDC;
}


void CCodeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	glClearColor(0, 0, 0, 0);
}


void CCodeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	glViewport(0, 0, (GLsizei)cx, (GLsizei)cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 10, 0, 10);
}
