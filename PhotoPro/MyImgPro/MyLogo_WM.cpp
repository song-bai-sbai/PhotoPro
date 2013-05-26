#include "MyLogo_WM.h"
#include <imgproc\imgproc_c.h>

MyLogo_WM::MyLogo_WM(void)
{
}


MyLogo_WM::~MyLogo_WM(void)
{
}

void MyLogo_WM::putText( const IplImage* src, IplImage *dst,string text )
{

}
/************************************************************************/
/* use img as water mark												*/
/************************************************************************/
void MyLogo_WM::putWM_img( IplImage *img,IplImage* wm_img, int pos_x, int pos_y, double alpha, double beta )
{
	Mat imgMat(img,0);
	Mat wm_imgMat(wm_img,0);
	if (!imgMat.empty()&&!wm_imgMat.empty())
	{
		Mat imgROI = imgMat(Rect(pos_x,pos_y,wm_imgMat.cols,wm_imgMat.rows));
		addWeighted(imgROI, alpha, wm_imgMat, beta, 0, imgROI);// dst = alpha* roi+ beta* src+ gamma
	} 
}

void MyLogo_WM::putLogoNoBack( IplImage* img, IplImage *logo, int pos_x, int pos_y )
{
	Mat imgMat(img,0);
	Mat logoMat(logo,0);
	IplImage *mask = cvCreateImage(cvGetSize(logo),IPL_DEPTH_8U,1);
	cvCvtColor(logo,mask,CV_BGR2GRAY);
	Mat maskMat(mask,0);
	Mat imageROI = imgMat(cv::Rect(pos_x,pos_y,logoMat.cols,logoMat.rows));
	logoMat.copyTo(imageROI,maskMat);
}

void MyLogo_WM::putLogoWithBack( IplImage* img, IplImage *logo, int pos_x, int pos_y )
{
	Mat imgMat(img,0);
	Mat logoMat(logo,0);

	Mat imageROI = imgMat(cv::Rect(pos_x,pos_y,logoMat.cols,logoMat.rows));
	logoMat.copyTo(imageROI);
}
