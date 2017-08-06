/*
 Name:		Sketch1.ino
 Created:	7/31/2016 1:00:33 PM
 Author:	baoliveira
*/

int servoPin1 = 9;
const unsigned int servoFrequency = 20;
unsigned int servoStep = 10;
unsigned int servoMinStep = 10;
unsigned int servoMaxStep = 100;
unsigned int servoMaxPos = 2700;
unsigned int servoMinPos = 400;
unsigned int servoPos = 1500;
unsigned int servoAceleration = 10;

// the setup function runs once when you press reset or power the board
void setup() 
{
	Serial.begin(9600);
	pinMode(servoPin1, OUTPUT);
	if (Serial.availableForWrite())
		Serial.println("Servo 9g initialization");

	Serial.println("going to position 0.");
	delay(3000);
	// pos zero
	servoPulse(14, servoPos);
	servoAceleration = 10;
}

// the loop function runs over and over again until power down or reset
void loop() 
{

	//delay(500);
	// pos from current pos to -90 step by step
	servoMoveTo(servoMinPos);
	/*
	delay(2000);
	// pos from current position to +90 max speed
	servoPulse(14, servoMaxPos);
	
	delay(2000);
	// pos from current position to -90 max speed
	servoPulse(14, servoMinPos);
	*/
	//delay(500);
	// pos from -90 to +90 step by step
	servoMoveTo(servoMaxPos);

	servoStep += servoAceleration;

	if (servoStep > servoMaxStep)
	{
		servoStep = servoMaxStep;
		servoAceleration = servoAceleration * (-1);
	} 
	else if (servoStep < servoMinStep)
	{
		servoStep = servoMinStep;
		servoAceleration = servoAceleration * (-1);
	}
}


void servoMoveTo(unsigned int targetPosition)
{
	if (targetPosition == servoPos)
		return;
	else if (targetPosition > servoPos)
	{

		for (int position = servoPos; position <= targetPosition; position += servoStep)
		{
			servoPulse(1, position);
		}
	}
	else
	{
		for (int position = servoPos; position >= targetPosition; position -= servoStep)
		{
			servoPulse(1, position);
		}
	}

	servoPos = targetPosition;
}

void servoPulse(unsigned int steps, unsigned int pulseWidth)
{
	for(int i = 1; i<= steps; i++)
	{
		digitalWrite(servoPin1, HIGH);
		delayMicroseconds(pulseWidth);
		digitalWrite(servoPin1, LOW);
		delay(servoFrequency);
	}
}