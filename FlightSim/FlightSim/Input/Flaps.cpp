/* 
* Flaps.cpp
*
* Created: 20/10/2019 18:13:13
* Author: Gielw
*/


#include "Flaps.h"
#include "Arduino.h"

Flaps::Flaps(int a_readPin, int a_enablePin, bool a_invertRead, int a_pinMode)
{
	this->m_readPin = a_readPin;
    this->m_enablePin = a_enablePin;
	pinMode(this->m_readPin, a_pinMode);
	pinMode(this->m_enablePin, INPUT_PULLUP);
	this->m_invertRead = a_invertRead;
} //Flaps

// default destructor
Flaps::~Flaps()
{
} //~Flaps

void Flaps::Update()
{
	this->m_flapsEnabled = digitalRead(this->m_enablePin) == LOW;
    if (this->m_flapsEnabled)
	{		
		int m_readValue = analogRead(this->m_readPin);
		if (this->m_invertRead)
		{
			m_readValue = 1024 - m_readValue;
		}
		if(m_readValue > this->m_lastRead + 5 || m_readValue < this->m_lastRead - 5)
		{
			this->m_lastRead = m_readValue;
			this->m_position = m_readValue / 1024.0;
		}
	}
	else
	{
		this->m_lastRead = 0;
		this->m_position = 0;
	}
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
