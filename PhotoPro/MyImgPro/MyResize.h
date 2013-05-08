#pragma once
#include <core\types_c.h>
#include <core\core_c.h>
#include <imgproc\types_c.h>
#include <imgproc\imgproc_c.h>
class MyResize
{
public:
	MyResize(void);
	~MyResize(void);
	/************************************************************************/
	/* default resize, use inter liner , times>0                             */
	/************************************************************************/
	IplImage * resizeByTimes(IplImage *src, double times);
	IplImage *  resize_CV_INTER_NN(IplImage *src, double times);
	IplImage * resize_CV_INTER_LINEAR(IplImage *src, double times);
	IplImage *  resize_CV_INTER_AREA(IplImage *src, double times);
	IplImage *  resize_CV_INTER_CUBIC(IplImage *src, double times);
	/************************************************************************/
	/* resize use inter liner                                             */
	/************************************************************************/
	IplImage * resizeByValue(IplImage *src, int width, int height);
};

