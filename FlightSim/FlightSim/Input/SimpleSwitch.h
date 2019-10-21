/* 
* SimpleSwitch.h
*
* Created: 20/10/2019 18:14:03
* Author: Gielw
*/


#ifndef __SIMPLESWITCH_H__
#define __SIMPLESWITCH_H__


class SimpleSwitch
{
//variables
public:
	bool m_value;
protected:
private:

//functions
public:
	SimpleSwitch();
	~SimpleSwitch();
	bool NextRetrieveIsLongOfDuration() { return false; }
	void Update();
	bool HasChangedSinceLastCheck();
protected:
private:

}; //SimpleSwitch

#endif //__SIMPLESWITCH_H__
