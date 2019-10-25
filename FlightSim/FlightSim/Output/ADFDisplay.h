/* 
* ADFDisplay.h
*
* Created: 18/10/2019 16:18:02
* Author: Gielw
*/


#ifndef __ADFDISPLAY_H__
#define __ADFDISPLAY_H__
#include "MeterBasis.h"

class ADFDisplay : public MeterBasis
{
//variables
public:
	float m_heading;
protected:
private:

//functions
public:
	ADFDisplay();
	~ADFDisplay();
	bool NextUpdateIsLongOfDuration() { return false; }
	int UpdateMeter();
protected:
private:

}; //ADFDisplay

#endif //__ADFDISPLAY_H__
