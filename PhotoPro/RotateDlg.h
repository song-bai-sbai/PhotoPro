#pragma once


// RotateDlg 对话框

class RotateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RotateDlg)

public:
	RotateDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RotateDlg();
	double angle;
// 对话框数据
	enum { IDD = IDD_ROTATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
