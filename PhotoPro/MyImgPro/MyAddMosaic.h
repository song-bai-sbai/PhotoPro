#pragma once
#include <core\types_c.h>
#include <core\core_c.h>

class MyAddMosaic
{
public:
	MyAddMosaic(void);
	~MyAddMosaic(void);
	IplImage* addMosaic(IplImage* src,int start_x, int start_y, int width, int height);
};

