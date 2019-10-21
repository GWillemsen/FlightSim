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
protected:
private:

//functions
public:
	SpeedDisplay(int a_pin);
	~SpeedDisplay();
	bool NextUpdateIsLongOfDuration() { return false; }
	void UpdateMeter();

}; //SpeedMeter

#endif //__SPEEDMETER_H__
