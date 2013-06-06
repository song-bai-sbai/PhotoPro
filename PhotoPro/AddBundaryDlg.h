#pragma once


// AddBundaryDlg 对话框

class AddBundaryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddBundaryDlg)

public:
	AddBundaryDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddBundaryDlg();

// 对话框数据
	enum { IDD = IDD_ADDBUNDARY };
	int sx;
	int sy;
	int width;
	int height;
	CString name;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
