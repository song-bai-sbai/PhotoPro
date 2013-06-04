#pragma once


// ChangeBriDlg 对话框

class ChangeBriDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChangeBriDlg)

public:
	ChangeBriDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ChangeBriDlg();
	double adjust_number;
// 对话框数据
	enum { IDD = IDD_CHANGEBRI };

protected:
	CString input_data;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
