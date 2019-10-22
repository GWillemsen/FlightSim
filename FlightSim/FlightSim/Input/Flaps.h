/* 
* Flaps.h
*
* Created: 20/10/2019 18:13:14
* Author: Gielw
*/


#ifndef __FLAPS_H__
#define __FLAPS_H__
#include "Arduino.h"

class Flaps
{
//variables
public:
	float m_position;
	int m_readPin;
	bool m_invertRead;
protected:
private:

//functions
public:
	Flaps(int a_readPin) : Flaps(a_readPin, false, INPUT) {}
	Flaps(int a_readPin, bool a_invertRead) : Flaps(a_readPin, a_invertRead, INPUT) {}
	Flaps(int a_readPin, bool a_invertRead, int a_pinMode);
	~Flaps();
	void Update();
	bool HasChangedSinceLastCheck();
protected:
private:

}; //Flaps

#endif //__FLAPS_H__
