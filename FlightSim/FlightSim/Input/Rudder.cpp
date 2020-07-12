/*
* Ruder.cpp
*
* Created: 21/10/2019 11:37:44
* Author: Gielw
*/


#include "Rudder.h"
#include "Arduino.h"

Rudder::Rudder(int a_readPin, bool a_invertRead, int a_pinMode)
{
	this->m_readPin = a_readPin;
	pinMode(this->m_readPin, a_pinMode);
	this->m_invertRead = a_invertRead;
} //Ruder

// default destructor
Rudder::~Rudder()
{
} //~Ruder

void Rudder::Update()
{
	int m_readValue = (int)analogRead(this->m_readPin);
	if (this->m_invertRead)
	{
		m_readValue = 1024 - m_readValue;
	}
	  
	int in_min = 360;
	int in_max = 620;
	int out_max = 1;
	int out_min = -1;
	if (m_readValue < in_min)
		m_readValue = in_min;
	else if (m_readValue > in_max)
		m_readValue = in_max;
	if(m_readValue > this->m_lastRead + 5 || m_readValue < this->m_lastRead - 5)
	{
		this->m_lastRead = m_readValue;
		this->m_position = ((float)m_readValue - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
}

bool Rudder::HasChangedSinceLastCheck()
{
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
