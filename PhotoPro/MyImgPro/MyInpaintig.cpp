#include "MyInpaintig.h"


MyInpaintig::MyInpaintig(void)
{
}


MyInpaintig::~MyInpaintig(void)
{
}

IplImage * MyInpaintig::inpaintig( IplImage * src, int a_x,int a_y, int c_x, int c_y, int b_x, int b_y, int d_x, int d_y )
{
	IplImage * mask = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
	IplImage * dst = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,3);
	//cvInpaint(src,mask,dst,3,CV_INPAINT_NS);

	return dst;
}
