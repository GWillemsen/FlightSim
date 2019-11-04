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
	pinMode(a_stepPin, OUTPUT);
	pinMode(a_dirPin, OUTPUT);
	pinMode(a_ms1Pin, OUTPUT);
	pinMode(a_ms2Pin, OUTPUT);
	digitalWrite(m_ms1Pin, LOW);
	digitalWrite(m_ms2Pin, HIGH);
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
	static unsigned int m_lastMicros = 0;
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
		int m_microDelay = micros() - m_lastMicros;
		if (m_microDelay > 150000)
		{
			m_microDelay = 500000;
		}
		if (m_microDelay < 500)
		{
			if (m_directionIsUp)
			{
				Serial.println(m_calcHeight);
				m_stepsFromZero += 1;
			}
			else
			{
				Serial.println(m_calcHeight);
				m_stepsFromZero -= 1;
			}
				
			if (m_heightDiff > this->m_minHeightDiffBeforeMoving * 2)
			{
				m_returnValue = 0;
			}
			else
			{
				m_returnValue = 1;
			}
			digitalWrite(this->m_dirPin, m_directionIsUp);
			digitalWrite(this->m_stepPin, LOW);
			digitalWrite(this->m_stepPin, HIGH);
			delayMicroseconds(m_microDelay);
			Serial.println("Step was 10MS HIGH, now going to LOW");
			digitalWrite(this->m_stepPin, LOW);
			m_lastMicros = micros();
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
