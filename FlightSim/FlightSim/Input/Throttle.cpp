/* 
* Throttle.cpp
*
* Created: 19/10/2019 17:21:42
* Author: Gielw
*/


#include "Throttle.h"
#include "Arduino.h"

Throttle::Throttle(int a_readPin, bool a_invertRead, int a_pinMode)
{
	this->m_readPin = a_readPin;
	pinMode(this->m_readPin, a_pinMode);
	this->m_invertRead = a_invertRead;
} //Throttle

// default destructor
Throttle::~Throttle()
{
} //~Throttle

void Throttle::Update()
{
	int m_readValue = analogRead(this->m_readPin);
	if (this->m_invertRead)
	{
		m_readValue = 1024 - m_readValue;
	}
	if(m_readValue > this->m_lastRead + 5 || m_readValue < this->m_lastRead - 5)
	{
		this->m_lastRead = m_readValue;
		this->m_value = m_readValue / 1024.0;
	}
}

bool Throttle::HasChangedSinceLastCheck()
{
	if (this->m_value != this->m_previousValue)
	{
		this->m_previousValue = this->m_value;
		return true;
	}
	else
	{
		return false;
	}
}
