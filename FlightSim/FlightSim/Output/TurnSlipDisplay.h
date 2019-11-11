/* 
* TurnSlipDisplay.h
*
* Created: 05/11/2019 21:56:00
* Author: Gielw
*/


#ifndef __TURNSLIPDISPLAY_H__
#define __TURNSLIPDISPLAY_H__

#include "MeterBasis.h"

class TurnSlipDisplay : public MeterBasis
{
//variables
public:
	float m_slip;
	float m_turn;
	int m_slipPin;
	int m_turnPin;
	int m_totalSlipDegrees;
	int m_totalTurnDegrees;
protected:
private:

//functions
public:
	TurnSlipDisplay(int a_slipPin, int a_turnPin, int a_totalSlipDegrees, int a_totalTurnDegrees);
	~TurnSlipDisplay();
	bool NextUpdateIsLongOfDuration() { return false; }
	int UpdateMeter();

}; //TurnSlipDisplay

#endif //__TURNSLIPDISPLAY_H__
