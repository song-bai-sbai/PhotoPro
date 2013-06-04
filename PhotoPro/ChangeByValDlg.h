#pragma once


// ChangeByValDlg 对话框

class ChangeByValDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChangeByValDlg)

public:
	ChangeByValDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ChangeByValDlg();
	int width;
	int height;
// 对话框数据
	enum { IDD = IDD_RESIZEBYVALUE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
