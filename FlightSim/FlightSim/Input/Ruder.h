/* 
* Ruder.h
*
* Created: 21/10/2019 11:37:44
* Author: Gielw
*/


#ifndef __RUDER_H__
#define __RUDER_H__


class Ruder
{
//variables
public:
	float m_position;
protected:
private:

//functions
public:
	Ruder();
	~Ruder();
	void Update();
	bool HasChangedSinceLastCheck();
protected:
private:

}; //Ruder

#endif //__RUDER_H__
