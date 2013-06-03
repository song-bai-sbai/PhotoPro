// ChangeBriDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PhotoPro.h"
#include "ChangeBriDlg.h"
#include "afxdialogex.h"
#include "Resource.h"


// ChangeBriDlg 对话框

IMPLEMENT_DYNAMIC(ChangeBriDlg, CDialogEx)

ChangeBriDlg::ChangeBriDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChangeBriDlg::IDD, pParent)
{

}

ChangeBriDlg::~ChangeBriDlg()
{
}

void ChangeBriDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChangeBriDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ChangeBriDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ChangeBriDlg 消息处理程序


void ChangeBriDlg::OnBnClickedOk()
{
	GetDlgItem(IDC_DATA)->GetWindowText(input_data);
	CDialogEx::OnOK();
}
