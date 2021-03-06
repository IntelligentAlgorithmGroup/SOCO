
// displayView.h: CdisplayView 类的接口
//

#pragma once


class CdisplayView : public CView
{
protected: // 仅从序列化创建
	CdisplayView();
	DECLARE_DYNCREATE(CdisplayView)

// 特性
public:
	CdisplayDoc* GetDocument() const;
	int _funcnum = 0;

// 操作
public:
	void my_test(double *, double *, int, int, int);
	int get_one(int, int, int, int);
	double _fi(double *, int, int, int);
	double _cri(double *, int, double, double, double);

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
	virtual ~CdisplayView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSoco();
};

#ifndef _DEBUG  // displayView.cpp 中的调试版本
inline CdisplayDoc* CdisplayView::GetDocument() const
   { return reinterpret_cast<CdisplayDoc*>(m_pDocument); }
#endif

