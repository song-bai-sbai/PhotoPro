#pragma once
#include <core\types_c.h>
#include <core\core_c.h>
#include "MyBrit_Con.h"
#include <imgproc\imgproc_c.h>
class MySharp
{
public:
	MySharp(void);
	~MySharp(void);
	/************************************************************************/
	/* usmSahrp                                                             */
	/************************************************************************/
	IplImage * usmSharp(const IplImage*src, float amount=40, int radius=13, uchar threshold=2,float contrast=3);

	IplImage * partUsmSharp(IplImage*src,int x, int y, int width, int height, float amount=40, int radius=13, uchar threshold=2,float contrast=3);
};

