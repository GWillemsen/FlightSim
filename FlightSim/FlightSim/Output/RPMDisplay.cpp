/* 
* RPMDisplay.cpp
*
* Created: 18/10/2019 16:20:30
* Author: Gielw
*/


#include "RPMDisplay.h"
#include "Arduino.h"

// default constructor
RPMDisplay::RPMDisplay(int a_writePin, int a_maxRpm, int a_maxPwm)
{
	this->m_rpms = 0;
	this->m_writePin = a_writePin;
	this->m_maxRpm = a_maxRpm;
	this->m_maxPwmValue = a_maxPwm;
	pinMode(a_writePin, OUTPUT);
} //RPMDisplay

// default destructor
RPMDisplay::~RPMDisplay()
{
	analogWrite(this->m_writePin, 0);
} //~RPMDisplay

void RPMDisplay::UpdateMeter()
{
	int m_maxedOutValue = this->m_rpms;
	if (m_maxedOutValue > this->m_maxRpm)
	{	
		m_maxedOutValue = this->m_maxRpm;
	}
	int m_mapedValue = map(this->m_rpms, 0, m_maxedOutValue, 0, this->m_maxPwmValue);
	analogWrite(this->m_writePin, m_mapedValue);
}
