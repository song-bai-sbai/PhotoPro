#include "MyLogo_WM.h"

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
void MyLogo_WM::putWM_img( Mat &img,Mat &wm_img, int pos_x, int pos_y, double alpha, double beta )
{
	if (!img.empty()&&!wm_img.empty())
	{
		Mat imgROI = img(Rect(pos_x,pos_y,wm_img.cols,wm_img.rows));
		addWeighted(imgROI, alpha, wm_img, beta, 0, imgROI);// dst = alpha* roi+ beta* src+ gamma
	} 
}
