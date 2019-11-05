/* 
* HeadingDisplay.cpp
*
* Created: 18/10/2019 16:14:27
* Author: Gielw
*/


#include "HeadingDisplay.h"

// default constructor
HeadingDisplay::HeadingDisplay(int a_startHeading)
{
	this->m_heading = a_startHeading;
} //HeadingDisplay

// default destructor
HeadingDisplay::~HeadingDisplay()
{
} //~HeadingDisplay

int HeadingDisplay::UpdateMeter()
{
	return 1;
}