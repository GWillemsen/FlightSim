/* 
* AltitudeDisplay.h
*
* Created: 18/10/2019 16:19:47
* Author: Gielw
*/


#ifndef __ALTITUDEDISPLAY_H__
#define __ALTITUDEDISPLAY_H__
#include "MeterBasis.h"

class AltitudeDisplay : public MeterBasis
{
//variables
public:
	float m_altitude;
	int m_stepPin;
	int m_dirPin;
	int m_ms1Pin;
	int m_ms2Pin;
	int m_minHeightDiffBeforeMoving;
	int m_stepsPer1000Feet;
protected:
private:

//functions
public:
	AltitudeDisplay(int a_stepPin, int a_dirPin, int a_ms1Pin, int a_ms2Pin, int a_minHeightDiffBeforeMoving, int a_stepsPer1000Feet);
	~AltitudeDisplay();
	bool NextUpdateIsLongOfDuration() { return false; }
	int UpdateMeter();
protected:
private:

}; //AltitudeDisplay

#endif //__ALTITUDEDISPLAY_H__
