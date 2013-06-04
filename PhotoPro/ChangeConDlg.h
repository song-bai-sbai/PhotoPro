#pragma once


// ChangeConDlg 对话框

class ChangeConDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChangeConDlg)

public:
	ChangeConDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ChangeConDlg();
	double adjust_number;
// 对话框数据
	enum { IDD = IDD_CHANGECON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
