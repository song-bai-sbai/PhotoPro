
// PhotoProDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PhotoPro.h"
#include "PhotoProDlg.h"
#include "afxdialogex.h"
#include "MyImgPro\MySmooth.h"
#include "Resource.h"
#include "MyImgPro\MyResize.h"
#include "ChangePoint.h"
#include "MyImgPro\MySharp.h"
#include "MyImgPro\MyAddMosaic.h"
#include "MyImgPro\MyInpaintig.h"
#include "ChangeBriDlg.h"
#include "MyImgPro\MyBrit_Con.h"
#include "ChangeConDlg.h"
#include "ResizeTimesDlg.h"
#include "ChangeByValDlg.h"
#include "MyImgPro\MyClipping.h"
#include "RotateDlg.h"
#include "MyImgPro\MyRotate.h"
#include "MyImgPro\MyLogo_WM.h"
#include "AddTextDlg.h"
#include "MyImgPro\MyRemoveLine.h"
#include "RemoveLineDlg.h"
#include "MyImgPro\MyBoundary.h"
#include "AddBundaryDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SRC_X 100
#define SRC_Y 10
#define SRC_WIDTH 300
#define SRC_HEIGHT 300
#define DST_X 410
#define DST_Y 10
#define DST_WIDTH 550
#define DST_HEIGHT 550

//Operation
#define ADDMOSAIC 101
#define CLIPPING 102
#define REPAIRIMG 103
#define REMOVELINE 104
#define USMSHARP 105
#define DOSMOOTH 106
#define ADDLOGO 107
#define ADDWM   108
#define ADDTEXT 109
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPhotoProDlg 对话框




CPhotoProDlg::CPhotoProDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPhotoProDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_HArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_HCross = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
	m_HHand = AfxGetApp()->LoadStandardCursor(IDC_HAND);
	src_img = NULL;
	dst_img = NULL;
	temp_img = NULL;
	isChooseArea =  false;
	isBeginDraw = false;
	isChoosePoint = false;
	isRemove = false;
	isBeginLine = false;
	img_OP = 0;
	pLeng = 0;
	SetRectEmpty(&m_recDrawing);
	m_penDrawing = ::CreatePen(PS_DASH, 1, RGB(255, 0, 0));
	pi.setDST_X(DST_X);
	pi.setDST_Y(DST_Y);
}

void CPhotoProDlg::DoDataExchange(CDataExchange* pDX)
{
	GetDlgItem(IDC_SrcImg)->MoveWindow(SRC_X,SRC_Y,SRC_WIDTH,SRC_HEIGHT,FALSE);
	GetDlgItem(IDC_DstImg)->MoveWindow(DST_X,DST_Y,DST_WIDTH,DST_HEIGHT,FALSE);
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPhotoProDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPhotoProDlg::OnBnClickedShowIMG)
	ON_BN_CLICKED(IDC_BUTTON2, &CPhotoProDlg::OnBnClickedUnDo)
	ON_BN_CLICKED(IDC_BUTTON3, &CPhotoProDlg::OnBnClickedLoadIMG)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON4, &CPhotoProDlg::OnBnClickedSaveImg)
	ON_BN_CLICKED(IDC_BUTTON5, &CPhotoProDlg::OnBnClickedDoSmooth)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON6, &CPhotoProDlg::OnBnClickedAddMosaic)
	ON_BN_CLICKED(IDC_BUTTON12, &CPhotoProDlg::OnBnClickedUsmSharp)
	ON_BN_CLICKED(IDC_BUTTON7, &CPhotoProDlg::OnBnClickedAllSharp)
	ON_BN_CLICKED(IDC_BUTTON13, &CPhotoProDlg::OnBnClickedAllBlur)
	ON_BN_CLICKED(IDC_BUTTON10, &CPhotoProDlg::OnBnClickedResizeByTimes)
	ON_BN_CLICKED(IDC_BUTTON11, &CPhotoProDlg::OnBnClickedRepair)
	ON_BN_CLICKED(IDC_BUTTON8, &CPhotoProDlg::OnBnClickedChangeBri)
	ON_BN_CLICKED(IDC_BUTTON9, &CPhotoProDlg::OnBnClickedChangeCon)
	ON_BN_CLICKED(IDC_BUTTON15, &CPhotoProDlg::OnBnClickedResizeByVal)
	ON_BN_CLICKED(IDC_BUTTON18, &CPhotoProDlg::OnBnClickedRemoveLine)
	ON_BN_CLICKED(IDC_BUTTON21, &CPhotoProDlg::OnBnClickedClipping)
	ON_BN_CLICKED(IDC_BUTTON20, &CPhotoProDlg::OnBnClickedRotate)
	ON_BN_CLICKED(IDC_BUTTON14, &CPhotoProDlg::OnBnClickedAddLOGO)
	ON_BN_CLICKED(IDC_BUTTON17, &CPhotoProDlg::OnBnClickedAddWM)
	ON_BN_CLICKED(IDC_BUTTON16, &CPhotoProDlg::OnBnClickedAddText)
	ON_BN_CLICKED(IDC_BUTTON19, &CPhotoProDlg::OnBnClickedAddBun)
