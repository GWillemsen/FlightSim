/* 
* ADFDisplay.cpp
*
* Created: 18/10/2019 16:18:02
* Author: Gielw
*/


#include "ADFDisplay.h"

// default constructor
ADFDisplay::ADFDisplay(int a_startHeading)
{
	this->m_heading = a_startHeading;
} //ADFDisplay

// default destructor
ADFDisplay::~ADFDisplay()
{
} //~ADFDisplay

int ADFDisplay::UpdateMeter()
{
	return 1;
}