#pragma once
#include <string>
using namespace std;
class PhotoInfo
{
public:
	PhotoInfo(void);
	~PhotoInfo(void);
	string getFileExt() const { return fileExt; }
	void setFileExt(string val) { fileExt = val; } 

	float getDstImg_Times() const { return dstImg_Times; }
	void setDstImg_Times(float val) { dstImg_Times = val; }

	int getResizeWidth() const { return resizeWidth; }
	void setResizeWidth(int val) { resizeWidth = val; }

	int getResizeHeight() const { return resizeHeight; }
	void setResizeHeight(int val) { resizeHeight = val; }

	CPoint getStart_pos() const { return start_pos; }
	void setStart_pos(CPoint val) { start_pos = val; }

	CPoint getEnd_pos() const { return end_pos; }
	void setEnd_pos(CPoint val) { end_pos = val; }
 
	int getDST_X() const { return DST_X; }
	void setDST_X(int val) { DST_X = val; }

	int getDST_Y() const { return DST_Y; }
	void setDST_Y(int val) { DST_Y = val; }
	
	CPoint getActualSP();

	CPoint getActualEP();
private:
	string fileExt;
	float dstImg_Times;
	int resizeWidth;
	int resizeHeight;
	CPoint start_pos;
	CPoint end_pos;
	int DST_X;
	int DST_Y;
	
};

