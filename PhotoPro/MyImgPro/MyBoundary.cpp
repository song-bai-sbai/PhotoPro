#include "MyBoundary.h"
#include "MyResize.h"


MyBoundary::MyBoundary(void)
{
}


MyBoundary::~MyBoundary(void)
{
}

void MyBoundary::addBoundary( IplImage * src, IplImage *back, int start_x, int start_y, int width, int height )
{
	Mat backMat(back,0);
	Mat backRoi = backMat(Rect(start_x,start_y,width,height));
	Mat srcMat(src,0);
	IplImage *srcRezise=NULL;
	if (src->width!=width||src->height!=height)
	{
		MyResize mr;
		srcRezise=mr.resizeByValue(src,width,height);
	}
	if (srcRezise==NULL)
	{
		srcMat.copyTo(backRoi);
	}
	else
	{
		Mat srcReziseMat(srcRezise,0);
		srcReziseMat.copyTo(backRoi);
	}
}