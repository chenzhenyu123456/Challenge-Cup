
// CodeView.h : CCodeView 类的接口
//

#pragma once


class CCodeView : public CView
{
protected: // 仅从序列化创建
	CCodeView();
	DECLARE_DYNCREATE(CCodeView)
private:
	HGLRC m_hRC;
	CClientDC* m_pDC;
public:
	int Case;

// 特性
public:
	CCodeDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CCodeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // CodeView.cpp 中的调试版本
inline CCodeDoc* CCodeView::GetDocument() const
   { return reinterpret_cast<CCodeDoc*>(m_pDocument); }
#endif

