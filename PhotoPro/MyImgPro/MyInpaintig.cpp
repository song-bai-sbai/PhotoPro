#include "MyInpaintig.h"


MyInpaintig::MyInpaintig(void)
{
}


MyInpaintig::~MyInpaintig(void)
{
}

IplImage * MyInpaintig::inpaintig( IplImage * src, int a_x,int a_y, int c_x, int c_y, int b_x, int b_y, int d_x, int d_y )
{
	mask = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U, 1);
	cvSetZero(mask);
	initVal = cvScalar(1,0,0,0);
	getStart_line(a_x,a_y,c_x,c_y);
	getEnd_line(b_x,b_y,d_x,d_y);
	getAllPonintAndInit();
	IplImage * dst = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,3);
	cvInpaint(src,mask,dst,3,CV_INPAINT_NS);

	return dst;
}

bool MyInpaintig::judgeInLine( int pos_x, int pos_y, int start_x, int start_y, int end_x, int end_y )
{
	if (( start_x -pos_x )*( end_y-pos_y) -( end_x -pos_x )*( start_y-pos_y)!=0) 
	{ 
		return false; 
	} 
	if ((pos_x > start_x && pos_x > end_x) || (pos_x < start_x && pos_x < end_x)) 
	{ 
		return false; 
	} 
	if ((pos_y > start_y && pos_y > end_y) || (pos_y < start_y && pos_y < end_y)) 
	{ 

		return false; 
	} 
	return true; 

}

void MyInpaintig::getStart_line(int a_x,int a_y, int c_x, int c_y )
{
	if (!p_StartLine.empty())
	{
		p_StartLine.clear();
	}
	My2DPoint mp;
	int start_x = a_x<c_x?a_x:c_x;
	int end_x = a_x>c_x?a_x:c_x;
	int start_y = a_y<c_y?a_y:c_y;
	int end_y = a_y>c_y?a_y:c_y;
	for (int x = start_x;x<end_x+1;x++)
	{
		for (int y =start_y;y<end_y+1;y++)
		{
			if (judgeInLine(x,y,a_x,a_y,c_x,c_y))
			{
				mp.setX(x);
				mp.setY(y);
				p_StartLine.push_back(mp);
			}

		}
	}
}

void MyInpaintig::getEnd_line( int b_x,int b_y, int d_x, int d_y)
{
	if (!p_EndLine.empty())
	{
		p_EndLine.clear();
	}
	My2DPoint mp;
	int start_x = b_x<d_x?b_x:d_x;
	int end_x = b_x>d_x?b_x:d_x;
	int start_y = b_y<d_y?b_y:d_y;
	int end_y = b_y>d_y?b_y:d_y;
	for (int x = start_x;x<end_x+1;x++)
	{
		for (int y =start_y;y<end_y+1;y++)
		{
			if (judgeInLine(x,y,b_x,b_y,d_x,d_y))
			{
				mp.setX(x);
				mp.setY(y);
				p_EndLine.push_back(mp);
			}

		}
	}
}

void MyInpaintig::getLine( int start_x,int start_y, int end_x, int end_y )
{
	if (!p_CurrentLine.empty())
	{
		p_CurrentLine.clear();
	}
	My2DPoint mp;
	int min_x = start_x<end_x?start_x:end_x;
	int max_x = start_x>end_x?start_x:end_x;
	int min_y = start_y<end_y?start_y:end_y;
	int max_y = start_y>end_y?start_y:end_y;
	for (int x = min_x;x<max_x+1;x++)
	{
		for (int y= min_y;y<max_y+1;y++)
		{
			if (judgeInLine(x,y,start_x,start_y,end_x,end_y))
			{
				mp.setX(x);
				mp.setY(y);
				p_CurrentLine.push_back(mp);
			}
		}
	}
}

bool MyInpaintig::getAllPonintAndInit()
{
	if (p_StartLine.empty()||p_EndLine.empty())
	{
		return false;
	}
	if (p_StartLine.size()!= p_EndLine.size())
	{
		return false;
	}
	if (!allPoint.empty())
	{
		allPoint.clear();
	}
	list<My2DPoint>::iterator iStart_front = p_StartLine.begin();
	list<My2DPoint>::iterator iStart_back = p_StartLine.end();
	list<My2DPoint>::iterator iEnd_front = p_EndLine.begin();
	list<My2DPoint>::iterator iEnd_back = p_EndLine.end();

	iEnd_back--;
	iStart_back--;
	int count_front = 0;
	int count_back = p_StartLine.size()-1;
	while (count_front<=count_back)
	{
		if (count_front==count_back)
		{
			getLine(iStart_front->getX(),iStart_front->getY(),iEnd_front->getX(),iEnd_front->getY());
			allPoint.push_back(p_CurrentLine);
			setCurrentLine_InitVal();
			iStart_front++;
			iEnd_front++;
			iStart_back--;
			iEnd_back--;
			count_front++;
			count_back--;
		}
		else
		{
			getLine(iStart_front->getX(),iStart_front->getY(),iEnd_front->getX(),iEnd_front->getY());
			allPoint.push_back(p_CurrentLine);
			setCurrentLine_InitVal();
			getLine(iStart_back->getX(),iStart_back->getY(),iEnd_back->getX(),iEnd_back->getY());
			allPoint.push_back(p_CurrentLine);
			setCurrentLine_InitVal();
			iStart_front++;
			iEnd_front++;
			iStart_back--;
			iEnd_back--;
			count_front++;
			count_back--;
		}

	}
	return true;
}

void MyInpaintig::setCurrentLine_InitVal()
{
	if (mask!=NULL&&!p_CurrentLine.empty())
	{
		list<My2DPoint>::iterator it;
		for (it=p_CurrentLine.begin();it!=p_CurrentLine.end();it++)
		{
			cvSet2D(mask,it->getY(),it->getX(),initVal);
		}
	}
}
