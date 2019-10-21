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
	float m_speed;
protected:
private:

//functions
public:
	ClimbingDisplay();
	~ClimbingDisplay();
	bool NextUpdateIsLongOfDuration() { return false; }
	void UpdateMeter();

protected:
private:
}; //ClimbingMeter

#endif //__CLIMBINGMETER_H__
