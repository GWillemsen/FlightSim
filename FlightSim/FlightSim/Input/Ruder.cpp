/* 
* Ruder.cpp
*
* Created: 21/10/2019 11:37:44
* Author: Gielw
*/


#include "Ruder.h"

// default constructor
Ruder::Ruder()
{
} //Ruder

// default destructor
Ruder::~Ruder()
{
} //~Ruder

void Ruder::Update()
{
	
}

bool Ruder::HasChangedSinceLastCheck()
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
