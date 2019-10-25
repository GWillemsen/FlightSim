/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
/*End of auto generated code by Atmel studio */

#include "Output/ADFDisplay.h"
#include "Output/AltitudeDisplay.h"
#include "Output/ArtficialHorizionDisplay.h"
#include "Output/ClimbingDisplay.h"
#include "Output/HeadingDisplay.h"
#include "Output/RPMDisplay.h"
#include "Output/SpeedDisplay.h"
#include "Input/Flaps.h"
#include "Input/Ruder.h"
#include "Input/Throttle.h"
#include "Input/SimpleSwitch.h"
#include "LiquidCrystal_I2C.h"
//#define USE_DISPLAY


// function prototypes
void UpdateMeterValues();
void CheckForSendNewInput();
void UpdateInputValues();
void ReadSerialData();
void ProcessingInputLines(String &data);
void PrintFloat(float a_number, int a_decimals);
void loop();
void setup();

// Display helpers (FlightGear outputs)
ADFDisplay m_adfDisplay = ADFDisplay();
AltitudeDisplay m_altitudeDisplay = AltitudeDisplay();
ArtficialHorizionDisplay m_ahDisplay = ArtficialHorizionDisplay(0, 0);
ClimbingDisplay m_climbingDisplay = ClimbingDisplay(5, 3, 63, 62, -1500, 1500);
HeadingDisplay m_headingDisplay = HeadingDisplay();
RPMDisplay m_rpmDisplay = RPMDisplay(9, 3000, 124);
SpeedDisplay m_speedDisplay = SpeedDisplay(10, 240, 108); // 220knots = 118
MeterBasis* m_meterDisplays[7];

// FlightGear inputs
Flaps m_flaps = Flaps(0);
Throttle m_throttle = Throttle(0);
Ruder m_ruder = Ruder(0);
SimpleSwitch m_parkingBreak = SimpleSwitch(0);

float totalSeconds = 10;
unsigned long endTimeRunning = millis() + (totalSeconds * 1000);
bool running = false;
unsigned long count = 0;
LiquidCrystal_I2C display = LiquidCrystal_I2C(0x3F, 20, 4); // 0x27 or 0x3F

void UpdateMeterValues()
{
	bool m_hasToUpdate = true;
	bool m_isUpdated[7];
	m_isUpdated[0] = false;
	m_isUpdated[1] = false;
	m_isUpdated[2] = false;
	m_isUpdated[3] = false;
	m_isUpdated[4] = false;
	m_isUpdated[5] = false;
	m_isUpdated[6] = false;
	int m_finishedCount = 0;
	MeterBasis* m_meters[7];
	m_meters[0] = &m_adfDisplay;
	m_meters[1] = &m_altitudeDisplay;
	m_meters[2] = &m_ahDisplay;
	m_meters[3] = &m_climbingDisplay;
	m_meters[4] = &m_headingDisplay;
	m_meters[5] = &m_rpmDisplay;
	m_meters[6] = &m_speedDisplay;
	while(m_finishedCount != 7)
	{
		for(int m_meterIndex = 0; m_meterIndex < 7; m_meterIndex++)
		{
			if (!m_isUpdated[m_meterIndex])
			{
				int m_res = m_meters[m_meterIndex]->UpdateMeter();
				if (m_res != 0)
				{
					m_finishedCount++;
					m_isUpdated[m_meterIndex] = true;
				}
			}
		}
	}	
}

void setup() {
	Serial.begin(19200);
	Serial.println("Starting loop");
	running = true;
	display.init();
	display.clear();
	display.setBacklight(1);
	display.print("hello world");
}

void loop() {
	
	/*UpdateInputValues();
	CheckForSendNewInput();*/
	ReadSerialData();
	UpdateMeterValues();
}

void ReadSerialData()
{
	static String m_serialData = "";
	
	// only read if there is data available
	if (Serial.available())
	{
		// set read time to 1 ms, so we only read available data
		Serial.setTimeout(1);
		int m_available = Serial.available();
		for (int m_index = 0; m_index < m_available; m_index++)
		{
			int m_data = Serial.read();
			if (m_data < 0)
				break;
			m_serialData += (char)m_data;
		}		
		char newline = '#';
		int data = m_serialData.indexOf(newline);
		//Serial.print((String)data + " " + (String)m_serialData.length() + "\n");
		
		ProcessingInputLines(m_serialData);
		// reset serial read timeout back to the default
		Serial.setTimeout(1000);
	}	
}

