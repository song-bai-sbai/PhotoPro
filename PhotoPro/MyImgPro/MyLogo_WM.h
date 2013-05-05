#pragma once
#include <string>
#include <core\types_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
using namespace cv;

class MyLogo_WM
{
public:
	MyLogo_WM(void);

	~MyLogo_WM(void);

	void putText(const IplImage* src, IplImage *dst,string text);
	/************************************************************************/
	/* use img as water mark												*/
	/************************************************************************/
	void putWM_img(Mat &img,Mat &wm_img, int pos_x, int pos_y, double alpha=1.0, double beta=0.3);
};

