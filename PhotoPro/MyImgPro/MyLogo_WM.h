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

	void putText(  IplImage* src, char* text,CvScalar color,int x, int y);
	/************************************************************************/
	/* use img as water mark												*/
	/************************************************************************/
	void putWM_img(IplImage* img,IplImage *wm_img, int pos_x, int pos_y, double alpha=1.0, double beta=0.3);
	/************************************************************************/
	/* put logo no back                                                     */
	/************************************************************************/
	void putLogoNoBack(IplImage* img, IplImage *logo, int pos_x, int pos_y);
	/************************************************************************/
	/* put logo with back                                                   */
	/************************************************************************/
	void putLogoWithBack(IplImage* img, IplImage *logo, int pos_x, int pos_y);
};

