/* 
* AltitudeDisplay.cpp
*
* Created: 18/10/2019 16:19:47
* Author: Gielw
*/


#include "AltitudeDisplay.h"
#include "Arduino.h"

// default constructor
AltitudeDisplay::AltitudeDisplay(int a_stepPin, int a_dirPin, int a_ms1Pin, int a_ms2Pin, int a_minHeightDiffBeforeMoving, int a_stepsPer1000Feet)
{
	this->m_altitude = 0;
	this->m_stepPin = a_stepPin;
	this->m_dirPin = a_dirPin;
	this->m_ms1Pin = a_ms1Pin;
	this->m_ms2Pin = a_ms2Pin;
	pinMode(a_stepPin, OUTPUT);
	pinMode(a_dirPin, OUTPUT);
	pinMode(a_ms1Pin, OUTPUT);
	pinMode(a_ms2Pin, OUTPUT);
	digitalWrite(a_ms1Pin, LOW);
	digitalWrite(a_ms2Pin, HIGH);
	this->m_minHeightDiffBeforeMoving = a_minHeightDiffBeforeMoving;
	this->m_stepsPer1000Feet = a_stepsPer1000Feet;
} //AltitudeDisplay

// default destructor
AltitudeDisplay::~AltitudeDisplay()
{
} //~AltitudeDisplay

int AltitudeDisplay::UpdateMeter()
{
	static float m_stepsFromZero = 0;
	static unsigned int m_lastMillis = 0;
	bool m_directionIsUp = false;
	int m_calcHeight = (m_stepsFromZero / this->m_stepsPer1000Feet) * 1000;
	int m_heightDiff = 0;
	int m_isMatchForHeight = false;
	int m_returnValue = 1;
	if (m_calcHeight > this->m_altitude)
	{
		m_heightDiff = m_calcHeight - this->m_altitude;
		m_directionIsUp = false;
	}
	else
	{
		m_heightDiff = this->m_altitude - m_calcHeight;
		m_directionIsUp = true;
	}
	
	if (m_heightDiff > this->m_minHeightDiffBeforeMoving)
	{
		int m_millisDif = millis() - m_lastMillis;
		if (m_millisDif > 1)
		{
			int m_millisDelay = 0;
			if (m_heightDiff > this->m_minHeightDiffBeforeMoving * 2)
			{
				m_returnValue = 0;
			}
			else
			{
				m_returnValue = 1;
			}
		
			if (m_lastMillis > 20)
			{
				m_millisDelay = 10;
			}
			else
			{
				m_millisDelay = m_millisDif;
			}
			digitalWrite(this->m_dirPin, m_directionIsUp);
			m_stepsFromZero += 1;
			digitalWrite(this->m_stepPin, HIGH);
			delay(m_millisDelay);
			digitalWrite(this->m_stepPin, LOW);
			m_lastMillis = millis();	
		}
		else 
		{
			m_returnValue = 0;
		}
	}
	else
	{
		m_returnValue = 1;
	}
	return m_returnValue;
}
