#include "MyAddMosaic.h"

MyAddMosaic::MyAddMosaic(void)
{
}


MyAddMosaic::~MyAddMosaic(void)
{
}

IplImage* MyAddMosaic::addMosaic( IplImage* src,int start_x, int start_y, int width, int height )
{
	if (src==NULL)
	{
		return NULL;
	}
	IplImage *dst = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,3);
	dst = cvCloneImage(src);
	cvSetImageROI(dst,cvRect(start_x,start_y,width,height));  
	int W=8;  
	int H=8;  
	for(int mi=W;mi<dst->roi->width;mi+=W)
	{  
		for(int mj=H;mj<dst->roi->height;mj+=H)  
		{  
			CvScalar tmp=cvGet2D(dst,mj-H/2,mi-W/2);  
			for(int mx=mi-W;mx<=mi;mx++)  
				for(int my=mj-H;my<=mj;my++)  
					cvSet2D(dst,my,mx,tmp);  
		} 
	}
	cvResetImageROI(dst);    
	return dst;
}
