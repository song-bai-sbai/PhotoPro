#include "MyResize.h"

MyResize::MyResize(void)
{
}


MyResize::~MyResize(void)
{
}
/************************************************************************/
/* nearest-neighbor interpolation                                       */
/************************************************************************/
IplImage *  MyResize::resize_CV_INTER_NN(IplImage *src, double times)
{
	if(src == NULL)
	{
		return NULL;
	}  
	CvSize dst_size; 
	dst_size.width = src->width * times;  
	dst_size.height = src->height * times;
	IplImage * dst=cvCreateImage(dst_size,src->depth,src->nChannels);
	cvResize(src,dst,CV_INTER_NN);
	return dst;
}
/************************************************************************/
/* bilinear interpolation                                               */
/************************************************************************/
IplImage * MyResize::resize_CV_INTER_LINEAR(IplImage *src, double times)
{
	if(src == NULL)
	{
		return NULL;
	}   
	CvSize dst_size; 
	dst_size.width = src->width * times;  
	dst_size.height = src->height * times;
	IplImage *dst=cvCreateImage(dst_size,src->depth,src->nChannels);
	cvResize(src,dst,CV_INTER_LINEAR);
	return dst;
}

/************************************************************************/
/* using pixel area relation. It may be the preferred method for 
   image decimation, as it gives moire-free results. But when the image
   is zoomed, it is similar to the INTER_NEAREST method                 */
/************************************************************************/
IplImage *  MyResize::resize_CV_INTER_AREA(IplImage *src, double times)// preferred for image decimation
{
	if(src == NULL)
	{
		return NULL;
	}    
	CvSize dst_size; 
	dst_size.width = src->width * times;  
	dst_size.height = src->height * times;
	IplImage * dst=cvCreateImage(dst_size,src->depth,src->nChannels);
	cvResize(src,dst,CV_INTER_AREA);
	return dst;
}
/************************************************************************/
/* bicubic interpolation over 4x4 pixel neighborhood                    */
/************************************************************************/
IplImage *  MyResize::resize_CV_INTER_CUBIC(IplImage *src, double times)
{
	if(src == NULL)
	{
		return NULL;
	}  
	CvSize dst_size; 
	dst_size.width = src->width * times;  
	dst_size.height = src->height * times;
	IplImage *dst=cvCreateImage(dst_size,src->depth,src->nChannels);
	cvResize(src,dst,CV_INTER_CUBIC);
	return dst;
}

IplImage * MyResize::resizeByTimes( IplImage *src, double times )
{
	return resize_CV_INTER_LINEAR(src,times);
}

IplImage * MyResize::resizeByValue( IplImage *src, int width, int height )
{
	if(src == NULL)
	{
		return NULL;
	}  
	CvSize dst_size; 
	dst_size.width = width ;
	dst_size.height = height;
	IplImage *dst=cvCreateImage(dst_size,src->depth,src->nChannels);
	cvResize(src,dst,CV_INTER_CUBIC);
	return dst;
}
