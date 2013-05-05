#pragma once
#include <core\types_c.h>
#include <core\core_c.h>
#include <imgproc\imgproc_c.h>
class MyRotate
{
public:
	MyRotate(void);
	~MyRotate(void);
	/************************************************************************/
	/* angle<0 clockwise;   angle>0 anticlockwise                           */
	/************************************************************************/
	IplImage * doRotate(IplImage *src, double angle);
};

