// AddBundaryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PhotoPro.h"
#include "AddBundaryDlg.h"
#include "afxdialogex.h"

#define BK1_X 35
#define BK1_Y 39
#define BK1_WIDTH 529
#define BK1_HEIGHT 519
#define BK1_NAME "bk/bk1.jpg"
#define BK2_X 101
#define BK2_Y 118
#define BK2_WIDTH 407
#define BK2_HEIGHT 417
#define BK2_NAME "bk/bk2.jpg"
#define BK3_X 109
#define BK3_Y 134
#define BK3_WIDTH 375
#define BK3_HEIGHT 328
#define BK3_NAME "bk/bk3.jpg"
// AddBundaryDlg 对话框

IMPLEMENT_DYNAMIC(AddBundaryDlg, CDialogEx)

AddBundaryDlg::AddBundaryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddBundaryDlg::IDD, pParent)
{

}

AddBundaryDlg::~AddBundaryDlg()
{
}

void AddBundaryDlg::DoDataExchange(CDataExchange* pDX)
{
	((CButton *)GetDlgItem(IDC_BUN1))->SetCheck(true);
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AddBundaryDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddBundaryDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// AddBundaryDlg 消息处理程序


void AddBundaryDlg::OnBnClickedOk()
{
	if (((CButton *)GetDlgItem(IDC_BUN1))->GetCheck())
	{
		sx = BK1_X;
		sy = BK1_Y;
		width = BK1_WIDTH;
		height = BK1_HEIGHT;
		name = BK1_NAME;
	}
	if (((CButton *)GetDlgItem(IDC_BUN2))->GetCheck())
	{
		sx = BK2_X;
		sy = BK2_Y;
		width = BK2_WIDTH;
		height = BK2_HEIGHT;
		name = BK2_NAME;
	}
	if (((CButton *)GetDlgItem(IDC_BUN3))->GetCheck())
	{
		sx = BK3_X;
		sy = BK3_Y;
		width = BK3_WIDTH;
		height = BK3_HEIGHT;
		name = BK3_NAME;
	}
	CDialogEx::OnOK();
}
