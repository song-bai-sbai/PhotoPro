#include "MyBoundary.h"
#include "MyResize.h"
#include <highgui\highgui_c.h>


MyBoundary::MyBoundary(void)
{
}


MyBoundary::~MyBoundary(void)
{
}

void MyBoundary::addBoundary( IplImage * src,IplImage * back, int start_x, int start_y, int width, int height )
{
	Mat backMat(back,0);
	Mat srcMat(src,0);
	IplImage *srcRezise=NULL;
	
	if (src->width!=width||src->height!=height)
	{
		int l_size = (src->width>src->height)?src->width:src->height;
		float times = (float)width/l_size;
		MyResize mr;
		srcRezise=mr.resizeByTimes(src,times);
	}
	if (srcRezise==NULL)
	{
		Mat backRoi = backMat(Rect(start_x,start_y,src->width,src->height));
		srcMat.copyTo(backRoi);
	}
	else
	{
		Mat srcReziseMat(srcRezise,0);
		if (srcRezise->width>srcRezise->height)
		{
			start_y = back->height/2 - srcRezise->height/2;
		}
		if (srcRezise->width<srcRezise->height)
		{
			start_x = back->width/2 - srcRezise->width/2;
		}
		Mat backRoi = backMat(Rect(start_x,start_y,srcRezise->width,srcRezise->height));
		srcReziseMat.copyTo(backRoi);
	}
}

