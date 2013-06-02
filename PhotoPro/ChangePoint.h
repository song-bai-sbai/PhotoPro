#pragma once
class ChangePoint
{
public:
	ChangePoint(CPoint sp,CPoint ep);
	~ChangePoint(void);
	CPoint newSp;
	int width;
	int height;
};

