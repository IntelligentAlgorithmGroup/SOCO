
// displayView.cpp: CdisplayView 类的实现
//

#include "stdafx.h"
#include <string.h>
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "display.h"
#endif

#include "displayDoc.h"
#include "displayView.h"
#include "cec17_test_func.h"
#include "CInputDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CdisplayView

IMPLEMENT_DYNCREATE(CdisplayView, CView)

BEGIN_MESSAGE_MAP(CdisplayView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SOCO, &CdisplayView::OnSoco)
END_MESSAGE_MAP()

// CdisplayView 构造/析构

CdisplayView::CdisplayView()
{
	// TODO: 在此处添加构造代码

}

CdisplayView::~CdisplayView()
{
}

BOOL CdisplayView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CdisplayView 绘图

void CdisplayView::my_test(double *x, double *f, int nx, int mx, int func_num)
{
	if (func_num == 0)
	{
		for (int i = 0; i < mx; i++) {
			double tmp = 0;
			for (int j = 0; j < nx; j++) {
				tmp += x[i*nx + j] * pow(-func_num, j);
			}
			f[i] = /*func_num * 20+*/ fabs(tmp);
			//printf("%lf\n", f[i]);
		}
	}
	else cec17_test_func(x, f, nx, mx, func_num);
}

int CdisplayView::get_one(int _mx, int i = -1, int p1 = -1, int p2 = -1)
{
	int r = rand() % _mx;
	while (r == i || r == p1 || r == p2) {
		r = rand() % _mx;
	}
	return r;
}

double CdisplayView::_fi(double *f, int p1, int p2, int p3)
{
	double Fl = 0.1;
	double Fu = 0.9;
	double fb, fm, fw;
	if (f[p1] < f[p2]) {
		if (f[p1] < f[p3]) {
			fb = f[p1];
			fm = (f[p2] < f[p3]) ? f[p2] : f[p3];
			fw = (f[p2] >= f[p3]) ? f[p2] : f[p3];
		}
		else {
			fb = f[p3];
			fm = f[p1];
			fw = f[p2];
		}
	}
	else {
		if (f[p2] < f[p3]) {
			fb = f[p2];
			fm = (f[p1] < f[p3]) ? f[p1] : f[p3];
			fw = (f[p1] >= f[p3]) ? f[p1] : f[p3];
		}
		else {
			fb = f[p3];
			fm = f[p2];
			fw = f[p1];
		}
	}
	double fi = Fl + (Fu - Fl)*((fm - fb) / (fw - fb));
	return fi;
}

double CdisplayView::_cri(double *f, int i, double f_ave, double f_min, double f_max)
{
	double crl = 0.1;
	double cru = 0.6;
	double cri = crl;
	if (f[i] > f_ave) {
		cri = crl + (cru - crl) * ((f[i] - f_min) / (f_max - f_min));
	}
	return cri;
}

