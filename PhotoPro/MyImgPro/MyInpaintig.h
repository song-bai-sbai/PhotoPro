#pragma once
#include <core\types_c.h>
#include <core\core_c.h>
#include <photo\photo_c.h>
class MyInpaintig
{
public:
	MyInpaintig(void);
	~MyInpaintig(void);
	IplImage * inpaintig(IplImage * src, int a_x,int a_y, int c_x, int c_y, int b_x, int b_y, int d_x, int d_y );
private:
	void getStart_line(int a_x,int a_y, int c_x, int c_y);

	void getEnd_line(int b_x, int b_y, int d_x, int d_y);

	void getLine(int start_x,int start_y, int end_x, int end_y);
};

