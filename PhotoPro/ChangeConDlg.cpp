// ChangeConDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PhotoPro.h"
#include "ChangeConDlg.h"
#include "afxdialogex.h"


// ChangeConDlg 对话框

IMPLEMENT_DYNAMIC(ChangeConDlg, CDialogEx)

	ChangeConDlg::ChangeConDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChangeConDlg::IDD, pParent)
{

}

ChangeConDlg::~ChangeConDlg()
{
}

void ChangeConDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChangeConDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ChangeConDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ChangeConDlg 消息处理程序


void ChangeConDlg::OnBnClickedOk()
{
	CString input_data;
	GetDlgItem(IDC_CONDATA)->GetWindowText(input_data);
	if (input_data=="" )
	{
		AfxMessageBox("请输入数值。");

	}
	else
	{
		adjust_number = _tstof(input_data);
		if (adjust_number<0)
		{
			AfxMessageBox("输入错误，请重新输入。");
		}
		CDialogEx::OnOK();
	}
}
