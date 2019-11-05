/* 
* ArtficialHorizion.cpp
*
* Created: 18/10/2019 15:48:43
* Author: Gielw
*/


#include "ArtficialHorizionDisplay.h"
#include "Arduino.h"

// default constructor
ArtficialHorizionDisplay::ArtficialHorizionDisplay(int a_pinPitchPot, int a_pinRollPot, int a_pinPitchA, int a_pinPitchB, int a_pinRollA, int a_pinRollB)
{
	this->m_pinPitchPot = a_pinPitchPot;
	this->m_pinRollPot = a_pinRollPot;
	this->m_pinPitchA = a_pinPitchA;
	this->m_pinPitchB = a_pinPitchB;
	this->m_pinRollA = a_pinRollA;
	this->m_pinRollB = a_pinRollB;
	pinMode(a_pinPitchA, OUTPUT);
	pinMode(a_pinPitchB, OUTPUT);
	pinMode(a_pinRollA, OUTPUT);
	pinMode(a_pinRollB, OUTPUT);
} //ArtficialHorizion

// default destructor
ArtficialHorizionDisplay::~ArtficialHorizionDisplay()
{
} //~ArtficialHorizion

int ArtficialHorizionDisplay::UpdateMeter()
{
	if (this->m_pitch > 0.05) // 0.05 is 18 degrees when normalized between 0 - 360
		this->m_pitch = 0.05;
	else if (this->m_pitch < -0.05)
		this->m_pitch = -0.05;
		
		
	if (this->m_rotation > 0.15) // 0.15 is 54 degrees when normalized between 0 - 360
		this->m_rotation = 0.15;
	else if (this->m_rotation < -0.15)
		this->m_rotation = -0.15;
		
		
	bool m_pitch = UpdatePart(this->m_pitch * 360, this->m_pinPitchPot, this->m_pinPitchA, this->m_pinPitchB, -20, 20, 0);
	bool m_roll = UpdatePart(this->m_rotation * 360, this->m_pinRollPot, this->m_pinRollA, this->m_pinRollB, -54, 54, 0);
	return (m_roll) ? 1 : 0;
}

bool ArtficialHorizionDisplay::UpdatePart(int a_degrees, int a_potPin, int a_pinA, int a_pinB, int a_minInput, int a_maxInput, int a_offset)
{
	// 500 op pot meter is middle
	int m_shouldValueOnPot = map(a_degrees, a_minInput, a_maxInput, 1000, 0);
	int m_potValue = analogRead(a_potPin);
	int m_returnValue = 0;
	bool m_inBelowRange = m_potValue + 7 >= m_shouldValueOnPot && m_potValue < m_shouldValueOnPot;
	bool m_inAboveRange = m_potValue - 7 <= m_shouldValueOnPot && m_potValue > m_shouldValueOnPot;
	if (m_potValue == m_shouldValueOnPot || m_inAboveRange || m_inBelowRange)
	{
		digitalWrite(a_pinA, LOW);
		digitalWrite(a_pinB, LOW);
		m_returnValue = 1;
	}
	else
	{
		int m_pinAValue = 0;
		int m_pinBValue = 0;
		int m_maxPwmValue = 50;
		if (m_potValue < m_shouldValueOnPot)
		{
			m_pinAValue = LOW;
			m_pinBValue = HIGH;
		}
		else
		{
			m_pinAValue = HIGH;
			m_pinBValue = LOW;
		}
		digitalWrite(a_pinA, m_pinAValue);
		digitalWrite(a_pinB, m_pinBValue);
		m_returnValue = 0;
	}
	return m_returnValue;
}
