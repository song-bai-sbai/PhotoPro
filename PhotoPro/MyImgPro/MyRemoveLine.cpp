#include "MyRemoveLine.h"
#include <photo\photo_c.h>


MyRemoveLine::MyRemoveLine(void)
{
}


MyRemoveLine::~MyRemoveLine(void)
{
}

IplImage * MyRemoveLine::removeLine(IplImage*src, int a_x,int a_y, int c_x, int c_y, int b_x, int b_y, int d_x, int d_y )
{
	mask = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U, 1);
	cvSetZero(mask);
	initVal = cvScalar(1,0,0,0);
	newInit( a_x, a_y,  c_x,  c_y, d_x,  d_y, b_x,  b_y );
	/*getStart_line(a_x,a_y,c_x,c_y);
	getEnd_line(b_x,b_y,d_x,d_y);
	getAllPonintAndInit();*/
	/*list<list<My2DPoint>>::iterator it;
	for (it=allPoint.begin();it!=allPoint.end();it++)
	{
	reDrawCurrentLine(*it);
	}*/
	IplImage * dst = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,3);
	cvInpaint(src,mask,dst,3,CV_INPAINT_NS);
	return dst;
}

bool MyRemoveLine::judgeInLine( int pos_x, int pos_y, int start_x, int start_y, int end_x, int end_y )
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

void MyRemoveLine::getStart_line(int a_x,int a_y, int c_x, int c_y )
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

void MyRemoveLine::getEnd_line( int b_x,int b_y, int d_x, int d_y)
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

void MyRemoveLine::getLine( int start_x,int start_y, int end_x, int end_y )
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

bool MyRemoveLine::getAllPonintAndInit()
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

void MyRemoveLine::setCurrentLine_InitVal()
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

void MyRemoveLine::reDrawCurrentLine(list<My2DPoint> line)
{
	list<My2DPoint>::iterator it;
	CvScalar p_diff;
	CvScalar p_0;
	CvScalar p_1;
	CvScalar p_2;
	CvScalar p_3;
	CvScalar p_4;
	CvScalar p_5;
	CvScalar p_6;
	CvScalar p_7;
	/*0 1 2
	**3   4
	**5 6 7*/
	int p_count = 0;
	for (it=line.begin();it!=line.end();it++)
	{
		p_diff = cvScalar(0,0,0,0);
		p_count = 0;
		//point0
		if (it->getX()-1>=0 && it->getY()-1>0)
		{
			p_0 = cvGet2D(mask,it->getY()-1>0,it->getX()-1>=0);
			addPointDiff(p_diff,p_0,p_count);
		}
		//point 1
		if (it->getY()-1>=0 )
		{
			p_1 = cvGet2D(mask,it->getY()-1,it->getX());
			addPointDiff(p_diff,p_1,p_count);
		}

		//point 2
		if (it->getX()+1<mask->width && it->getY()-1>0 )
		{
			p_2 = cvGet2D(mask,it->getY()-1,it->getX()+1);
			addPointDiff(p_diff,p_2,p_count);
		}

		//point 3
		if (it->getX()-1>=0)
		{
			p_3 = cvGet2D(mask,it->getY(),it->getX()-1);
			addPointDiff(p_diff,p_3,p_count);
		}

		//point 4
		if (it->getX()+1<mask->width )
		{
			p_4 = cvGet2D(mask,it->getY(),it->getX()+1);
			addPointDiff(p_diff,p_4,p_count);
		}

		//point 5
		if (it->getX()-1>=0 && it->getY()+1<mask->height)
		{
			p_5 = cvGet2D(mask,it->getY()+1,it->getX()-1);
			addPointDiff(p_diff,p_5,p_count);
		}

		//point 6
		if (it->getY()+1<mask->height)
		{
			p_6 = cvGet2D(mask,it->getY()+1,it->getX());
			addPointDiff(p_diff,p_6,p_count);
		}

		//point 7
		if (it->getX()+1<mask->width && it->getY()+1<mask->height )
		{
			p_7=cvGet2D(mask,it->getY()+1,it->getX()+1);
			addPointDiff(p_diff,p_7,p_count);
		}

		if (p_count == 0)
		{
			cvSet2D(mask,it->getY(),it->getX(),initVal);
		} 
		else
		{
			for (int i =0 ;i< mask->nChannels; i++)
			{
				p_diff.val[i]=p_diff.val[i]/p_count;
			}
			cvSet2D(mask,it->getY(),it->getX(),p_diff);
		}

	}
}

bool MyRemoveLine::isInitVal( CvScalar cs)
{
	for (int i= 0;i<mask->nChannels;i++)
	{
		if (cs.val[i]!=initVal.val[i])
		{
			return false;
		}
	}
	return true;
}

void MyRemoveLine::addPointDiff(CvScalar &diff,CvScalar p_x ,int &p_count)
{
	if (!isInitVal(p_x))
	{
		for(int i =0 ; i< mask->nChannels; i++)
		{
			diff.val[i]+= p_x.val[i];
		}
		p_count++;
	}
}

bool MyRemoveLine::inArea(int x, int y,int a_x,int a_y, int c_x, int c_y,int d_x, int d_y, int b_x, int b_y )
{ 
	double dTriangle = triangleArea(a_x,a_y, c_x,c_y, x,y) + triangleArea( c_x,c_y,d_x,d_y, x,y) +  triangleArea(d_x,d_y,b_x,b_y, x,y) + triangleArea(b_x,b_y, a_x,a_y, x,y);  
	double dQuadrangle = triangleArea(a_x,a_y, b_x,b_y, c_x,c_y) + triangleArea(c_x,c_y, d_x,d_y, b_x,b_y);  
	return dTriangle == dQuadrangle; 
}

double MyRemoveLine::triangleArea( int a_x,int a_y, int b_x, int b_y ,int c_x, int c_y )
{
	double result = abs((a_x * b_y + b_x * c_y + c_x * a_y - b_x * a_y  
		- c_x * b_y - a_x * c_y) / 2.0);  
	return result;  
}

void MyRemoveLine::newInit(int a_x,int a_y,int c_x, int c_y, int d_x, int d_y, int b_x, int b_y )
{
	for (int x=0;x<mask->width;x++)
	{
		for (int y=0;y<mask->height;y++)
		{
			if (inArea(x,y, a_x, a_y,  c_x,  c_y, d_x,  d_y , b_x,  b_y ))
			{
				cvSet2D(mask,y,x,initVal);
			}

		}
	}
}

bool MyRemoveLine::isIn( int x, int y,int a_x,int a_y, int c_x, int c_y, int d_x, int d_y,int b_x, int b_y  )
{
	double a[8] = {0};
	a[0] = atan2(double(y-a_y),double(x-a_x));
	a[1] = atan2(double(c_y-a_y),double(c_x-a_x));
	a[2] = atan2(double(y-c_y),double(x-c_x));
	a[3] = atan2(double(d_y-c_y),double(d_x-c_x));
	a[4] = atan2(double(y-d_y),double(x-d_x));
	a[5] = atan2(double(b_y-d_y),double(b_x-d_x));
	a[6] = atan2(double(y-b_y),double(x-b_x));
	a[7] = atan2(double(a_y-b_y),double(a_x-b_x));
	int i = 0;
	for(i = 0; i < 8; i++)
	{
		if(a[i]<0) a[i] = 2*3.1415926 + a[i];
	}
	if(a[0]>a[1]&&a[2]>a[3]&&a[4]>a[5]&&a[6]>a[7])
		return true;
	else
		return false;
}



