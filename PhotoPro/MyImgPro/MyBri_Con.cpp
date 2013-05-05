#include "MyBrit_Con.h"

/************************************************************************/
/*     adjust_number, >0 add brightness, <0 reduce brightness           */
/************************************************************************/
IplImage * MyBri_Con::adjust_bright(const IplImage* src,float adjust_number )   
{
	if (src == NULL)
	{
		return NULL;
	}
	IplImage* dst = NULL;
	dst = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,3);
	if(src->nChannels==3)  
	{  
		for (int i = 0; i < 3; i++)              // 3 channel  
			for (int y = 0; y < src->height; y++)  
				for (int x = 0; x < src->width; x++)  
				{  
					float val = ((uchar*)(src->imageData + src->widthStep*y))[x*3+i];  
					val+=adjust_number;  
					if(val<0)
					{
						val=0;
					} 
					else if(val>255) 
					{
						val=255;
					}  
					((uchar*)(dst->imageData + dst->widthStep*y))[x*3+i] = (uchar)val;  
				}  
	}  
	else                                  // single channel
	{  
		for (int y = 0; y < src->height; y++)  
			for (int x = 0; x < src->width; x++)  
			{  
				float val = ((uchar*)(src->imageData + src->widthStep*y))[x];  
				val+=adjust_number;  
				if(val<0)   
				{
					val=0;
				}  
				else if(val>255) 
				{
					val=255;
				}  
				((uchar*)(dst->imageData + dst->widthStep*y))[x] = (uchar)val;  
			}  
	}           
	return dst;
}
/************************************************************************/
/* nPercent   , >1 add contrast, <1 reduce contrast                     */
/************************************************************************/
IplImage * MyBri_Con::adjust_contrast( const IplImage* src,float nPercent )
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


	if (src->nChannels==3)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int y = 0; y < src->height; y++)
			{
				for (int x = 0; x < src->width; x++)
				{

					float val = ((uchar*)(src->imageData + src->widthStep*y))[x*3+i];
					val = 128 + (val - 128) * nPercent;
					if(val>255) 
					{
						val=255;
					}
					if(val<0) 
					{
						val=0;
					}
					((uchar*)(dst->imageData + dst->widthStep*y))[x*3+i] = (uchar)val;
				}
			}
		}
	}
	else
	{
		for (int y = 0; y < src->height; y++)
		{
			for (int x = 0; x < src->width; x++)
			{

				float val = ((uchar*)(src->imageData + src->widthStep*y))[x];
				val = 128 + (val - 128) * nPercent;
				if(val>255) 
				{
					val=255;
				}
				if(val<0) 
				{
					val=0;
				}
				((uchar*)(dst->imageData + dst->widthStep*y))[x] = (uchar)val;
			}
		}
	}
	return dst;
}

/************************************************************************/
/* another type of adjust contrast, not work well                       */
/************************************************************************/
IplImage * MyBri_Con::old_AdjustContrast( const IplImage* src,  int contrast )
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

	//mean
	CvScalar mean = {0,0,0,0};
	for (int y=0; y<imageheight; y++)
	{
		for (int x=0; x<imagewidth; x++)
		{
			for (int k=0; k<channel; k++)
			{
				CvScalar ori = cvGet2D(src, y, x);
				for (int k=0; k<channel; k++)
				{
					mean.val[k] += ori.val[k];
				}
			}
		}
	}
	for (int k=0; k<channel; k++)
	{
		mean.val[k] /= imagewidth * imageheight;
	}

	//adjust contrast
	if (contrast <= -255)
	{
		//-255
		for (int y=0; y<imageheight; y++)
		{
			for (int x=0; x<imagewidth; x++)
			{
				cvSet2D(dst, y, x, mean);
			}
		}
	} 
	else if(contrast > -255 &&  contrast <= 0)
	{
		//(1)nRGB = RGB + (RGB - Threshold) * Contrast / 255
		for (int y=0; y<imageheight; y++)
		{
			for (int x=0; x<imagewidth; x++)
			{
				CvScalar nRGB;
				CvScalar ori = cvGet2D(src, y, x);
				for (int k=0; k<channel; k++)
				{
					nRGB.val[k] = ori.val[k] + (ori.val[k] - mean.val[k]) *contrast /255;
				}
				cvSet2D(dst, y, x, nRGB);
			}
		}
	}
	else if(contrast >0 && contrast <255)
	{

		//(2)、nContrast = 255 * 255 / (255 - Contrast) - 255
		CvScalar nRGB;
		int nContrast = 255 *255 /(255 - contrast) - 255;

		for (int y=0; y<imageheight; y++)
		{
			for (int x=0; x<imagewidth; x++)
			{
				CvScalar ori = cvGet2D(src, y, x);
				for (int k=0; k<channel; k++)
				{
					nRGB.val[k] = ori.val[k] + (ori.val[k] - mean.val[k]) *nContrast /255;
				}
				cvSet2D(dst, y, x, nRGB);
			}
		}
	}
	else
	{
		//255
		for (int y=0; y<imageheight; y++)
		{
			for (int x=0; x<imagewidth; x++)
			{
				CvScalar rgb;
				CvScalar ori = cvGet2D(src, y, x);
				for (int k=0; k<channel; k++)
				{
					if (ori.val[k] > mean.val[k])
					{
						rgb.val[k] = 255;
					}
					else
					{
						rgb.val[k] = 0;
					}
				}
				cvSet2D(dst, y, x, rgb);
			}
		}
	}
	return dst;
}
