#pragma once
class My2DPoint
{
public:
	My2DPoint(void);
	~My2DPoint(void);
	int getX();

	int getY();
	
	void setX(int x);
	
	void setY(int y);
private:
	int x;
	int y;
};
