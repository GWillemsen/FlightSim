/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */


// function prototypes
void ReadSerialData();
void ProcessingInputLines(String &data);
void loop();
void setup();

// FlightGear variables
float throttle = 0;
bool parkingBrake = false;
bool leftWheelBrake = false;
bool rightWheelBrake = false;
float flaps = 0;
float ruder = 0;

float speed = 0;
float ahRoll = 0;
float ahPitch = 0;
float heading = 0;
float altitude = 0;
float climbing = 0;
float adf = 0;
float rpm = 0;

float totalSeconds = 10;
unsigned long endTimeRunning = millis() + (totalSeconds * 1000);
bool running = false;
unsigned long count = 0;

void setup() {
	Serial.begin(19200);
	Serial.println("Starting loop");
	running = true;
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
					toUpdateField = &speed;
				else if (partIndex == 1)
					toUpdateField = &ahRoll;
				else if (partIndex == 2)
					toUpdateField = &ahPitch;
				else if (partIndex == 3)
					toUpdateField = &heading;
				else if (partIndex == 4)
					toUpdateField = &altitude;
				else if (partIndex == 5)
					toUpdateField = &climbing;
				else if (partIndex == 6)
					toUpdateField = &adf;
				else if(partIndex == 7)
					toUpdateField = &rpm;
				
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
