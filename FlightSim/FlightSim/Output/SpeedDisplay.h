/* 
* SpeedMeter.h
*
* Created: 18/10/2019 15:24:33
* Author: Gielw
*/


#ifndef __SPEEDMETER_H__
#define __SPEEDMETER_H__
#include "MeterBasis.h"

// A class that manages the speed meter for us
class SpeedDisplay : public MeterBasis
{
//variables
public:
	float m_knots;
	int m_writePin;
	int m_maxKnts;
	int m_maxPwm;
protected:
private:

//functions
public:
	SpeedDisplay(int a_writePin, int a_maxKnts, int a_maxPwm);
	~SpeedDisplay();
	bool NextUpdateIsLongOfDuration() { return false; }
	int UpdateMeter();

}; //SpeedMeter

#endif //__SPEEDMETER_H__
