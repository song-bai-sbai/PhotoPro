#pragma once
#include <highgui/highgui.hpp>
#include <imgproc\imgproc_c.h>
#include <imgproc\types_c.h>
class MySmooth
{
   public:
	   /************************************************************************/
	   /* Gaussian blur  recommended                                           */
	   /************************************************************************/
	  IplImage * doSmooth_Gaussian(const IplImage * src);

	  /************************************************************************/
	  /* blur                                                                 */
	  /************************************************************************/
	  IplImage * doSmooth_Blur(const IplImage * src);

	  /************************************************************************/
	  /* part blur                                                            */
	  /************************************************************************/
	  IplImage * partSmooth(IplImage *src ,int x, int y, int width, int height);
};


