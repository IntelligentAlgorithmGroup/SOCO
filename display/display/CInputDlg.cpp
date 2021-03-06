// CInputDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "display.h"
#include "CInputDlg.h"
#include "afxdialogex.h"


// CInputDlg 对话框

IMPLEMENT_DYNAMIC(CInputDlg, CDialog)

CInputDlg::CInputDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_INPUT, pParent)
	, i_funcnum(0)
{

}

CInputDlg::~CInputDlg()
{
}

void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT, i_funcnum);
	DDV_MinMaxInt(pDX, i_funcnum, 0, 30);
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialog)
END_MESSAGE_MAP()


// CInputDlg 消息处理程序
