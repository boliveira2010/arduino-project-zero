/*
 Name:		shift_register.ino
 Created:	8/12/2016 1:00:31 PM
 Author:	baoliveira
*/

#include "Fire.h"
#include "Line.h"
#include "Ship.h"

// shift register pins
int latchPin = 2;
int clockPin = 3;
int dataPin = 4;

// ground pins for matrix because we dont have another shift register
int col1Pin = 5;
int col2Pin = 6;
int col3Pin = 7;
int col4Pin = 8;
int col5Pin = 9;
int col6Pin = 10;
int col7Pin = 11;
int col8Pin = 12;

int powerButtonsPin = A0;
int LFTButtonPin = A1;
int RGTButtonPin = A2;

// the column pins array
int columnIds[8] = { col1Pin, col2Pin, col3Pin, col4Pin, col5Pin, col6Pin, col7Pin, col8Pin };

// a 64 bit canvas (8 bytes x 8 bit)
// each position represents a column
byte matrix[8] =
{
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000
};

// the screen height
const int screenHeight = 8;
// the screen width
const int screenWidth = 8;

// game variables
Ship shipObj;
Fire fireLFTObj;
Fire fireRGTObj;
Line lineObj;

//user interface 
unsigned long lastTimeLFTButton = 0;
unsigned long lastTimeRGTButton = 0;


// the setup function runs once when you press reset or power the board
void setup()
{
	Serial.begin(9600);

	pinMode(dataPin, OUTPUT);
	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);

	pinMode(col1Pin, OUTPUT);
	pinMode(col2Pin, OUTPUT);
	pinMode(col3Pin, OUTPUT);
	pinMode(col4Pin, OUTPUT);
	pinMode(col5Pin, OUTPUT);
	pinMode(col6Pin, OUTPUT);
	pinMode(col7Pin, OUTPUT);
	pinMode(col8Pin, OUTPUT);

	// disable all columns
	digitalWrite(col1Pin, HIGH);
	digitalWrite(col2Pin, HIGH);
	digitalWrite(col3Pin, HIGH);
	digitalWrite(col4Pin, HIGH);
	digitalWrite(col5Pin, HIGH);
	digitalWrite(col6Pin, HIGH);
	digitalWrite(col7Pin, HIGH);
	digitalWrite(col8Pin, HIGH);
	
	fireLFTObj.Initialize(matrix, screenWidth, screenHeight);
	fireRGTObj.Initialize(matrix, screenWidth, screenHeight);
	
	lineObj.Initialize(matrix, screenWidth, screenHeight);
	shipObj.Initialize(matrix, screenWidth, screenHeight);

	clearCanvas(matrix, 8);

	// left, right buttons and power 
	pinMode(LFTButtonPin, INPUT);
	pinMode(RGTButtonPin, INPUT);

	pinMode(powerButtonsPin, OUTPUT);
	digitalWrite(powerButtonsPin, HIGH);
}

// the loop function runs over and over again until power down or reset
void loop()
{
	// z order canvas being painted 
	// we need to paint it only when moving or changing form.
	// each canvas represents a game object being updated
	// update ship
	
	// update ship
	shipObj.Update();

	if (((millis() - lastTimeLFTButton) > 500) && (digitalRead(LFTButtonPin) == HIGH) )
	{
		lastTimeLFTButton = millis();
		fireLFTObj.SetEnabled(true);
		fireLFTObj.SetX(shipObj.GetX());
		fireLFTObj.SetY(shipObj.GetY()+1);
		
	}
	if (((millis() - lastTimeRGTButton) > 500) && (digitalRead(RGTButtonPin) == HIGH))
	{
		lastTimeRGTButton = millis();
		fireRGTObj.SetEnabled(true);
		fireRGTObj.SetX(shipObj.GetX() + shipObj.GetWidth() - 1);
		fireRGTObj.SetY(shipObj.GetY()+1);
	}
	// update line
	lineObj.Update();
	
	// update fire
	fireLFTObj.Update();
	fireRGTObj.Update();

	refreshScreen();
}


void refreshScreen()
{
	int previousCol = screenWidth - 1;
	for (int col = 0; col < screenWidth; col++)
	{
		// take data and feed the shift-registers
		digitalWrite(latchPin, LOW);
		shiftOut(dataPin, clockPin, LSBFIRST, matrix[col]);

		// turn off previous column
		digitalWrite(columnIds[previousCol], HIGH);
		// set row pixels high
		digitalWrite(latchPin, HIGH);
		// turn on current column
		digitalWrite(columnIds[col], LOW);

		previousCol = col;
	}

}

/*
void paintCanvas(byte target[], byte width, byte x, byte y)
{

	for (byte col = 0; col < width; col++)
	{
		matrix[col+x] = matrix[col+x] | (target[col] << y);
	}
}
*/

void clearCanvas(byte target[], byte size)
{
	for (byte pos = 0; pos < size; pos++)
	{
		target[pos] = 0;
	}
}
/*
void invalidateCanvas(byte target[], byte width, byte x, byte y)
{
	for (byte col = 0; col < width; col++)
	{
		matrix[col + x] = matrix[col + x] ^ (target[col] << (y));
	}
}
*/