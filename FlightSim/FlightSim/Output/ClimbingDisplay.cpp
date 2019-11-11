/* 
* ClimbingMeter.cpp
*
* Created: 18/10/2019 16:14:56
* Author: Gielw
*/


#include "ClimbingDisplay.h"
#include "Arduino.h"

// default constructor
ClimbingDisplay::ClimbingDisplay(int a_upperScalePin, int a_lowerScalePin, int a_maxLowerScalePwm, int a_maxUpperScalePwm, int a_minClimbValue, int a_maxClimbValue)
{
	 this->m_feetPerMinut = 0;
	 this->m_lowerScalePin = a_lowerScalePin;
	 this->m_upperScalePin = a_upperScalePin;
	 pinMode(a_lowerScalePin, OUTPUT);
	 pinMode(a_upperScalePin, OUTPUT);
	 
	 this->m_maxLowerScalePwm = a_maxLowerScalePwm;
	 this->m_maxUpperScalePwm = a_maxUpperScalePwm;
	 this->m_minClimbValue = a_minClimbValue;
	 this->m_maxClimbValue = a_maxClimbValue;
} //ClimbingMeter

// default destructor
ClimbingDisplay::~ClimbingDisplay()
{
	analogWrite(this->m_upperScalePin, 0);
	analogWrite(this->m_lowerScalePin, 0);
} //~ClimbingMeter

int ClimbingDisplay::UpdateMeter()
{
	int m_uperScaleValue = 0;
	int m_lowerScaleValue = 0;
	int m_convertedValue = this->m_feetPerMinut;
	if (m_convertedValue > this->m_maxClimbValue)
	{
		m_convertedValue = this->m_maxClimbValue;
	}
	else if(m_convertedValue < this->m_minClimbValue)
	{
		m_convertedValue = this->m_minClimbValue;
	}
	
	int m_minClibm = this->m_minClimbValue;
	int m_maxClimb = this->m_maxClimbValue;
	int m_lowerPwm = -this->m_maxLowerScalePwm;
	int m_upperPwm = this->m_maxUpperScalePwm;
	int m_mappedValue = map(m_convertedValue, m_minClibm, m_maxClimb, m_lowerPwm, m_upperPwm);
	
	if(m_mappedValue > 0)
	{		
		m_uperScaleValue = m_mappedValue;
	}
	else if (m_mappedValue < 0)
	{	
		m_lowerScaleValue = -m_mappedValue;
	}
	
	
	analogWrite(this->m_upperScalePin, m_uperScaleValue);
	analogWrite(this->m_lowerScalePin, m_lowerScaleValue);
	return 1;
}
