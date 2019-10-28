/* 
* AltitudeDisplay.cpp
*
* Created: 18/10/2019 16:19:47
* Author: Gielw
*/


#include "AltitudeDisplay.h"
#include "Arduino.h"

// default constructor
AltitudeDisplay::AltitudeDisplay(int a_stepPin, int a_dirPin, int a_valueOfOneStep)
{
	this->m_altitude = 0;
	this->m_stepPin = a_stepPin;
	this->m_dirPin = a_dirPin;
	this->m_valueOfOneStep = a_valueOfOneStep;
} //AltitudeDisplay

// default destructor
AltitudeDisplay::~AltitudeDisplay()
{
} //~AltitudeDisplay

int AltitudeDisplay::UpdateMeter()
{
	static float m_lastAltitude = 0;
	static bool m_lastStateStepPin = false;
	static unsigned long m_lastSetMicro = micros();
	int m_roundingRemainder = (int)this->m_altitude % this->m_valueOfOneStep;
	int m_roundedAltitude = this->m_altitude;
	if (m_roundingRemainder > this->m_valueOfOneStep - (this->m_valueOfOneStep / 4))
	{
		m_roundedAltitude += (this->m_valueOfOneStep - m_roundingRemainder);
	}
	else
	{
		m_roundedAltitude -= m_roundingRemainder;
	}
	
	
	if (m_roundedAltitude > m_lastAltitude)
	{
		bool m_direction = m_roundedAltitude < m_lastAltitude;
		digitalWrite(this->m_dirPin, m_direction);
		if (micros() - m_lastSetMicro > 100)
		{
			if (m_lastStateStepPin)
			{
				digitalWrite(this->m_stepPin, LOW);
				m_lastStateStepPin = false;
				m_lastAltitude += this->m_valueOfOneStep;
				m_lastSetMicro = micros();
			}
			else
			{
				digitalWrite(this->m_stepPin, HIGH);
				m_lastStateStepPin = true;
				m_lastSetMicro = micros();
			}
		}
		return 0;
	}
	else
	{
		return 1;
	}
}
