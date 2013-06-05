#pragma once


// RemoveLineDlg 对话框

class RemoveLineDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RemoveLineDlg)

public:
	RemoveLineDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RemoveLineDlg();
	int pLeng;
// 对话框数据
	enum { IDD = IDD_REMOVELINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
