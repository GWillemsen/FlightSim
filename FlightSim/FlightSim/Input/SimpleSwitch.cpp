/* 
* SimpleSwitch.cpp
*
* Created: 20/10/2019 18:14:02
* Author: Gielw
*/


#include "SimpleSwitch.h"

// default constructor
SimpleSwitch::SimpleSwitch()
{
} //SimpleSwitch

// default destructor
SimpleSwitch::~SimpleSwitch()
{
} //~SimpleSwitch

void SimpleSwitch::Update()
{
	
}

bool SimpleSwitch::HasChangedSinceLastCheck()
{
	static bool m_previousValue = 0;
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
