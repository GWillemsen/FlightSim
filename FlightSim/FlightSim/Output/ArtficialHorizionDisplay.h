/* 
* ArtficialHorizion.h
*
* Created: 18/10/2019 15:48:43
* Author: Gielw
*/


#ifndef __ARTFICIALHORIZION_H__
#define __ARTFICIALHORIZION_H__
#include "MeterBasis.h"

class ArtficialHorizionDisplay : public MeterBasis
{
public:
	float m_rotation;
	float m_pitch;
	int m_pinPitchPot;
	int m_pinRollPot;
	int m_pinPitchA;
	int m_pinPitchB;
	int m_pinRollA;
	int m_pinRollB;
protected:
private:

//functions
public:
	ArtficialHorizionDisplay(int a_pinPitchPot, int a_pinRollPot, int a_pinPitchA, int a_pinPitchB, int a_pinRollA, int a_pinRollB);
	~ArtficialHorizionDisplay();
	bool NextUpdateIsLongOfDuration() { return false; }
	int UpdateMeter();
protected:
private:
	bool UpdatePart(int a_degrees, int a_potPin, int a_pinA, int a_pinB, int a_minInput, int a_maxInput, int a_offset);

}; //ArtficialHorizion

#endif //__ARTFICIALHORIZION_H__
