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
	bool m_flapsEnabled;
	int m_readPin;
	int m_enablePin;
	bool m_invertRead;
	int m_lastRead;
protected:
private:

//functions
public:
	Flaps(int a_readPin, int a_enablePin) : Flaps(a_readPin, a_enablePin, false, INPUT) {}
	Flaps(int a_readPin, int a_enablePin, bool a_invertRead) : Flaps(a_readPin, a_enablePin, a_invertRead, INPUT) {}
	Flaps(int a_readPin, int a_enablePin, bool a_invertRead, int a_pinMode);
	~Flaps();
	void Update();
	bool HasChangedSinceLastCheck();
protected:
private:

}; //Flaps

#endif //__FLAPS_H__
