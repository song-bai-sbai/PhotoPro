#include "MyLineTrack.h"

MyLineTrack::MyLineTrack(void)
{
}


MyLineTrack::~MyLineTrack(void)
{
}

void MyLineTrack::trackLine( IplImage * src,int start_x, int start_y,int end_x, int end_y)
{
	int pre_x = -1;
	int pre_y = -1;
	int t_pre_x = -1;
	int t_pre_y = -1;
	My2DPoint p_next;
	p_next.setX(start_x);
	p_next.setY(start_y);
	p_result.push_back(p_next);
	while(!(p_next.getX()==end_x&&p_next.getY()==end_y))
	{
		t_pre_x = p_next.getX();
		t_pre_y = p_next.getY();
		p_next = judgeLine(src, p_next.getX(), p_next.getY(),pre_x,pre_y,end_x,end_y);
		pre_x = t_pre_x;
		pre_y = t_pre_y;
		p_result.push_back(p_next);
	}
	list<My2DPoint>::iterator it;
	for (it = p_result.begin(); it!= p_result.end();it++)
	{
	    cvSet2D(src,it->getY(),it->getX(),cvScalar(255,255,255,0));
	}
}

My2DPoint MyLineTrack::judgeLine(IplImage * src, int start_x, int start_y, int pre_x, int pre_y, int end_x, int end_y)
{
	static My2DPoint result;
	if (start_x+1==end_x||start_x-1==end_x||start_x==end_x)
	{
		if (start_y==end_y||start_y-1==end_y||start_y+1==end_y)
		{

			result.setX(end_x);
			result.setY(end_y) ;
			return result;
		}
	}

	int preNum = getPreNum(start_x,start_y,pre_x,pre_y);

	double diff[8];/*0 1 2
				   **3   4
				   **5 6 7*/
	for (int i=0;i<8;i++)
	{
		diff[i]=9999;
	}
	CvScalar ori = cvGet2D(src, start_y, start_x);

	// point 0
	if (start_x-1>=0 && start_y-1>0&& preNum!=0)
	{
		comparePoint(src,start_x-1,start_y-1,diff,0,ori);
	}
	//point 1
	if (start_y-1>=0 && preNum!=1)
	{
		comparePoint(src,start_x,start_y-1,diff,1,ori);
	}

	//point 2
	if (start_x+1<src->width && start_y-1>0 && preNum!=2)
	{
		comparePoint(src,start_x+1,start_y+1,diff,2,ori);
	}

	//point 3
	if (start_x-1>=0 && preNum!=3)
	{
		comparePoint(src,start_x-1,start_y,diff,3,ori);
	}

	//point 4
	if (start_x+1<src->width && preNum!=4)
	{
		comparePoint(src,start_x+1,start_y,diff,4,ori);
	}

	//point 5
	if (start_x-1>=0 && start_y+1<src->height && preNum!=5)
	{
		comparePoint(src,start_x-1,start_y+1,diff,5,ori);
	}

	//point 6
	if (start_y+1<src->height && preNum!=6)
	{
		comparePoint(src,start_x,start_y+1,diff,6,ori);
	}

	//point 7
	if (start_x+1<src->width && start_y+1<src->height && preNum!=7)
	{
		comparePoint(src,start_x+1,start_y+1,diff,7,ori);
	}

	int min_p = findMin(diff);
	//TODO if min_p = -1;

	if (min_p != -1)
	{
		if (min_p == 0)
		{
			result.setX(start_x-1);
			result.setY(start_y-1);
		}
		if (min_p == 1)
		{
			result.setX(start_x);
			result.setY( start_y-1);
		}
		if (min_p == 2)
		{
			result.setX(start_x+1);
			result.setY(start_y+1);
		}
		if (min_p == 3)
		{
			result.setX(start_x-1);
			result.setY( start_y);
		}
		if (min_p == 4)
		{
			result.setX(start_x+1);
			result.setY(start_y);
		}
		if (min_p == 5)
		{
			result.setX(start_x-1);
			result.setY(start_y+1);
		}
		if (min_p == 6)
		{
			result.setX(start_x);
			result.setY(start_y+1);
		}
		if (min_p == 7)
		{
			result.setX(start_x+1);
			result.setY(start_y+1);
		}
	}

	return result;
}

void MyLineTrack::comparePoint( IplImage * src,int x, int y, double *diff ,int p_num , CvScalar ori)
{
	diff[p_num]=0;
	CvScalar p = cvGet2D(src,y,x);
	for (int k=0; k<src->nChannels; k++)
	{
		diff[p_num] += abs(ori.val[k]-p.val[k]);
	}

}

int MyLineTrack::findMin( double *a )
{
	int p_Num = -1;
	double	p_Value = a[0];
	for (int i=1;i<8;i++)
	{
		if (a[i]<p_Value)
		{
			p_Num=i;
			p_Value=a[i];
		}
	}

	return p_Num;
}

int MyLineTrack::getPreNum( int start_x, int start_y, int pre_x, int pre_y )
{
	if (start_x-1==pre_x)
	{
		if (start_y-1==pre_y)
		{
			return 0;
		}
		else if (start_y == pre_y)
		{
			return 3;
		}
		else if (start_y+1 == pre_y)
		{
			return 5;
		}
	}

	else if (start_x==pre_x)
	{
		if (start_y-1==pre_y)
		{
			return 1;
		}
		else if (start_y+1 == pre_y)
		{
			return 6;
		}
	}

	else if (start_x+1 ==pre_x)
	{
		if (start_y-1==pre_y)
		{
			return 2;
		}
		else if (start_y == pre_y)
		{
			return 4;
		}
		else if (start_y+1 == pre_y)
		{
			return 7;
		}
	}
	return -1;
}