END_MESSAGE_MAP()


// CPhotoProDlg 消息处理程序

BOOL CPhotoProDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPhotoProDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPhotoProDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPhotoProDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPhotoProDlg::OnBnClickedShowIMG()
{
	if (src_img!=NULL)
	{
		cvNamedWindow( "Image", 1 );
		cvShowImage( "Image", src_img );
		cvWaitKey(0); 
		cvDestroyWindow( "Image" );
	}

}

void CPhotoProDlg::DrawSrcImg()//max size 300*300
{
	UINT ID = IDC_SrcImg;
	if (src_img->width>SRC_WIDTH||src_img->height>SRC_HEIGHT)
	{
		int l_size = (src_img->width>src_img->height)?src_img->width:src_img->height;
		float times = (float)SRC_WIDTH/l_size;
		GetDlgItem(ID)->MoveWindow(SRC_X,SRC_Y,src_img->width*times,src_img->height*times,FALSE);
	}
	else
	{
		GetDlgItem(ID)->MoveWindow(SRC_X,SRC_Y,src_img->width,src_img->height,FALSE);
	}

	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC= pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf( src_img ); // Copy IMG
	cimg.DrawToHDC( hDC, &rect ); // Draw PIC
	ReleaseDC( pDC );
}

void CPhotoProDlg::DrawDstImg()
{
	UINT ID = IDC_DstImg;
	if (dst_img->width>DST_WIDTH||dst_img->height>DST_HEIGHT)
	{
		int l_size = (dst_img->width>dst_img->height)?dst_img->width:dst_img->height;
		float times = (float)DST_WIDTH/l_size;
		pi.setDstImg_Times(times);
		pi.setResizeWidth(dst_img->width*times);
		pi.setResizeHeight(dst_img->height*times);
		GetDlgItem(ID)->MoveWindow(DST_X,DST_Y,pi.getResizeWidth(),pi.getResizeHeight(),FALSE);
		//GetDlgItem(ID)->SetWindowPos(NULL,DST_X,DST_Y,pi.getResizeWidth(),pi.getResizeHeight(),SWP_NOMOVE);
	}
	else
	{
		pi.setDstImg_Times(1);
		pi.setResizeWidth(dst_img->width);
		pi.setResizeHeight(dst_img->height);
		GetDlgItem(ID)->MoveWindow(DST_X,DST_Y,dst_img->width,dst_img->height,FALSE);
	}

	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC= pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cvvimamg;
	cvvimamg.CopyOf( dst_img ); // Copy IMG
	cvvimamg.DrawToHDC( hDC, &rect ); // Draw PIC
	ReleaseDC( pDC );
	this->OnPaint();
}

void CPhotoProDlg::OnBnClickedLoadIMG()//load img
{
	CFileDialog filedialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"JPG,JPEG,PNG,BMP (*.jpg;*.jpeg;*.png;*.bmp)|*.jpg;*.jpeg;*.png;*.bmp|All Files (*.*)|*.*||", this);
	if(IDOK==filedialog.DoModal())
	{
		if(src_img!=NULL)
		{
			cvReleaseImage(&src_img);
		}
		src_img = cvLoadImage(filedialog.GetPathName(),1);
		dst_img = cvCreateImage(cvGetSize(src_img),IPL_DEPTH_8U,3);
		dst_img = cvCloneImage(src_img);

		temp_img = cvCreateImage(cvGetSize(src_img),IPL_DEPTH_8U,3);
		temp_img = cvCloneImage(src_img);
		GetDlgItem(IDC_SrcImg)->Invalidate();
		GetDlgItem(IDC_DstImg)->Invalidate();
		this->UpdateWindow();
		DrawSrcImg();
		DrawDstImg();
	}
}


void CPhotoProDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (isChooseArea||isRemove)
	{
		if (point.x>DST_X&&point.x<DST_X+pi.getResizeWidth()&&point.y>DST_Y&&point.y<DST_Y+pi.getResizeHeight())
		{
			SetCursor(m_HCross);
		}
		else
		{
			SetCursor(m_HArrow);
		}
		if (isBeginDraw)
		{
			drawRectangle(point);
		}
		if (isBeginLine)
		{
			drawLine(point);
		}

	}
	if (isChoosePoint)
	{
		if (point.x>DST_X&&point.x<DST_X+pi.getResizeWidth()&&point.y>DST_Y&&point.y<DST_Y+pi.getResizeHeight())
		{
			SetCursor(m_HHand);
		}
		else
		{
			SetCursor(m_HArrow);
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CPhotoProDlg::OnBnClickedSaveImg()
{
	if (dst_img!=NULL)
	{
		CFileDialog filedialog(FALSE, "jpg", " ", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			"JPG (*.jpg)| *.jpg|JPEG (*.jpeg)| *.jpeg|PNG (*.png)| *.png|BMP (*.bmp)| *.bmp||", this);
		if(IDOK==filedialog.DoModal())
		{
			CvvImage cimg;
			cimg.CopyOf(dst_img);
			cimg.Save(filedialog.GetPathName());
		}
	}
	else
	{
		AfxMessageBox("请先载入一张照片");
	}	
}

void CPhotoProDlg::UpdateDstImg(IplImage * modifiedImg)
{
	if (modifiedImg== NULL)
	{
		AfxMessageBox("修改失败。");
	}
	else if (src_img ==NULL)
	{
		AfxMessageBox("请先载入一张照片");
	}
	else
	{	
		cvReleaseImage(&temp_img);
		temp_img = cvCreateImage(cvGetSize(dst_img),IPL_DEPTH_8U,3);
		temp_img = cvCloneImage(dst_img);
		cvReleaseImage(&dst_img);
		dst_img = cvCreateImage(cvGetSize(modifiedImg),IPL_DEPTH_8U,3);
		dst_img = cvCloneImage(modifiedImg);
		GetDlgItem(IDC_DstImg)->Invalidate();
		this->UpdateWindow();
		DrawDstImg();
		AfxMessageBox("修改完成。");
	}
}


void CPhotoProDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (isChooseArea==true)
	{
		isBeginDraw=true;
		m_ptBegin = point;
		pi.setStart_pos(point);
	}
	if (isRemove == true)
	{
		m_ptOrign = point;
		pi.setStart_pos(point);
		isBeginLine = true;
		xOldSrc = point.x;
		yOldSrc = point.y;
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CPhotoProDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (isChooseArea==true&&isBeginDraw==true)
	{
		isChooseArea = false;
		isBeginDraw = false;
		SetRect(&m_recDrawing, 0, 0, 0,0);
		pi.setEnd_pos(point);
		CPoint sp= pi.getActualSP();
		CPoint ep=pi.getActualEP();
		doOperation(img_OP,sp,ep);
	}
	if (isChoosePoint==true)
	{
		isChoosePoint = false;
		pi.setEnd_pos(point);
		CPoint ap = pi.getActualEP();
		doOperationForPoint(img_OP,ap);
	}
	if (isRemove == true)
	{
		isRemove = false;
		isBeginLine = false;
		pi.setEnd_pos(point);

		CClientDC dc(this);
		dc.SetROP2(R2_NOT);
		CPen pen(PS_SOLID, 5, RGB(255,0,0));
		CPen *pOldPen = dc.SelectObject(&pen);
		dc.MoveTo(pi.getStart_pos().x,pi.getStart_pos().y);//---- 擦除上次的线条
		dc.LineTo(xOldSrc,yOldSrc);
		dc.SelectObject(pOldPen);

		CPoint sp= pi.getActualSP();
		CPoint ep=pi.getActualEP();
		doOperation(img_OP,sp,ep);
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CPhotoProDlg::drawRectangle(CPoint point)
{
	CDC* pDC = GetDC();
	if (pDC) 
	{
		HDC hdc = pDC->m_hDC;

		// set the drawing mode and the drawing pen.
		int nDrawMode = ::SetROP2(hdc, R2_NOTXORPEN);
		HPEN hOldPen = (HPEN)::SelectObject(hdc, m_penDrawing);

		// erase the last rect
		Rectangle(hdc, m_recDrawing.left, m_recDrawing.top, m_recDrawing.right, m_recDrawing.bottom);
		SetRect(&m_recDrawing, m_ptBegin.x, m_ptBegin.y, point.x, point.y);
		Rectangle(hdc, m_recDrawing.left, m_recDrawing.top, m_recDrawing.right, m_recDrawing.bottom);

		// restore the dc
		SetROP2(hdc, nDrawMode);
		SelectObject(hdc, hOldPen);

		ReleaseDC(pDC);
	}
}

void CPhotoProDlg::drawLine( CPoint point )
{
	CClientDC dc(this);
	dc.SetROP2(R2_NOT);
	CPen pen(PS_SOLID, pLeng, RGB(255,0,0));
	CPen *pOldPen = dc.SelectObject(&pen);
	dc.MoveTo(pi.getStart_pos().x,pi.getStart_pos().y);
	dc.LineTo(point.x,point.y);

	dc.MoveTo(pi.getStart_pos().x,pi.getStart_pos().y);//---- 擦除上次的线条
	dc.LineTo(xOldSrc,yOldSrc);


	xOldSrc=point.x;
	yOldSrc=point.y;
	dc.SelectObject(pOldPen);
}

void CPhotoProDlg::OnBnClickedUnDo()
{
	if (dst_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		IplImage * modifiedImg = cvCreateImage(cvGetSize(temp_img),IPL_DEPTH_8U,3);
		modifiedImg = cvCloneImage(temp_img);
		UpdateDstImg(modifiedImg);
	}
}


void CPhotoProDlg::OnBnClickedAllSharp()
{
	if (dst_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		MySharp ms;
		IplImage * modifiedImg = ms.usmSharp(dst_img);
		UpdateDstImg(modifiedImg);
	}

}


void CPhotoProDlg::OnBnClickedDoSmooth()
{
	if (dst_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		AfxMessageBox("请选择要模糊化的区域。");
		isChooseArea = true;
		img_OP = DOSMOOTH;
	}
}

void CPhotoProDlg::OnBnClickedAllBlur()
{
	if (dst_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		MySmooth ms;
		IplImage * modifiedImg = ms.doSmooth_Gaussian(dst_img);
		UpdateDstImg(modifiedImg);
	}
}

void CPhotoProDlg::OnBnClickedAddMosaic()
{
	if (dst_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		AfxMessageBox("请选择要打马赛克的区域。");
		isChooseArea = true;
		img_OP = ADDMOSAIC;
	}
}

void CPhotoProDlg::OnBnClickedUsmSharp()
{
	if (dst_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		AfxMessageBox("请选择要锐化的区域。");
		isChooseArea = true;
		img_OP = USMSHARP;
	}
}


void CPhotoProDlg::OnBnClickedRepair()
{
	if (dst_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		AfxMessageBox("请选择要修复的区域。");
		isChooseArea = true;
		img_OP = REPAIRIMG;
	}
}

void CPhotoProDlg::OnBnClickedChangeBri()
{
	if (dst_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		ChangeBriDlg cbdlg;
		INT_PTR ret= cbdlg.DoModal();
		if (ret == IDOK)
		{
			double adj = cbdlg.adjust_number;
			MyBri_Con mbc;
			IplImage * modifiedImg = mbc.adjust_bright(dst_img,adj);
			UpdateDstImg(modifiedImg);

		}
	}
}




void CPhotoProDlg::OnBnClickedChangeCon()
{
	if (dst_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		ChangeConDlg ccdlg;
		INT_PTR ret= ccdlg.DoModal();
		if (ret == IDOK)
		{
			double adj = ccdlg.adjust_number;
			MyBri_Con mbc;
			IplImage * modifiedImg = mbc.adjust_contrast(dst_img,adj);
			UpdateDstImg(modifiedImg);

		}
	}
}


void CPhotoProDlg::OnBnClickedResizeByTimes()
{
	if (dst_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		ResizeTimesDlg rtdlg;
		INT_PTR ret= rtdlg.DoModal();
		if (ret == IDOK)
		{
			double adj = rtdlg.times;
			MyResize mbc;
			IplImage * modifiedImg = mbc.resizeByTimes(dst_img,adj);
			UpdateDstImg(modifiedImg);

		}
	}
}


void CPhotoProDlg::OnBnClickedResizeByVal()
{
	if (dst_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		ChangeByValDlg cbvdlg;
		INT_PTR ret= cbvdlg.DoModal();
		if (ret == IDOK)
		{
			int width = cbvdlg.width;
			int height = cbvdlg.height;
			MyResize mbc;
			IplImage * modifiedImg = mbc.resizeByValue(dst_img,width,height);
			UpdateDstImg(modifiedImg);

		}
	}
}


void CPhotoProDlg::OnBnClickedClipping()
{
	if (dst_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		AfxMessageBox("请选择要剪切的区域。");
		isChooseArea = true;
		img_OP = CLIPPING;
	}
}



void CPhotoProDlg::OnBnClickedRotate()
{
	if (dst_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		RotateDlg rotdlg;
		INT_PTR ret= rotdlg.DoModal();
		if (ret == IDOK)
		{
			double angle = rotdlg.angle;
			MyRotate mr;
			IplImage * modifiedImg = mr.doRotate(dst_img,angle);
			UpdateDstImg(modifiedImg);
		}
	}
}


void CPhotoProDlg::OnBnClickedAddLOGO()
{
	if (dst_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		AfxMessageBox("请选择LOGO图片路径。");
		CFileDialog filedialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			"JPG,JPEG,PNG,BMP (*.jpg;*.jpeg;*.png;*.bmp)|*.jpg;*.jpeg;*.png;*.bmp|All Files (*.*)|*.*||", this);
		if(IDOK==filedialog.DoModal())
		{
			logoORwm = cvLoadImage(filedialog.GetPathName(),1);
			AfxMessageBox("请选择要添加LOGO的位置。");
			isChoosePoint = true;
			img_OP = ADDLOGO;
		}
	}
}



void CPhotoProDlg::OnBnClickedAddWM()
{
	if (dst_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		AfxMessageBox("请选择水印图片路径。");
		CFileDialog filedialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			"JPG,JPEG,PNG,BMP (*.jpg;*.jpeg;*.png;*.bmp)|*.jpg;*.jpeg;*.png;*.bmp|All Files (*.*)|*.*||", this);
		if(IDOK==filedialog.DoModal())
		{
			logoORwm = cvLoadImage(filedialog.GetPathName(),1);
			AfxMessageBox("请选择要添加水印的位置。");
			isChoosePoint = true;
			img_OP = ADDWM;
		}
	}
}

void CPhotoProDlg::OnBnClickedAddText()
{
	if (dst_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		AddTextDlg atdlg;
		INT_PTR ret= atdlg.DoModal();
		if (ret == IDOK)
		{
			inputText =  atdlg.text;
			textColor = atdlg.color;
			AfxMessageBox("请选择要添加文字的位置。");
			isChoosePoint = true;
			img_OP = ADDTEXT;
		}
	}
}



void CPhotoProDlg::OnBnClickedRemoveLine()
{
	if (dst_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		RemoveLineDlg rldlg;
		INT_PTR ret= rldlg.DoModal();
		if (ret == IDOK)
		{
			pLeng = rldlg.pLeng;
			isRemove = true;
			img_OP = REMOVELINE;
		}
	}

}




void CPhotoProDlg::OnBnClickedAddBun()
{
	if (dst_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		AddBundaryDlg abdlg;
		INT_PTR ret= abdlg.DoModal();
		if (ret == IDOK)
		{
			MyBoundary mb;
			IplImage * modifiedImg = cvLoadImage((LPSTR)(LPCTSTR)abdlg.name,1);
			mb.addBoundary(dst_img,modifiedImg, abdlg.sx,abdlg.sy,abdlg.width,abdlg.height);
			UpdateDstImg(modifiedImg);

		}

	}
}


void CPhotoProDlg::doOperation( int op, CPoint sp, CPoint ep )
{

	if (op == 0)
	{
		AfxMessageBox("error#102# no operation!");
	}
	else
	{	
		IplImage * modifiedImg;
		ChangePoint cp(sp,ep);
		if (op == DOSMOOTH)
		{
			MySmooth ms;
			modifiedImg =ms.partSmooth(dst_img,cp.newSp.x,cp.newSp.y,cp.width,cp.height);

		}
		if (op == USMSHARP)
		{
			MySharp ms;
			modifiedImg = ms.partUsmSharp(dst_img,cp.newSp.x,cp.newSp.y,cp.width,cp.height);
		}
		if (op == ADDMOSAIC)
		{
			MyAddMosaic mam;
			modifiedImg = mam.addMosaic(dst_img,cp.newSp.x,cp.newSp.y,cp.width,cp.height);
		}
		if (op == REPAIRIMG)
		{
			MyInpaintig mi;
			modifiedImg = mi.inpaintig(dst_img,sp.x,sp.y,sp.x,ep.y,ep.x,sp.y,ep.x,ep.y);
		}
		if (op == CLIPPING)
		{
			MyClipping mc;
			modifiedImg = mc.clip(dst_img,cp.newSp.x,cp.newSp.y,cp.newSp.x+cp.width,cp.newSp.y+cp.height);
		}
		if (op == REMOVELINE)
		{
			getPointForRemoveLine(sp,ep,pLeng);
			MyRemoveLine mrl;
			modifiedImg = mrl.removeLine(dst_img,rm_a.x,rm_a.y,rm_c.x,rm_c.y,rm_b.x,rm_b.y,rm_d.x,rm_d.y);
		}
		UpdateDstImg(modifiedImg);
	}


}
void CPhotoProDlg::doOperationForPoint( int op,CPoint p )
{

	if (op == 0)
	{
		AfxMessageBox("error#102# no operation!");
	}
	else
	{	
		IplImage *modifiedImg = NULL;
		if (op == ADDLOGO)
		{
			modifiedImg = cvCreateImage(cvGetSize(dst_img),IPL_DEPTH_8U,3);
			modifiedImg = cvCloneImage(dst_img);
			MyLogo_WM mlwm;
			mlwm.putLogoWithBack(modifiedImg,logoORwm,p.x,p.y);
		}
		if (op == ADDWM)
		{
			modifiedImg = cvCreateImage(cvGetSize(dst_img),IPL_DEPTH_8U,3);
			modifiedImg = cvCloneImage(dst_img);
			MyLogo_WM mlwm;
			mlwm.putWM_img(modifiedImg,logoORwm,p.x,p.y);
		}
		if (op == ADDTEXT)
		{
			modifiedImg = cvCreateImage(cvGetSize(dst_img),IPL_DEPTH_8U,3);
			modifiedImg = cvCloneImage(dst_img);
			MyLogo_WM mlwm;
			mlwm.putText(modifiedImg,(LPSTR)(LPCTSTR)inputText,textColor,p.x,p.y);
		}
		UpdateDstImg(modifiedImg);
	}
}

void CPhotoProDlg::getPointForRemoveLine(CPoint sp, CPoint ep, int leng)
{
	leng = leng/pi.getDstImg_Times();
	rm_a.x=sp.x-leng;
	rm_a.y=sp.y-leng;
	rm_c.x=sp.x-leng;
	rm_c.y=sp.y+leng;
	rm_b.x=ep.x+leng;
	rm_b.y=ep.y-leng;
	rm_d.x=ep.x+leng;
	rm_d.y=ep.y+leng;
	if (rm_a.x<0)
	{
		rm_a.x=0;
		rm_c.x=0;
	}
	if (rm_a.y<0)
	{
		rm_a.y=0;
		rm_c.y=0+leng*2;
	}
	if (rm_c.y>(0+dst_img->height))
	{
		rm_c.y=0+dst_img->height;
		rm_a.y=0+dst_img->height-leng*2;
	}
	if (rm_b.x>(0+dst_img->width))
	{
		rm_b.x=0+dst_img->width;
		rm_d.x=0+dst_img->width;
	}
	if (rm_b.y<0) 
	{
		rm_b.y=0;
		rm_d.y=0+leng*2;
	}
	if (rm_d.y>(0+dst_img->height))
	{
		rm_d.y=0+dst_img->height;
		rm_b.y=0+dst_img->height-leng*2;
	}

}






