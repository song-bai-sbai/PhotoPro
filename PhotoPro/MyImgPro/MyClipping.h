#pragma once
#include <core\types_c.h>
#include <core\core_c.h>
class MyClipping
{
public:
	MyClipping(void);
	~MyClipping(void);
	/************************************************************************/
	/* clip                                                                 */
	/************************************************************************/
	IplImage * clip( IplImage * src,int start_x, int start_y,int end_x, int end_y );
};

