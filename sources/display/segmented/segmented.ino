/*
 Name:		segmented.ino
 Created:	8/5/2016 12:35:04 AM
 Author:	baoliveira
*/

const unsigned int voltagePin = A0;
const unsigned int displayPinA = 2;
const unsigned int displayPinB = 3;
const unsigned int displayPinC = 4;
const unsigned int displayPinD = 5;
const unsigned int displayPinE = 6;
const unsigned int displayPinF = 7;
const unsigned int displayPinG = 8;
const unsigned int displayPinH = 9;

// voltage fields
const float voltageMax = 5;
unsigned long voltageOperationTime;
int voltageLastValue;
unsigned long voltageReadFrequency;

// display fields
unsigned long displayFrequency;
unsigned long displayOperationTime;

// the setup function runs once when you press reset or power the board
void setup() 
{
	// initialize serial communication at 9600 bits per second:
	Serial.begin(9600);

	voltageOperationTime = 0;
	voltageLastValue = 0;
	voltageReadFrequency = 100;

	pinMode(displayPinA, OUTPUT);
	pinMode(displayPinB, OUTPUT);
	pinMode(displayPinC, OUTPUT);
	pinMode(displayPinD, OUTPUT);
	pinMode(displayPinE, OUTPUT);
	pinMode(displayPinF, OUTPUT);
	pinMode(displayPinG, OUTPUT);
	pinMode(displayPinH, OUTPUT);

	displayFrequency = 33;
	displayOperationTime = 0;

	for (int i = 1; i <= 10; i++)
	{
		displayLedWrite(9);
		displayLedWrite(8);
		displayLedWrite(7);
		displayLedWrite(6);
		displayLedWrite(5);
		displayLedWrite(4);
		displayLedWrite(3);
		displayLedWrite(2);
		displayLedWrite(1);
		displayLedWrite(0);

	}
	
}

// the loop function runs over and over again until power down or reset
void loop() 
{
	float voltage = readVoltage(voltagePin);
	displayLedWrite(voltage);
	delay(500);
}

void displayLedSet(bool pinA, bool pinB, bool pinC, 
	bool pinDDot, bool pinEMid, 
	bool pinF, bool pinG, bool pinH)
{
	unsigned long time = millis();
	if (time - displayOperationTime < displayFrequency)
	{
		delay(displayFrequency - (time - displayOperationTime));
	}

	displayOperationTime = time;
	digitalWrite(displayPinA, pinA ? HIGH : LOW);
	digitalWrite(displayPinB, pinB ? HIGH : LOW);
	digitalWrite(displayPinC, pinC ? HIGH : LOW);

	digitalWrite(displayPinD, pinDDot ? HIGH : LOW);
	digitalWrite(displayPinE, pinEMid ? HIGH : LOW);

	digitalWrite(displayPinF, pinF ? HIGH : LOW);
	digitalWrite(displayPinG, pinG ? HIGH : LOW);
	digitalWrite(displayPinH, pinH ? HIGH : LOW);

}

void displayLedWrite(byte character)
{
	

	switch (character)
	{
	case 0:
		displayLedSet(true, true, true, false, false, true, true, true);
		break;
	case 1:
		displayLedSet(false, false, true, false, false, false, false, true);
		break;
	case 2:
		displayLedSet(true, true, false, false, true, false, true, true);
		break;
	case 3:
		displayLedSet(false, true, true, false, true, false, true, true);
		break;
	case 4:
		displayLedSet(false, false, true, false, true, true, false, true);
		break;
	case 5:
		displayLedSet(false, true, true, false, true, true, true, false);
		break;
	case 6:
		displayLedSet(true, true, true, false, true, true, true, false);
		break;
	case 7:
		displayLedSet(false, false, true, false, false, false, true, true);
		break;
	case 8:
		displayLedSet(true, true, true, false, true, true, true, true);
		break;
	case 9:
		displayLedSet(false, true, true, false, true, true, true, true);
		break;
	default :
		// exclamation mark '!' 6
		displayLedSet(false, false, false, true, false, false, false, true);
		Serial.println((byte)character);
		break;
	}
}

float readVoltage(unsigned int apin)
{
	unsigned long newRead = millis();
	if ((newRead - voltageOperationTime) < voltageReadFrequency)
	{
		return voltageLastValue;
	}
	else
	{
		// read the input on analog pin 0:
		int sensorValue = analogRead(apin);
		voltageOperationTime = newRead;

		// Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
		float voltage = sensorValue * (voltageMax / 1023.0);

		// print out the value you read:
		Serial.println(voltage);

		return voltage;
	}
}