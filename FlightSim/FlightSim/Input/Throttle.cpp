/* 
* Throttle.cpp
*
* Created: 19/10/2019 17:21:42
* Author: Gielw
*/


#include "Throttle.h"

// default constructor
Throttle::Throttle()
{
} //Throttle

// default destructor
Throttle::~Throttle()
{
} //~Throttle

void Throttle::Update()
{
	
}

bool Throttle::HasChangedSinceLastCheck()
{
	static float m_previousValue = 0;
	if (this->m_value != m_previousValue)
	{
		m_previousValue = this->m_value;
		return true;
	}
	else
	{
		return false;
	}
}
