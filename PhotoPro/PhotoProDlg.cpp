
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



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SRC_X 10
#define SRC_Y 10
#define SRC_WIDTH 300
#define SRC_HEIGHT 300
#define DST_X 400
#define DST_Y 10
#define DST_WIDTH 600
#define DST_HEIGHT 600

//Operation
#define ADDMOSAIC 101
#define CLIPPING 102
#define REPAIRIMG 103
#define REMOVELINE 104
#define USMSHARP 105
#define DOSMOOTH 106
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
	src_img = NULL;
	dst_img = NULL;
	temp_img = NULL;
	isChooseArea =  false;
	isBeginDraw = false;
	img_OP = 0;
	SetRectEmpty(&m_recDrawing);
	m_penDrawing = ::CreatePen(PS_DASH, 1, RGB(255, 0, 0));
	pi.setDST_X(DST_X);
	pi.setDST_Y(DST_Y);
}

void CPhotoProDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPhotoProDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPhotoProDlg::OnBnClickedShowIMG)
	ON_BN_CLICKED(IDC_BUTTON2, &CPhotoProDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPhotoProDlg::OnBnClickedLoadIMG)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON4, &CPhotoProDlg::OnBnClickedSaveImg)
	ON_BN_CLICKED(IDC_BUTTON5, &CPhotoProDlg::OnBnClickedDoSmooth)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON6, &CPhotoProDlg::OnBnClickedAddMosaic)
	ON_BN_CLICKED(IDC_BUTTON12, &CPhotoProDlg::OnBnClickedUsmSharp)
	ON_BN_CLICKED(IDC_BUTTON7, &CPhotoProDlg::OnBnClickedAllSharp)
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
	if (isChooseArea)
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

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CPhotoProDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (isChooseArea==true&&isBeginDraw==true)
	{
		isChooseArea = false;
		isBeginDraw = false;
		pi.setEnd_pos(point);
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

void CPhotoProDlg::OnBnClickedButton2()
{
	MySmooth ms;
	//IplImage * modifiedImg =ms.doSmooth_Gaussian(src_img);
	MyResize mr;
	IplImage * modifiedImg = mr.resizeByTimes(src_img,0.5);
	UpdateDstImg(modifiedImg);
}


void CPhotoProDlg::OnBnClickedAllSharp()
{
	if (src_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		MySharp ms;
		IplImage * modifiedImg = ms.usmSharp(src_img);
		UpdateDstImg(modifiedImg);
	}

}


void CPhotoProDlg::OnBnClickedDoSmooth()
{
	if (src_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		isChooseArea = true;
		img_OP = DOSMOOTH;
	}
}

void CPhotoProDlg::OnBnClickedAddMosaic()
{
	if (src_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		img_OP = ADDMOSAIC;
	}
}

void CPhotoProDlg::OnBnClickedUsmSharp()
{
	if (src_img == NULL)
	{
		AfxMessageBox("请先载入一张照片。");
	}
	else
	{
		isChooseArea = true;
		img_OP = USMSHARP;
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
			modifiedImg =ms.partSmooth(src_img,cp.newSp.x,cp.newSp.y,cp.width,cp.height);

		}
		if (op == USMSHARP)
		{
			MySharp ms;
			modifiedImg = ms.partUsmSharp(src_img,cp.newSp.x,cp.newSp.y,cp.width,cp.height);
		}
		UpdateDstImg(modifiedImg);
	}


}
