/* 
* RPMDisplay.h
*
* Created: 18/10/2019 16:20:30
* Author: Gielw
*/


#ifndef __RPMDISPLAY_H__
#define __RPMDISPLAY_H__
#include "MeterBasis.h"

class RPMDisplay : public MeterBasis
{
//variables
public:
	float m_rpms;
	int m_writePin;
	int m_maxRpm;
	int m_maxPwmValue;
protected:
private:

//functions
public:
	RPMDisplay(int a_writePin, int a_maxRpm, int a_maxPwm);
	~RPMDisplay();
	bool NextUpdateIsLongOfDuration() { return false; }
	int UpdateMeter();
protected:
private:

}; //RPMDisplay

#endif //__RPMDISPLAY_H__
