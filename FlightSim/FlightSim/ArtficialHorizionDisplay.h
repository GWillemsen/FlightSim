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
protected:
private:

//functions
public:
	ArtficialHorizionDisplay(int a_pinPitch, int a_pinRoll);
	~ArtficialHorizionDisplay();
	bool NextUpdateIsLongOfDuration() { return false; }
	void UpdateMeter();
protected:
private:
	ArtficialHorizionDisplay (const ArtficialHorizionDisplay &c );
	ArtficialHorizionDisplay& operator=( const ArtficialHorizionDisplay &c );

}; //ArtficialHorizion

#endif //__ARTFICIALHORIZION_H__
