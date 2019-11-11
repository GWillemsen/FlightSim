/* 
* Throttle.h
*
* Created: 19/10/2019 17:21:43
* Author: Gielw
*/


#ifndef __THROTTLE_H__
#define __THROTTLE_H__
#include "Arduino.h"

class Throttle
{
//variables
public:
	float m_value;
	int m_readPin;
	bool m_invertRead;
	int m_lastRead = 0;
	float m_previousValue = 0;
protected:
private:

//functions
public:
	Throttle(int a_readPin) : Throttle(a_readPin, false, INPUT) {}
	Throttle(int a_readPin, bool a_invertRead) : Throttle(a_readPin, a_invertRead, INPUT) {}
	Throttle(int a_readPin, bool a_invertRead, int a_pinMode);
	~Throttle();
	void Update();
	bool HasChangedSinceLastCheck();
protected:
private:

}; //Throttle

#endif //__THROTTLE_H__
