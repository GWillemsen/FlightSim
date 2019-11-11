#include "ADFDisplay.h"
#include "AltitudeDisplay.h"
#include "ArtficialHorizionDisplay.h"
#include "ClimbingDisplay.h"
#include "HeadingDisplay.h"
#include "RPMDisplay.h"
#include "SpeedDisplay.h"
#include "TurnSlipDisplay.h"
#include "Flaps.h"
#include "Ruder.h"
#include "Throttle.h"
#include "SimpleSwitch.h"
#ifdef __AS7__
#include <Arduino.h>
#endif

#define USE_DISPLAY 1

#ifdef USE_DISPLAY
#include "LiquidCrystal_I2C.h"
#endif

// function prototypes
#ifdef __AS7__
void GetPartData(int m_partIndex, int& m_line, String &m_val, int &m_offset);
void SetupMeterArrays();
void UpdateMeterValues();
void CheckForSendNewInput();
void UpdateInputValues();
void ReadSerialData();
void ProcessingInputLines(String &data);
void PrintFloat(float a_number, int a_decimals);
void loop();
void setup();
#endif

// Display helpers (FlightGear outputs)
ADFDisplay m_adfDisplay(0);
AltitudeDisplay m_altitudeDisplay(31, 32, 29, 30, 20, 20); // fix the MS1, and MS2 pins
ArtficialHorizionDisplay m_ahDisplay(10, 11, 34, 35, 36, 37); //13, 12, 7, 8);
ClimbingDisplay m_climbingDisplay(3, 4, 102, 97, -1500, 1500); // Bij 5V 63 & 62, Bij 3.3V 102, 97
HeadingDisplay m_headingDisplay(0);
RPMDisplay m_rpmDisplay(5, 3000, 195); // Bij 3.3V 195,
SpeedDisplay m_speedDisplay(2, 240, 174);  // Bij 5V 108, bij 3.3V 174  // 220knots = 118
TurnSlipDisplay m_tunSlipDisplay(6, 7, 1000, 1000); // not used, not enough time

// FlightGear inputs
Flaps m_flaps(8, 26);
Throttle m_throttle(9);
Ruder m_ruder(7);
SimpleSwitch m_parkingBreak(25, false, INPUT_PULLUP);
SimpleSwitch m_carborator(24, true, INPUT_PULLUP);
SimpleSwitch m_mixture(22, false, INPUT_PULLUP);
SimpleSwitch m_landingLights(27, false, INPUT_PULLUP);
#ifdef USE_DISPLAY
LiquidCrystal_I2C display(0x3F, 20, 4); // 0x27 or 0x3F
#endif
MeterBasis* m_meters[8];

void setup() {
	Serial.begin(57600);
	Serial.println("Starting INIT");
	#if USE_DISPLAY
	display.init();
	display.clear();
	display.setBacklight(1);
	display.print(".");
	#endif
	SetupMeterArrays();
	Serial.println("Starting loop");
	m_altitudeDisplay.m_altitude = 1000;
	while(m_altitudeDisplay.UpdateMeter() == 0)
	{
		delay(1);
		Serial.println("Updateing altitude");
	}
}

void loop() {
	UpdateInputValues();
	CheckForSendNewInput();
	ReadSerialData();
	UpdateMeterValues();
}

void SetupMeterArrays()
{
	Serial.print("Setting up meter array...");
	m_meters[0] = &m_adfDisplay;
	m_meters[1] = &m_altitudeDisplay;
	m_meters[2] = &m_ahDisplay;
	m_meters[3] = &m_climbingDisplay;
	m_meters[4] = &m_headingDisplay;
	m_meters[5] = &m_rpmDisplay;
	m_meters[6] = &m_speedDisplay;
	m_meters[7] = &m_tunSlipDisplay;
	Serial.println("Done");
}

void UpdateMeterValues()
{
	bool m_hasToUpdate = true;
	bool m_isUpdated[7];
	m_isUpdated[0] = false;
	m_isUpdated[1] = true;
	m_isUpdated[2] = false;
	m_isUpdated[3] = false;
	m_isUpdated[4] = false;
	m_isUpdated[5] = false;
	m_isUpdated[6] = false;
	int m_finishedCount = 0;
	unsigned long m_startTime = millis();
	
	while (m_finishedCount != 7 && millis() - m_startTime < 10)
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
				else if(partIndex == 8)
					toUpdateField = &m_tunSlipDisplay.m_slip;
				else if(partIndex == 9)
					toUpdateField = &m_tunSlipDisplay.m_turn;
				
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
				GetPartData(partIndex, m_line, m_val, m_offset);
				
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

void GetPartData(int m_partIndex, int& m_line, String &m_val, int &m_offset)
{
	if(m_partIndex == 0)
	{
		m_line = 1;
		m_val = "Sp: " + m_val;
	}
	else if(m_partIndex == 1)
	{
		m_line = 1;
		m_offset = 10;
		m_val = "Ro: " + m_val;
	}
	else if(m_partIndex == 2)
	{
		m_line = 2;
		m_offset = 0;
		m_val = "Pt: " + m_val;
	}
	else if(m_partIndex == 3)
	{
		m_line = 2;
		m_offset = 10;
		m_val = "He: " + m_val;
	}
	else if(m_partIndex == 4)
	{
		m_line = 3;
		m_offset = 0;
		m_val = "At: " + m_val;
	}
	else if(m_partIndex == 5)
	{
		m_line = 3;
		m_offset = 10;
		m_val = "Fp: " + m_val;
	}
	else if(m_partIndex == 5)
	{
		m_line = 3;
		m_offset = 10;
		m_val = "AD: " + m_val;
	}
	else if(m_partIndex == 7)
	{
		m_line = 4;
		m_val = "Rp: " + m_val;
	}
}

void UpdateInputValues()
{
	m_flaps.Update();
	m_throttle.Update();
	m_ruder.Update();
	m_parkingBreak.Update();
	m_carborator.Update();
	m_mixture.Update();
	m_landingLights.Update();
}

void CheckForSendNewInput()
{
	bool m_potMeters = m_throttle.HasChangedSinceLastCheck() ||
						m_flaps.HasChangedSinceLastCheck() ||
						m_ruder.HasChangedSinceLastCheck();
	
	bool m_switches = m_parkingBreak.HasChangedSinceLastCheck() ||
						m_carborator.HasChangedSinceLastCheck() ||
						m_mixture.HasChangedSinceLastCheck() ||
						m_landingLights.HasChangedSinceLastCheck();
	
	if (m_potMeters || m_switches)
	{
		PrintFloat(m_throttle.m_value, 3);
		Serial.print(",");
		PrintFloat(m_flaps.m_position, 2);
		Serial.print(",");
		PrintFloat(m_ruder.m_position, 3);
		Serial.print(",");
		Serial.print(m_carborator.m_value);
		//Serial.print(",");
		//Serial.print(m_mixture.m_value);
		Serial.print(",");
		Serial.print(m_landingLights.m_value);
		Serial.print(",");
		Serial.print(m_parkingBreak.m_value); // parking brake itself
		Serial.print(",");
		Serial.print(m_parkingBreak.m_value); // left brake double, in this case either full or non
		Serial.print(",");
		Serial.print(m_parkingBreak.m_value); // right brake double, in this case either full or non
		
		Serial.print("\n");
	}
}

// Prints the float with the given precision
void PrintFloat(float a_number, int a_decimals)
{
	int m_integerPart = (int)a_number;	
	
	if (a_number < 0 && a_number > -1)
	{
		Serial.print("-");
		a_number = -a_number;
	}
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
