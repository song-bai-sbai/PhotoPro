
// PhotoProDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PhotoPro.h"
#include "PhotoProDlg.h"
#include "afxdialogex.h"
#include "MyImgPro\MySmooth.h"
#include "Resource.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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

void CPhotoProDlg::DrawPicToHDC( IplImage *img, UINT ID , int pos_x, int pos_y)
{
	GetDlgItem(ID)->MoveWindow(pos_x,pos_y,img->width,img->height,FALSE);
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC= pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cvvimamg;
	cvvimamg.CopyOf( img ); // Copy IMG
	cvvimamg.DrawToHDC( hDC, &rect ); // Draw PIC
	ReleaseDC( pDC );
}


void CPhotoProDlg::OnBnClickedButton2()
{
	MySmooth ms;
	IplImage * dst =ms.doSmooth_Gaussian(src_img);
	DrawPicToHDC(dst, IDC_DstImg,600,0);
}


void CPhotoProDlg::OnBnClickedLoadIMG()//load img
{
	CFileDialog filedialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,
		NULL, this);
	if(IDOK==filedialog.DoModal())
	{
		if(src_img!=NULL)
		{
			cvReleaseImage(&src_img);
		}
		src_img = cvLoadImage(filedialog.GetPathName(),1);
		DrawSrcImg(src_img, IDC_SrcImg);
	}
}


void CPhotoProDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (point.x>0&&point.x<100&&point.y>0&&point.y<100)
	{
		SetCursor(m_HCross);
	}
	else
	{
        SetCursor(m_HArrow);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CPhotoProDlg::DrawSrcImg(IplImage *img, UINT ID)//max size 300*300
{

	if (img->width>300||img->height>300)
	{
		int l_size = (img->width>img->height)?img->width:img->height;
		float times = (float)300/l_size;
		GetDlgItem(ID)->MoveWindow(10,10,img->width*times,img->height*times,FALSE);
	}
	else
	{
		GetDlgItem(ID)->MoveWindow(10,10,img->width,img->height,FALSE);
	}
	
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC= pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf( img ); // Copy IMG
	cimg.DrawToHDC( hDC, &rect ); // Draw PIC
	ReleaseDC( pDC );
}


void CPhotoProDlg::OnBnClickedSaveImg()
{
	CFileDialog filedialog(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,
		NULL, this);
	if(IDOK==filedialog.DoModal())
	{
		CvvImage cimg;
		cimg.Save(filedialog.GetPathName());
	}
}
