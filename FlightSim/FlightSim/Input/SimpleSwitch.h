/* 
* SimpleSwitch.h
*
* Created: 20/10/2019 18:14:03
* Author: Gielw
*/


#ifndef __SIMPLESWITCH_H__
#define __SIMPLESWITCH_H__
#include "Arduino.h"

class SimpleSwitch
{
//variables
public:
	bool m_value;
	int m_readPin;
	bool m_inverted;
protected:
private:

//functions
public:
	SimpleSwitch(int a_readPin) :SimpleSwitch(a_readPin, false, INPUT) {}
	SimpleSwitch(int a_readPin, bool a_inverted) : SimpleSwitch(a_readPin, a_inverted, INPUT) {}
	SimpleSwitch(int a_readPin, bool a_inverted, int a_pinMode);
	~SimpleSwitch();
	void Update();
	bool HasChangedSinceLastCheck();
protected:
private:

}; //SimpleSwitch

#endif //__SIMPLESWITCH_H__
