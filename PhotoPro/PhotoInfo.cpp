#include "StdAfx.h"
#include "PhotoInfo.h"


PhotoInfo::PhotoInfo(void)
{
	setFileExt("");
	setDstImg_Times(0);
	setResizeWidth(0);
	setResizeHeight(0);
}


PhotoInfo::~PhotoInfo(void)
{
}

CPoint PhotoInfo::getActualSP()
{
	CPoint sp;
	sp.x = (start_pos.x-DST_X)/dstImg_Times;
	sp.y = (start_pos.y-DST_Y)/dstImg_Times;
	return sp;
}

CPoint PhotoInfo::getActualEP()
{
	CPoint ep;
	ep.x = (end_pos.x-DST_X)/dstImg_Times;
	ep.y = (end_pos.y-DST_Y)/dstImg_Times;
	return ep;
}
