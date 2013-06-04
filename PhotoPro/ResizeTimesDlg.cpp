// ResizeTimesDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PhotoPro.h"
#include "ResizeTimesDlg.h"
#include "afxdialogex.h"
#include "Resource.h"


// ResizeTimesDlg 对话框

IMPLEMENT_DYNAMIC(ResizeTimesDlg, CDialogEx)

ResizeTimesDlg::ResizeTimesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ResizeTimesDlg::IDD, pParent)
{

}

ResizeTimesDlg::~ResizeTimesDlg()
{
}

void ResizeTimesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ResizeTimesDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ResizeTimesDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ResizeTimesDlg 消息处理程序


void ResizeTimesDlg::OnBnClickedOk()
{
	CString input_data;
	GetDlgItem(IDC_RESIZETIMES)->GetWindowText(input_data);
	if (input_data=="" )
	{
		AfxMessageBox("请输入数值。");

	}
	else
	{
		times = _tstof(input_data);
		if (times<0)
		{
			AfxMessageBox("输入错误，请重新输入。");
		}
		CDialogEx::OnOK();	
	}
}
