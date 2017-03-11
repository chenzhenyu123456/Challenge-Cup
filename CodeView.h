
// CodeView.h : CCodeView ��Ľӿ�
//

#pragma once


class CCodeView : public CView
{
protected: // �������л�����
	CCodeView();
	DECLARE_DYNCREATE(CCodeView)
private:
	HGLRC m_hRC;
	CClientDC* m_pDC;
public:
	int Case;

// ����
public:
	CCodeDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CCodeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	void Work();
	bool ChooseInputDirectory(char *szPath);
	bool ChooseOutputDirectory(char *szPath);
	afx_msg void OnScreen();
	afx_msg void OnStation();
	afx_msg void OnTotal();
	bool ChooseInputFile(char *szPath);
	bool ChooseOutputFile(char *szPath);
	afx_msg void OnFirstStep();
	afx_msg void OnSecond();
	bool bSetDCPixelFormat();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // CodeView.cpp �еĵ��԰汾
inline CCodeDoc* CCodeView::GetDocument() const
   { return reinterpret_cast<CCodeDoc*>(m_pDocument); }
#endif

