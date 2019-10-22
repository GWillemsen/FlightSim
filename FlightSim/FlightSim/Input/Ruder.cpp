/* 
* Ruder.cpp
*
* Created: 21/10/2019 11:37:44
* Author: Gielw
*/


#include "Ruder.h"
#include "Arduino.h"

Ruder::Ruder(int a_readPin, bool a_invertRead, int a_pinMode)
{
	this->m_readPin = a_readPin;
	pinMode(this->m_readPin, a_pinMode);
	this->m_invertRead = a_invertRead;
} //Ruder

// default destructor
Ruder::~Ruder()
{
} //~Ruder

void Ruder::Update()
{
	int m_readValue = analogRead(this->m_readPin);
	if (this->m_invertRead)
	{
		m_readValue = 1024 - m_readValue;
	}
	this->m_position = m_readValue / 1024.0;
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
