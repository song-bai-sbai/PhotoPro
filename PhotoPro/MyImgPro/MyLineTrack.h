#pragma once
#include <core\types_c.h>
#include <core\core_c.h>
#include <list>
#include "My2DPoint.h"
using namespace std;
class MyLineTrack
{
public:
	MyLineTrack(void);
	~MyLineTrack(void);
	/************************************************************************/
	/* track line                                                           */
	/************************************************************************/
	void trackLine(IplImage * src,int start_x, int start_y,int end_x, int end_y);
private:
	void comparePoint(IplImage * src,int x, int y, double *diff,int p_num , CvScalar ori);

	My2DPoint judgeLine(IplImage * src, int start_x, int start_y, int pre_x, int pre_y, int end_x, int end_y);

	int getPreNum(int start_x, int start_y, int pre_x, int pre_y);

    int findMin(double *a);

	list<My2DPoint> p_result;
};


