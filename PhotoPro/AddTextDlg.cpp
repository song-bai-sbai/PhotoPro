// AddTextDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PhotoPro.h"
#include "AddTextDlg.h"
#include "afxdialogex.h"
#include <core\types_c.h>


// AddTextDlg 对话框

IMPLEMENT_DYNAMIC(AddTextDlg, CDialogEx)

AddTextDlg::AddTextDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddTextDlg::IDD, pParent)
{

}

AddTextDlg::~AddTextDlg()
{
}

void AddTextDlg::DoDataExchange(CDataExchange* pDX)
{
	((CButton *)GetDlgItem(IDC_WHITE))->SetCheck(true);
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AddTextDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddTextDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// AddTextDlg 消息处理程序


void AddTextDlg::OnBnClickedOk()
{
	CString input_data;
	GetDlgItem(IDC_TEXT)->GetWindowText(input_data);
	if (input_data=="" )
	{
		AfxMessageBox("请输入文字。");

	}
	else
	{
		text = input_data;
		if (((CButton *)GetDlgItem(IDC_WHITE))->GetCheck())
		{
			color = cvScalar(255,255,255,0);
		}
		if (((CButton *)GetDlgItem(IDC_BLACK))->GetCheck())
		{
			color = cvScalar(0,0,0,0);
		}
		if (((CButton *)GetDlgItem(IDC_RED))->GetCheck())
		{
			color = cvScalar(255,0,255,0);
		}
		if (((CButton *)GetDlgItem(IDC_BLUE))->GetCheck())
		{
			color = cvScalar(0,0,255,0);
		}
		if (((CButton *)GetDlgItem(IDC_YELLOW))->GetCheck())
		{
			color = cvScalar(255,255,0,0);
		}
		if (((CButton *)GetDlgItem(IDC_GREEN))->GetCheck())
		{
			color = cvScalar(0,128,0,0);
		}
		CDialogEx::OnOK();	
	}
}
