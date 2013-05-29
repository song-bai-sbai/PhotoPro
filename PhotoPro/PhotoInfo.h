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

private:
	string fileExt;
	float dstImg_Times;
	int resizeWidth;
	int resizeHeight;
	CPoint start_pos;
	CPoint end_pos;
	
};

