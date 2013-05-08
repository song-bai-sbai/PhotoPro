#pragma once
#include <core\types_c.h>
#include <videostab\global_motion.hpp>
using namespace cv;
class MyBoundary
{
public:
	MyBoundary(void);
	~MyBoundary(void);
	/************************************************************************/
	/* add boundary                                                         */
	/************************************************************************/
	void addBoundary(IplImage * src, IplImage *back, int start_x, int start_y,int width, int height);
};

