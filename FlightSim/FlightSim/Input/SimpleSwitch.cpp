/* 
* SimpleSwitch.cpp
*
* Created: 20/10/2019 18:14:02
* Author: Gielw
*/


#include "SimpleSwitch.h"
#include "Arduino.h"

SimpleSwitch::SimpleSwitch(int a_readPin, bool a_inverted, int a_pinMode)
{
	this->m_readPin = a_readPin;
	pinMode(this->m_readPin, a_pinMode);
	this->m_inverted = a_inverted;
}

// default destructor
SimpleSwitch::~SimpleSwitch()
{
} //~SimpleSwitch

void SimpleSwitch::Update()
{
	int m_readValue = digitalRead(this->m_readPin);
	if (this->m_inverted)
	{
		this->m_value = m_readValue == LOW;		
	}
	else
	{
		this->m_value = m_readValue == HIGH;
	}
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
