#pragma once


// ResizeTimesDlg 对话框

class ResizeTimesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ResizeTimesDlg)

public:
	ResizeTimesDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ResizeTimesDlg();
	double times;
// 对话框数据
	enum { IDD = IDD_RESIZEBYTIMES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
