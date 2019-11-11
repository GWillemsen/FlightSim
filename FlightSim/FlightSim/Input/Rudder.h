/* 
* Ruder.h
*
* Created: 21/10/2019 11:37:44
* Author: Gielw
*/


#ifndef __RUDER_H__
#define __RUDER_H__
#include "Arduino.h"

class Rudder
{
//variables
public:
	float m_position;
	int m_readPin;
	bool m_invertRead;
	int m_lastRead;
	float m_previousValue;
protected:
private:

//functions
public:
	Rudder(int a_readPin) : Rudder (a_readPin, false, INPUT) {}
	Rudder(int a_readPin, bool a_invertRead) : Rudder(a_readPin, a_invertRead, INPUT) {}
	Rudder(int a_readPin, bool a_invertRead, int a_pinMode);
	~Rudder();
	void Update();
	bool HasChangedSinceLastCheck();
protected:
private:

}; //Ruder

#endif //__RUDER_H__