void CdisplayView::OnDraw(CDC* pDC)
{
	CdisplayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	// TODO: 在此处为本机数据添加绘制代码

	double top = 1e9;
	double bottom = _funcnum * 100;
	

	int _mx = 50;
	int _nx = 10;
	double x[500];
	double _min = -100;
	double _max = 100;
	int iter_times = 500;
	double F = 0.5;
	double h[500]; //mutate
	double cr = 0.8;
	double v[500]; //cross

	double f[50];
	double f_min;
	double f_max;
	double f_total;
	double f_ave;
	double x_best[10];
	double fv[50];


	double dx[5005]; //pos
	double _f[505];	//value
	double _v[5005];	//speed
	double global_best_pos[505];
	double global_best_val;
	double local_best_pos[5005];
	double local_best_val[505];
	int dim = 10;	//dimension
	int sz = 500;	//number
	double pos_max = 10;
	double pos_min = -10;
	double v_max = 10;
	double v_min = -10;
	int times = iter_times;
	double path = 0.8; //步长

	RECT rect;
	GetClientRect(&rect);
	int iW = rect.right, iH = rect.bottom;
	double ipw, iph;
	

	CPen pen, bpen, rpen, dpen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	bpen.CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
	rpen.CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
	dpen.CreatePen(PS_DOT, 1, RGB(128, 128, 128));
	pDC->SelectObject(&pen);

	//pDC->SetViewportOrg(50, 50);

	wchar_t buf[40];

	
	

	

	//(1)种群初始化
	for (int i = 0; i < _mx; i++) {
		for (int j = 0; j < _nx; j++) {
			x[i*_nx + j] = _min + (rand() % 10000 / 10000.0) * (_max - _min);
		}
	}

	//printf("begin the %d func\n", _funcnum);
	

	for (int g = 0; g < iter_times; g++) {
		my_test(x, f, _nx, _mx, _funcnum);
		//cec17_test_func(x, f, _nx, _mx, _funcnum);
		f_min = f[0];
		f_max = f[0];
		f_total = f[0];
		for (int j = 0; j < _nx; j++) {
			x_best[j] = x[j];
		}
		for (int i = 1; i < _mx; i++) {
			if (f_min > f[i]) {
				f_min = f[i];
				for (int j = 0; j < _nx; j++) {
					x_best[j] = x[i*_nx + j];
				}
			}
			if (f_max < f[i]) {
				f_max = f[i];
			}
			f_total += f[i];
		}
		f_ave = f_total / _mx;

		if (g == 0) {
			top = f_min;
			if (top < bottom + 1000) top = bottom + 1000;
			if (top > bottom + 10000) top = bottom + 10000;
			ipw = (iW - 100) / iter_times;
			iph = (iH - 100) / (top - bottom);
			pDC->Rectangle(50, 50, iW - 50, iH - 50);
			pDC->SelectObject(dpen);
			for (int i = 0; i <= 10; i++) {
				swprintf_s(buf, 40, L"%d", i * (iter_times / 10));
				pDC->TextOutW(50 + i * (iW - 100) / 10, iH - 40, buf);
				pDC->MoveTo(50 + i * (iW - 100) / 10, iH - 50);
				pDC->LineTo(50 + i * (iW - 100) / 10, 50);
			}

			for (int j = 0; j <= 8; j++) {
				swprintf_s(buf, 40, L"%d", (int)(bottom + j * (top - bottom) / 8));
				pDC->TextOutW(10, iH - 50 - (j * ((iH - 100) / 8)), buf);
				pDC->MoveTo(50, iH - 50 - (j * ((iH - 100) / 8)));
				pDC->LineTo(iW - 50, iH - 50 - (j * ((iH - 100) / 8)));
			}

			pDC->SelectObject(bpen);
			pDC->MoveTo(50, 50);
		}
		
		//printf("iter times: %d, fitness :%lf\n", g, f_min);

		int tmp = f_min;
		if (tmp > top) tmp = top;
		tmp = iH - 50 - (tmp - bottom)*iph;
		
		/*if(g > 0)*/ pDC->LineTo(50 + g * ipw, tmp);
		pDC->MoveTo(50 + g * ipw, tmp);

		//(2)变异
		for (int i = 0; i < _mx; i++) {
			int p1 = get_one(_mx, i, -1, -1);
			int p2 = get_one(_mx, i, p1, -1);
			int p3 = get_one(_mx, i, p1, p2);
			double Fi = _fi(f, p1, p2, p3);
			for (int j = 0; j < _nx; j++) {
				h[i*_nx + j] = x[p1*_nx + j] + Fi * (x[p2*_nx + j] - x[p3*_nx + j]);
			}
			//(3)交叉
			double cri = _cri(f, i, f_ave, f_min, f_max);
			if ((rand() % 10000 / 10000.0) <= cri) {
				for (int j = 0; j < _nx; j++) {
					v[i*_nx + j] = h[i*_nx + j];
				}
			}
			else {
				for (int j = 0; j < _nx; j++) {
					v[i*_nx + j] = x[i*_nx + j];
				}
			}
		}
		//(4)选择
		my_test(v, fv, _nx, _mx, _funcnum);
		//cec17_test_func(v, fv, _nx, _mx, _funcnum);
		for (int i = 0; i < _mx; i++) {
			if (fv[i] < f[i]) {
				for (int j = 0; j < _nx; j++) {
					x[i*_nx + j] = v[i*_nx + j];
				}
			}
		}
	}

	pDC->MoveTo(50, 50);
	pDC->SelectObject(rpen);

	global_best_val = 1e9;
	for (int i = 0; i < sz; i++) {
		local_best_val[i] = 1e9;
		for (int j = 0; j < dim; j++) {
			dx[i * dim + j] = pos_min + (pos_max - pos_min) * (rand() % 10000 / 10000.0);
			_v[i * dim + j] = v_min + (v_max - v_min) * (rand() % 10000 / 10000.0);
		}
	}
	//���� 
	for (int t = 0; t < times; t++) {
		//cec17_test_func(dx, f, dim, sz, func_num);
		my_test(dx, _f, dim, sz, _funcnum);
		//�޸ľֲ���ȫ������ֵ 
		for (int i = 0; i < sz; i++) {
			if (local_best_val[i] > _f[i]) {
				for (int j = 0; j < dim; j++) {
					local_best_pos[i * dim + j] = dx[i * dim + j];
				}
				local_best_val[i] = _f[i];
			}
			if (global_best_val > _f[i]) {
				for (int j = 0; j < dim; j++) {
					global_best_pos[j] = dx[i * dim + j];
				}
				global_best_val = _f[i];
			}
		}
		//�����ٶȲ��޸�����λ�� 
		for (int i = 0; i < sz; i++) {
			for (int j = 0; j < dim; j++) {
				double local_diff = local_best_pos[i * dim + j] - dx[i * dim + j];
				double global_diff = global_best_pos[j] - dx[i * dim + j];
				_v[i * dim + j] += path * (rand() % 10000 / 10000.0) * local_diff + path * (rand() % 10000 / 10000.0) * global_diff;
				dx[i * dim + j] += _v[i * dim + j];
			}
		}
		//printf("Times: %d, Best: %.6f", t, global_best_val);
		//for(int i = 0; i < dim; i++){
			//printf("%.2f, ", global_best_pos[i]);
		//}
		//puts("");
		if (global_best_val > top) global_best_val = top;
		/*if(t > 0)*/ pDC->LineTo(50 + t * ipw, (int)iH - 50 - (global_best_val-bottom)*iph);
		pDC->MoveTo(50 + t * ipw, (int)iH - 50 - (global_best_val-bottom)*iph);
	}

}


// CdisplayView 打印

BOOL CdisplayView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CdisplayView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CdisplayView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CdisplayView 诊断

#ifdef _DEBUG
void CdisplayView::AssertValid() const
{
	CView::AssertValid();
}

void CdisplayView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CdisplayDoc* CdisplayView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CdisplayDoc)));
	return (CdisplayDoc*)m_pDocument;
}
#endif //_DEBUG


// CdisplayView 消息处理程序


void CdisplayView::OnSoco()
{
	// TODO: 在此添加命令处理程序代码
	CInputDlg dlg; // 创建对话框对象
	dlg.i_funcnum = _funcnum;
	if (dlg.DoModal() == IDOK) { // 显示对话框
		_funcnum = dlg.i_funcnum;
	}
	RedrawWindow();
}
