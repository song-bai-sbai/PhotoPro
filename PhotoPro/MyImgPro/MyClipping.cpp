#include "MyClipping.h"



MyClipping::MyClipping(void)
{
}


MyClipping::~MyClipping(void)
{
}

IplImage * MyClipping::clip( IplImage * src,int start_x, int start_y,int end_x, int end_y )
{
	if (src == NULL)
	{
		return NULL;
	}
	IplImage * dst;
	cvSetImageROI(src,cvRect(start_x,start_y,end_x-start_x,end_y-start_y));    
	dst = cvCreateImage(cvSize(end_x-start_x,end_y-start_y),    
		IPL_DEPTH_8U,    
		src->nChannels);    
	cvCopy(src,dst,0); 
	cvResetImageROI(src);   
	return dst;
}
