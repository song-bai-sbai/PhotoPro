#include "MyRotate.h"

MyRotate::MyRotate( void )
{

}

MyRotate::~MyRotate( void )
{

}
/************************************************************************/
/* angle<0 clockwise;   angle>0 anticlockwise                           */
/************************************************************************/
IplImage * MyRotate::doRotate( IplImage *src, double angle )
{
	if (src == NULL)
	{
		return NULL;
	}
	IplImage *dst= NULL;
	int remain = (int)angle%90;
	if (remain==0)
	{
		dst = cvCreateImage(cvSize(src->height,src->width),IPL_DEPTH_8U,3);
	} 
	else
	{
		dst= cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,3);
	}

	float m[6];
	// Matrix m looks like:
	//
	// [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
	// [ m3  m4  m5 ]       [ A21  A22   b2 ]
	//
	CvMat M = cvMat (2, 3, CV_32F, m);
	int w = src->width;
	int h = src->height;

	m[0] = (float) ( cos (-angle * CV_PI / 180.));
	m[1] = (float) ( sin (-angle * CV_PI / 180.));
	m[3] = -m[1];
	m[4] = m[0];
	// move rotate center to image center
	m[2] = w * 0.5f;
	m[5] = h * 0.5f;
	//  dst(x,y) = A * src(x,y) + b
	cvZero (dst);
	cvGetQuadrangleSubPix (src, dst, &M);//当函数需要图像边界外的像素点时，使用重复边界模式（replication border mode）恢复出所需的值。

	return dst;
}

