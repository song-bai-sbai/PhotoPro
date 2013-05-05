#pragma once
#include <core\types_c.h>
#include <core\core_c.h>
class MyBri_Con
{
public:
	/************************************************************************/
	/*     adjust_number, >0 add brightness, <0 reduce brightness           */
	/************************************************************************/
	IplImage * adjust_bright(const IplImage* srcimg,float adjust_number);

	/************************************************************************/
	/* nPercent   , >1 add contrast, <1 reduce contrast                     */
	/************************************************************************/
	IplImage *  adjust_contrast(const IplImage* src,float adjust_number );

	/************************************************************************/
	/* another type of adjust contrast, not work well                       */
	/************************************************************************/
	IplImage *  old_AdjustContrast(const IplImage* src, int contrast);
};




