#include "MySmooth.h"

IplImage * MySmooth::doSmooth_Gaussian( const IplImage * src )
{
	if(src == NULL)
	{
		return NULL;
	}  
	IplImage * dst = NULL;
	dst = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,3);
	cvSmooth(src,dst,CV_GAUSSIAN);
	return dst;
}

IplImage * MySmooth::doSmooth_Blur( const IplImage * src )
{
	if(src == NULL)
	{
		return NULL;
	}  
	IplImage * dst = NULL;
	dst = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,3);
	cvSmooth(src,dst,CV_BLUR);
	return dst;
}

IplImage * MySmooth::partSmooth( IplImage *src ,int x, int y, int width, int height)
{
	if(src == NULL)
	{
		return NULL;
	}  
	IplImage *temp = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,3);
	cvCopy(src,temp,NULL);
	IplImage * dst = NULL;
	cvSetImageROI(temp,cvRect(x,y,width,height));
	dst = cvCreateImage(cvGetSize(temp),IPL_DEPTH_8U,3);
	dst = doSmooth_Gaussian(temp);
	cvCopy(dst,temp,NULL);
	cvResetImageROI(temp);// reset
	return temp;
}