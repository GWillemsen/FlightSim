/* 
* Flaps.h
*
* Created: 20/10/2019 18:13:14
* Author: Gielw
*/


#ifndef __FLAPS_H__
#define __FLAPS_H__


class Flaps
{
//variables
public:
	float m_value;
protected:
private:

//functions
public:
	Flaps();
	~Flaps();
	bool NextRetrieveIsLongOfDuration() { return false; }
	void Update();
	bool HasChangedSinceLastCheck();
protected:
private:

}; //Flaps

#endif //__FLAPS_H__
