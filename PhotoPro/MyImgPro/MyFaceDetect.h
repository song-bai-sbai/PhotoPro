#pragma once
#include <core\core.hpp>
#include <objdetect\objdetect.hpp>
#include <core\core_c.h>
#include <highgui\highgui.hpp>
#include <imgproc\imgproc.hpp>
#include <imgproc\types_c.h>

using namespace cv;
class MyFaceDetect
{
public:
	MyFaceDetect(void);
	~MyFaceDetect(void);
	void detectFace( Mat& img, CascadeClassifier& cascade,
		CascadeClassifier& nestedCascade,
		double scale, bool tryflip);
};

