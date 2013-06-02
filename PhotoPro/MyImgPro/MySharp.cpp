#include "MySharp.h"

MySharp::MySharp(void)
{
}


MySharp::~MySharp(void)
{
}
/************************************************************************/
/* usmSahrp                                                             */
/************************************************************************/
IplImage * MySharp::usmSharp(const IplImage* src,  float amount, int radius, uchar threshold, float contrast)
{
		if (src == NULL)
		{
			return NULL;
		}
        IplImage* dst = NULL;
		dst = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,3);
		int imagewidth = src->width;
		int imageheight = src->height;
		int channel = src->nChannels;

		IplImage* blurimage = cvCreateImage(cvSize(imagewidth,imageheight), src->depth, channel);
		IplImage* DiffImage = cvCreateImage(cvSize(imagewidth,imageheight), 8, channel);

		//get high contrast image
		IplImage* highcontrast;
		MyBri_Con mb;
		highcontrast = mb.adjust_contrast(src,contrast);

		//get blur image
		cvSmooth(src, blurimage, CV_GAUSSIAN, radius);

		//get diff 
		for (int y=0; y<imageheight; y++)
		{
			for (int x=0; x<imagewidth; x++)
			{
				CvScalar ori = cvGet2D(src, y, x);
				CvScalar blur = cvGet2D(blurimage, y, x);
				CvScalar val;
				val.val[0] = abs(ori.val[0] - blur.val[0]);
				val.val[1] = abs(ori.val[1] - blur.val[1]);
				val.val[2] = abs(ori.val[2] - blur.val[2]);

				cvSet2D(DiffImage, y, x, val);
			}
		}

		//sharp
		for (int y=0; y<imageheight; y++)
		{
			for (int x=0; x<imagewidth; x++)
			{
				CvScalar hc = cvGet2D(highcontrast, y, x);
				CvScalar diff = cvGet2D(DiffImage, y, x);
				CvScalar ori = cvGet2D(src, y, x);
				CvScalar val;

				for (int k=0; k<channel; k++)
				{
					if (diff.val[k] > threshold)
					{
						//dst = ori*(1-r) + hight contrast*r
						val.val[k] = ori.val[k] *(100-amount) + hc.val[k] *amount;
						val.val[k] /= 100;
					}
					else
					{
						val.val[k] = ori.val[k];
					}
				}
				cvSet2D(dst, y, x, val);
			}
		}
		cvReleaseImage(&blurimage);
		cvReleaseImage(&DiffImage);
        return dst;	
}

IplImage * MySharp::partUsmSharp( IplImage*src,int x0, int y0, int width0, int height0, float amount/*=40*/, int radius/*=13*/, uchar threshold/*=2*/,float contrast/*=3*/ )
{
	if(src == NULL)
	{
		return NULL;
	}  
	IplImage * dst = NULL;
	dst = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,3);
	dst = cvCloneImage(src);

	int imagewidth = src->width;
	int imageheight = src->height;
	int channel = src->nChannels;

	IplImage* blurimage = cvCreateImage(cvSize(imagewidth,imageheight), src->depth, channel);
	IplImage* DiffImage = cvCreateImage(cvSize(imagewidth,imageheight), 8, channel);

	//get high contrast image
	IplImage* highcontrast;
	MyBri_Con mb;
	highcontrast = mb.adjust_contrast(src,contrast);

	//get blur image
	cvSmooth(src, blurimage, CV_GAUSSIAN, radius);

	//get diff 
	for (int y=y0; y<height0; y++)
	{
		for (int x=x0; x<width0; x++)
		{
			CvScalar ori = cvGet2D(src, y, x);
			CvScalar blur = cvGet2D(blurimage, y, x);
			CvScalar val;
			val.val[0] = abs(ori.val[0] - blur.val[0]);
			val.val[1] = abs(ori.val[1] - blur.val[1]);
			val.val[2] = abs(ori.val[2] - blur.val[2]);

			cvSet2D(DiffImage, y, x, val);
		}
	}

	//sharp
	for (int y=y0; y<height0; y++)
	{
		for (int x=x0; x<width0; x++)
		{
			CvScalar hc = cvGet2D(highcontrast, y, x);
			CvScalar diff = cvGet2D(DiffImage, y, x);
			CvScalar ori = cvGet2D(src, y, x);
			CvScalar val;

			for (int k=0; k<channel; k++)
			{
				if (diff.val[k] > threshold)
				{
					//dst = ori*(1-r) + hight contrast*r
					val.val[k] = ori.val[k] *(100-amount) + hc.val[k] *amount;
					val.val[k] /= 100;
				}
				else
				{
					val.val[k] = ori.val[k];
				}
			}
			cvSet2D(dst, y, x, val);
		}
	}
	cvReleaseImage(&blurimage);
	cvReleaseImage(&DiffImage);

	return dst;
}
