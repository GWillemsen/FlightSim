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
protected:
private:

//functions
public:
	AltitudeDisplay();
	~AltitudeDisplay();
	bool NextUpdateIsLongOfDuration() { return false; }
	void UpdateMeter();
protected:
private:
	AltitudeDisplay( const AltitudeDisplay &c );
	AltitudeDisplay& operator=( const AltitudeDisplay &c );

}; //AltitudeDisplay

#endif //__ALTITUDEDISPLAY_H__
