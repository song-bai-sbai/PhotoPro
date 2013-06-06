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
	}
	if (((CButton *)GetDlgItem(IDC_BUN3))->GetCheck())
	{
	}
	CDialogEx::OnOK();
}
