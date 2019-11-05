/* 
* HeadingDisplay.h
*
* Created: 18/10/2019 16:14:27
* Author: Gielw
*/


#ifndef __HEADINGDISPLAY_H__
#define __HEADINGDISPLAY_H__
#include "MeterBasis.h"

class HeadingDisplay : public MeterBasis
{
//variables
public:
	float m_heading;
protected:
private:

//functions
public:
	HeadingDisplay(int a_startHeading);
	virtual ~HeadingDisplay();
	bool NextUpdateIsLongOfDuration() { return false; }
	int UpdateMeter();
protected:
private:

}; //HeadingDisplay

#endif //__HEADINGDISPLAY_H__