void ProcessingInputLines(String &data)
{
	int m_startPos = 0;
	int lineEnd = data.indexOf("#", m_startPos);
	while(lineEnd > -1)
	{
		#ifdef USE_DISPLAY
		display.clear();
		#endif
		/*display.print("  ");
		display.setCursor(9, 0);
		display.print("  ");
		display.setCursor(18, 0);
		display.print("  ");
		display.setCursor(9, 1);
		display.print("  ");
		display.setCursor(18, 1);
		display.print("  ");
		display.setCursor(9, 2);
		display.print("  ");
		display.setCursor(18, 2);
		display.print("  ");
		display.setCursor(9, 3);
		display.print("  ");
		display.setCursor(18, 3);*/
		int partIndex = 0;
		if (lineEnd == m_startPos)
		{
			m_startPos++;
		}
		else
		{
			while(m_startPos < lineEnd)
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
					toUpdateField = &m_climbingDisplay.m_feetPerMinut;
				else if (partIndex == 6)
					toUpdateField = &m_adfDisplay.m_heading;
				else if(partIndex == 7)
					toUpdateField = &m_rpmDisplay.m_rpms;					
				
				int nextSeparator = data.indexOf(",", m_startPos);
				// if the input is terminated or a next line is also available
				if (nextSeparator == -1 || nextSeparator > lineEnd)
					nextSeparator = lineEnd;

				// update the set variable with the new float value
				*toUpdateField = data.substring(m_startPos, nextSeparator).toFloat();
				
				#ifdef USE_DISPLAY
				float m_float = data.substring(m_startPos, nextSeparator).toFloat();
				String m_val = String(m_float, 1);
				int m_line = 0;
				int m_offset = 0;
				if(partIndex == 0)
				{
					m_line = 1;
					m_val = "Sp: " + m_val;
				}
				else if(partIndex == 1)
				{
					m_line = 1;
					m_offset = 10;
					m_val = "Ro: " + m_val;
				}
				else if(partIndex == 2)
				{
					m_line = 2;
					m_offset = 0;
					m_val = "Pt: " + m_val;
				}
				else if(partIndex == 3)
				{
					m_line = 2;
					m_offset = 10;
					m_val = "He: " + m_val;
				}
				else if(partIndex == 4)
				{
					m_line = 3;
					m_offset = 0;
					m_val = "At: " + m_val;
				}
				else if(partIndex == 5)
				{
					m_line = 3;
					m_offset = 10;
					m_val = "Fp: " + m_val;					
				}
				else if(partIndex == 5)
				{
					m_line = 3;
					m_offset = 10;
					m_val = "AD: " + m_val;
				}
				else if(partIndex == 7)
				{
					m_line = 4;
					m_val = "Rp: " + m_val;					
				}
				
				if (m_line)
				{
					for(int i = 0; i < m_val.length(); i++)
					{
						display.setCursor(i + m_offset, m_line - 1);						
						display.print(m_val[i]);
					}
					if (m_val.length() < 10)
					{
						for(int i = m_val.length(); i < 10; i++)
						{
							display.setCursor(i + m_offset, m_line - 1);
							display.print(" ");
						}						
						
					}
				}
				#endif
				// move to the next part of the input
				m_startPos = nextSeparator + 1;
				partIndex++;
			}
		}
		lineEnd = data.indexOf("#", m_startPos);
	}
	
	// if the startPos is at the end of the string, remove all, else only remove the read part
	if (m_startPos < data.length())
		data.remove(0, m_startPos);
	else
		data.remove(0);
}

void UpdateInputValues()
{
	m_flaps.Update();
	m_throttle.Update();
	m_ruder.Update();
	m_parkingBreak.Update();
}

void CheckForSendNewInput()
{
	if (m_flaps.HasChangedSinceLastCheck() ||
		m_throttle.HasChangedSinceLastCheck() ||
		m_ruder.HasChangedSinceLastCheck() ||
		m_parkingBreak.HasChangedSinceLastCheck())
		{
			PrintFloat(m_throttle.m_value, 4);
			Serial.print(",");
			Serial.print(m_parkingBreak.m_value); // parking brake itself
			Serial.print(",");
			Serial.print(m_parkingBreak.m_value); // left brake double, in this case either full or non
			Serial.print(",");
			Serial.print(m_parkingBreak.m_value); // right brake double, in this case either full or non
			Serial.print(",");
			PrintFloat(m_flaps.m_position, 4);
			Serial.print(",");
			PrintFloat(m_ruder.m_position, 4);
			Serial.print("\n");
		}	
}

// Prints the float with the given precision
void PrintFloat(float a_number, int a_decimals)
{	
	int m_integerPart = (int)a_number;
	Serial.print(m_integerPart);
	Serial.print(".");
	float m_decimal_part = a_number - ((int)a_number);
	m_decimal_part = m_decimal_part * 10;
	String m_data = (String)m_integerPart;
	while(a_decimals > 0)
	{
		m_data = (String)m_integerPart;
		m_integerPart = (int)m_decimal_part;
		Serial.print(m_integerPart);
		m_decimal_part -= m_integerPart;
		m_decimal_part *= 10;
		a_decimals--;
	}
}

