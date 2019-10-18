/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
/*End of auto generated code by Atmel studio */

#include "ADFDisplay.h"
#include "AltitudeDisplay.h"
#include "ArtficialHorizionDisplay.h"
#include "ClimbingDisplay.h"
#include "HeadingDisplay.h"
#include "RPMDisplay.h"
#include "SpeedDisplay.h"

// function prototypes
void ReadSerialData();
void ProcessingInputLines(String &data);
void loop();
void setup();

// Display helpers
ADFDisplay m_adfDisplay = ADFDisplay();
AltitudeDisplay m_altitudeDisplay = AltitudeDisplay();
ArtficialHorizionDisplay m_ahDisplay = ArtficialHorizionDisplay(0, 0);
ClimbingDisplay m_climbingDisplay = ClimbingDisplay();
HeadingDisplay m_headingDisplay = HeadingDisplay();
RPMDisplay m_rpmDisplay = RPMDisplay();
SpeedDisplay m_speedDisplay = SpeedDisplay(5);


// FlightGear variables
float throttle = 0;
bool parkingBrake = false;
bool leftWheelBrake = false;
bool rightWheelBrake = false;
float flaps = 0;
float ruder = 0;


float totalSeconds = 10;
unsigned long endTimeRunning = millis() + (totalSeconds * 1000);
bool running = false;
unsigned long count = 0;

void setup() {
	Serial.begin(19200);
	Serial.println("Starting loop");
	running = true;
	m_speedDisplay.NextUpdateIsLongOfDuration();
	m_ahDisplay.NextUpdateIsLongOfDuration();
}

void loop() {
	if (!running)
		return;
	ReadSerialData();
	count = count + 1;
	if (endTimeRunning < millis())
	{	
		double cnt = (double)count;
		double hz = cnt / totalSeconds;
		Serial.print("Count: ");
		Serial.println(count);
		Serial.print("Hertz: ");
		Serial.println(hz);
		running = false;
	}
}

void ReadSerialData()
{
	static String serialData = "";
	
	// only read if there is data available
	if (Serial.available())
	{
		// set read time to 1 ms, so we only read available data
		Serial.setTimeout(1);
		serialData += Serial.readString();
		ProcessingInputLines(serialData);		
		// reset serial read timeout back to the default
		Serial.setTimeout(1000);
	}	
}

void ProcessingInputLines(String &data)
{
	int startPos = 0;
	int lineEnd = data.indexOf("\n", startPos);
	while(lineEnd > -1)
	{
		int partIndex = 0;
		if (lineEnd == startPos)
		{
			startPos++;
		}
		else
		{
			while(startPos < lineEnd)
			{
				// select the next property to update
				float* toUpdateField;
				if (partIndex == 0)
					toUpdateField = &m_speedDisplay.m_knots;
				else if (partIndex == 1)
					toUpdateField = &m_ahDisplay.m_rotation;
				else if (partIndex == 2)
					toUpdateField = &m_ahDisplay.m_pitch;
				else if (partIndex == 3)
					toUpdateField = &m_headingDisplay.m_heading;
				else if (partIndex == 4)
					toUpdateField = &m_altitudeDisplay.m_altitude;
				else if (partIndex == 5)
					toUpdateField = &m_climbingDisplay.m_speed;
				else if (partIndex == 6)
					toUpdateField = &m_adfDisplay.m_heading;
				else if(partIndex == 7)
					toUpdateField = &m_rpmDisplay.m_rpms;
				
				int nextSeparator = data.indexOf(",", startPos);
				// if the input is terminated or a next line is also available
				if (nextSeparator == -1 || nextSeparator > lineEnd)
					nextSeparator = lineEnd;
				
				// update the set variable with the new float value
				*toUpdateField = data.substring(startPos, nextSeparator).toFloat();
				
				// move to the next part of the input
				startPos = nextSeparator + 1;
				partIndex++;
			}
		}
		lineEnd = data.indexOf("\n", startPos);
	}
	
	// if the startPos is at the end of the string, remove all, else only remove the read part
	if (startPos < data.length())
		data.remove(0, startPos);
	else
		data.remove(0);
}
