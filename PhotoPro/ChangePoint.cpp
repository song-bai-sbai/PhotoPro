#include "StdAfx.h"
#include "ChangePoint.h"


ChangePoint::ChangePoint(CPoint sp,CPoint ep)
{
	newSp = 0;
	width = 0;
	height = 0;
	if (ep.x-sp.x<0&&ep.y-sp.y<0)
	{
		newSp.x = ep.x;
		newSp.y = ep.y;
		width = sp.x - ep.x;
		height = sp.y - ep.y;
	}
	if (ep.x-sp.x>0&&ep.y-sp.y<0)
	{
		newSp.x = sp.x;
		newSp.y = ep.y;
		width = ep.x - sp.x;
		height = sp.y - ep.y;
	}
	if (ep.x-sp.x<0&&ep.y-sp.y>0)
	{
		newSp.x = ep.x;
		newSp.y = sp.y;
		width = sp.x - ep.y;
		height = ep.y - sp.y;
	}
	if (ep.x-sp.x>0&&ep.y-sp.y>0)
	{
		newSp.x = sp.x;
		newSp.y = sp.y;
		width = ep.x-sp.x;
		height = ep.y-sp.y;
	}
}


ChangePoint::~ChangePoint(void)
{
}
