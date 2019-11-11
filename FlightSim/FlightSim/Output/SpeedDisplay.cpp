/* 
* SpeedMeter.cpp
*
* Created: 18/10/2019 15:24:33
* Author: Gielw
*/


#include "SpeedDisplay.h"
#include "Arduino.h"

// default constructor
SpeedDisplay::SpeedDisplay(int a_writePin, int a_maxKnts, int a_maxPwm)
{
	this->m_knots = 0;
	this->m_writePin = a_writePin;	
	pinMode(a_writePin, OUTPUT);
	this->m_maxKnts = a_maxKnts;
	this->m_maxPwm = a_maxPwm;	
} //SpeedMeter

// default destructor
SpeedDisplay::~SpeedDisplay()
{
	analogWrite(this->m_writePin, 0);
} //~SpeedMeter

int SpeedDisplay::UpdateMeter()
{
	int m_maxedOutValue = this->m_knots;
	if (m_maxedOutValue > this->m_maxKnts)
	{
		m_maxedOutValue = this->m_maxKnts;
	}
	int m_mappedValue = map(m_maxedOutValue, 0, this->m_maxKnts, 0, this->m_maxPwm);
	analogWrite(this->m_writePin, m_mappedValue);
	return 1;
}
