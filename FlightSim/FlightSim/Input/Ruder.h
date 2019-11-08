/* 
* Ruder.h
*
* Created: 21/10/2019 11:37:44
* Author: Gielw
*/


#ifndef __RUDER_H__
#define __RUDER_H__
#include "Arduino.h"

class Ruder
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
	Ruder(int a_readPin) : Ruder (a_readPin, false, INPUT) {}
	Ruder(int a_readPin, bool a_invertRead) : Ruder(a_readPin, a_invertRead, INPUT) {}
	Ruder(int a_readPin, bool a_invertRead, int a_pinMode);
	~Ruder();
	void Update();
	bool HasChangedSinceLastCheck();
protected:
private:

}; //Ruder

#endif //__RUDER_H__
