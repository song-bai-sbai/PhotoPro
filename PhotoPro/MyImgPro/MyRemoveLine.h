#pragma once
#include <core\types_c.h>
#include "My2DPoint.h"
#include <core\core_c.h>
#include <list>
using namespace std;
class MyRemoveLine
{
public:
	/************************************************************************/
	/* a----b
	***|    |
	***c----d*/
	/************************************************************************/
	MyRemoveLine(void);
	~MyRemoveLine(void);
	/************************************************************************/
	/* remove line                                                          */
	/************************************************************************/
	IplImage * removeLine(IplImage * src,int a_x,int a_y, int c_x, int c_y, int b_x, int b_y, int d_x, int d_y);
private:
	bool judgeInLine( int pos_x, int pos_y, int start_x, int start_y, int end_x, int end_y);

	void getStart_line(int a_x,int a_y, int c_x, int c_y);

	void getEnd_line(int b_x, int b_y, int d_x, int d_y);

    void getLine(int start_x,int start_y, int end_x, int end_y);

	void setCurrentLine_InitVal();

	bool getAllPonintAndInit(); 

	void reDrawCurrentLine(list<My2DPoint> line);

	bool isInitVal( CvScalar cs);

	void addPointDiff(CvScalar &diff,CvScalar p_x ,int &p_count);

	list<My2DPoint> p_StartLine;

	list<My2DPoint> p_EndLine;

	list<My2DPoint> p_CurrentLine;
	
	list<list<My2DPoint>> allPoint;

	IplImage * img_src;

	CvScalar initVal;
};

