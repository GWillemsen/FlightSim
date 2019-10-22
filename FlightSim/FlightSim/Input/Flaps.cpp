/* 
* Flaps.cpp
*
* Created: 20/10/2019 18:13:13
* Author: Gielw
*/


#include "Flaps.h"
#include "Arduino.h"

Flaps::Flaps(int a_readPin, bool a_invertRead, int a_pinMode)
{
	this->m_readPin = a_readPin;
	pinMode(this->m_readPin, a_pinMode);
	this->m_invertRead = a_invertRead;
} //Flaps

// default destructor
Flaps::~Flaps()
{
} //~Flaps

void Flaps::Update()
{
	int m_readValue = analogRead(this->m_readPin);
	if (this->m_invertRead)
	{
		m_readValue = 1024 - m_readValue;
	}
	this->m_readPin = m_readValue / 1024.0;
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
