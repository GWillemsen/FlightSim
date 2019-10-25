/* 
* ClimbingMeter.h
*
* Created: 18/10/2019 16:14:56
* Author: Gielw
*/


#ifndef __CLIMBINGMETER_H__
#define __CLIMBINGMETER_H__
#include "MeterBasis.h"

class ClimbingDisplay : public MeterBasis
{
//variables
public:
	float m_feetPerMinut;
	int m_upperScalePin;
	int m_lowerScalePin;
	int m_maxLowerScalePwm;
	int m_maxUpperScalePwm;
	int m_maxClimbValue;
	int m_minClimbValue;
protected:
private:

//functions
public:
	ClimbingDisplay(int a_upperScalePin, int a_lowerScalePin, int a_maxLowerScalePwm, int a_maxUpperScalePwm, int a_minClimbValue, int a_maxClimbValue);
	~ClimbingDisplay();
	bool NextUpdateIsLongOfDuration() { return false; }
	int UpdateMeter();

protected:
private:
}; //ClimbingMeter

#endif //__CLIMBINGMETER_H__
