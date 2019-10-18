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
protected:
private:

//functions
public:
	RPMDisplay();
	~RPMDisplay();
	bool NextUpdateIsLongOfDuration() { return false; }
	void UpdateMeter();
protected:
private:
	RPMDisplay( const RPMDisplay &c );
	RPMDisplay& operator=( const RPMDisplay &c );

}; //RPMDisplay

#endif //__RPMDISPLAY_H__
