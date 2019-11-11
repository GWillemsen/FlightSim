/* 
* TurnSlipDisplay.cpp
*
* Created: 05/11/2019 21:55:55
* Author: Gielw
*/


#include "TurnSlipDisplay.h"
#include "Arduino.h"

// default constructor
TurnSlipDisplay::TurnSlipDisplay(int a_slipPin, int a_turnPin, int a_totalSlipDegrees, int a_totalTurnDegrees)
{
	this->m_slipPin = a_slipPin;
	this->m_turnPin = a_turnPin;
	pinMode(a_slipPin, OUTPUT);
	pinMode(a_turnPin, OUTPUT);
	this->m_totalSlipDegrees = a_totalSlipDegrees;
	this->m_totalTurnDegrees = a_totalTurnDegrees;
} //TurnSlipDisplay

// default destructor
TurnSlipDisplay::~TurnSlipDisplay()
{
} //~TurnSlipDisplay

int TurnSlipDisplay::UpdateMeter()
{
	// multi by 1000 as map does not accept a floating point
	long m_maxSlipValueFromZero = this->m_totalSlipDegrees / 2;
	int m_slipMapped = map((long)(this->m_slip * 1000), -m_maxSlipValueFromZero, m_maxSlipValueFromZero, 0, 255);
	analogWrite(this->m_slipPin, m_slipMapped);
	
	long m_maxTurnValueFromZero = this->m_totalTurnDegrees / 2;
	int m_turnMapped = map((long)(this->m_turn * 1000), -m_maxTurnValueFromZero, m_maxTurnValueFromZero, 0, 255);
	analogWrite(this->m_turnPin, m_turnMapped);
	return 1;
}
