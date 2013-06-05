
// PhotoProDlg.h : 头文件
//

#pragma once
#include <core\types_c.h>
#include "CvvImage.h"
#include "Resource.h"
#include "PhotoInfo.h"

// CPhotoProDlg 对话框
class CPhotoProDlg : public CDialogEx
{
// 构造
public:
	CPhotoProDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PHOTOPRO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	IplImage * src_img;
	IplImage * temp_img;
	IplImage * dst_img;
	IplImage * logoORwm;
	HCURSOR m_HArrow;
	HCURSOR m_HCross;
	HCURSOR m_HHand;
	bool isChoosePoint;
	bool isChooseArea;
	bool isBeginDraw;
	PhotoInfo pi;
	RECT    m_recDrawing;
	HPEN    m_penDrawing;
	POINT   m_ptBegin;
	int img_OP;
	CString inputText;
	CvScalar textColor;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	void DrawDstImg();
	void DrawSrcImg();
	void UpdateDstImg(IplImage * modifiedImg);
	void drawRectangle(CPoint point);
	void doOperation(int op, CPoint sp, CPoint ep );
	void doOperationForPoint(int op,CPoint p);
	afx_msg void OnBnClickedShowIMG();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedLoadIMG();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedSaveImg();
	afx_msg void OnBnClickedDoSmooth();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedAddMosaic();
	afx_msg void OnBnClickedUsmSharp();
	afx_msg void OnBnClickedAllSharp();
	afx_msg void OnBnClickedAllBlur();
	afx_msg void OnBnClickedResizeByTimes();
	afx_msg void OnBnClickedRepair();
	afx_msg void OnBnClickedChangeBri();
	afx_msg void OnBnClickedChangeCon();
	afx_msg void OnBnClickedResizeByVal();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedClipping();
	afx_msg void OnBnClickedRotate();
	afx_msg void OnBnClickedAddLOGO();
	afx_msg void OnBnClickedAddWM();
	afx_msg void OnBnClickedAddText();
};
