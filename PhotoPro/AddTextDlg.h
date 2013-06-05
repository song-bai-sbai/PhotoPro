#pragma once
#include <core\types_c.h>


// AddTextDlg 对话框

class AddTextDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddTextDlg)

public:
	AddTextDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddTextDlg();

// 对话框数据
	enum { IDD = IDD_ADDTEXT };

	CString text;
	CvScalar color;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
