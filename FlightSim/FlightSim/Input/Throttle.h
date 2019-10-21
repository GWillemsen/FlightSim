/* 
* Throttle.h
*
* Created: 19/10/2019 17:21:43
* Author: Gielw
*/


#ifndef __THROTTLE_H__
#define __THROTTLE_H__


class Throttle
{
//variables
public:
	float m_value;
protected:
private:

//functions
public:
	Throttle();
	~Throttle();
	bool NextRetrieveIsLongOfDuration() { return false; }
	void Update();
	bool HasChangedSinceLastCheck();
protected:
private:

}; //Throttle

#endif //__THROTTLE_H__
