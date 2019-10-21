/* 
* Flaps.cpp
*
* Created: 20/10/2019 18:13:13
* Author: Gielw
*/


#include "Flaps.h"

// default constructor
Flaps::Flaps()
{
} //Flaps

// default destructor
Flaps::~Flaps()
{
} //~Flaps

void Flaps::Update()
{	
	
}

bool Flaps::HasChangedSinceLastCheck()
{
	static float m_previousValue = 0;
	if (this->m_position != m_previousValue)
	{
		m_previousValue = this->m_position;
		return true;
	}
	else
	{
		return false;
	}
}
