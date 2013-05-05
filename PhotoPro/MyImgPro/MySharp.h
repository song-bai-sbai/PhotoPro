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
	IplImage * usmSharp(const IplImage*src, float amount, int radius, uchar threshold,float contrast=3);
};

