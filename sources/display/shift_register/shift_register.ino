/*
 Name:		shift_register.ino
 Created:	8/12/2016 1:00:31 PM
 Author:	baoliveira
*/

#include "Fire.h"
#include "Line.h"

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

// ship bitmap
byte ship[5] =
{
	B00001,
	B00010,
	B00100,
	B00010,
	B00001,
};

// ship properties
int shipX = 1;
int shipY = 0;
int shipWidth = 5;
int shipHeight = 5;
short shipHdir = 0;
short shipVdir = 1;
short shipSpeed = 3;
unsigned long shipLastTime;
bool startingShip = true;

Fire fireObj;
Line lineObj;

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
	
	fireObj.Initialize(matrix, screenWidth, screenHeight);
	lineObj.Initialize(matrix, screenWidth, screenHeight);
	
	clearCanvas(matrix, 8);
}


// the loop function runs over and over again until power down or reset
void loop()
{
	// z order canvas being painted 
	// we need to paint it only when moving or changing form.
	// each canvas represents a game object being updated
	// update ship
	
	// update ship
	if ((millis() - shipLastTime) > 1000 / shipSpeed)
	{
		if (startingShip)
		{
			startingShip = false;
		}
		else
			invalidateCanvas(ship, shipWidth, shipX, shipY);

		shipX += shipHdir;
		if ((shipX + shipWidth-1) > screenWidth-1)
		{
			shipX = screenWidth - shipWidth;
			shipHdir = shipHdir * (-1);
			shipX += shipHdir;
		}
		else if (shipX < 0)
		{
			shipX = 0;
			shipHdir = shipHdir * (-1);
			shipX += shipHdir;
		}

		shipY += shipVdir;
		if ((shipY + shipHeight-1) > screenHeight-1)
		{
			shipY = screenHeight - shipHeight;
			shipVdir = shipVdir * (-1);
			shipY += shipVdir;
		}
		else if (shipY < 0)
		{
			shipY = 0;
			shipVdir = shipVdir * (-1);
			shipY += shipVdir;
		}

		if (shipVdir == -1 && shipY == 1)
		{
			fireObj.SetEnabled(true);
			fireObj.SetX(shipX + shipWidth - 1);
			fireObj.SetY(1);
		}

		shipLastTime = millis();
		paintCanvas(ship, shipWidth, shipX, shipY);
	}

	// update line
	lineObj.Update();
	
	/*
	if ((millis() - lineLastTime) > 1000 / lineSpeed)
	{
		if (startingLine)
		{
			startingLine = false;
		}
		else
			invalidateCanvas(line, lineWidth, lineX, lineY);

		lineY += lineVdir;
		if ((lineY + lineHeight-1) > screenHeight-1)
		{
			lineY = screenHeight - lineHeight;
			lineVdir = lineVdir * (-1);
			lineY += lineVdir;
		}
		else if (lineY < 0)
		{
			lineY = 0;
			lineVdir = lineVdir * (-1);
			lineY += lineVdir;
		}

		lineLastTime = millis();
		paintCanvas(line, lineWidth, lineX, lineY);
	}
	*/

	// update fire
	fireObj.Update();
	
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
//byte height, 
void paintCanvas(byte target[], byte width, byte x, byte y)
{

	for (byte col = 0; col < width; col++)
	{
		/*
		Serial.println(width);
		Serial.println(matrix[col + x]);
		Serial.println(target[col] << y);
		*/
		matrix[col+x] = matrix[col+x] | (target[col] << y);
	}
}

void clearCanvas(byte target[], byte size)
{
	for (byte pos = 0; pos < size; pos++)
	{
		target[pos] = 0;
	}
}

void invalidateCanvas(byte target[], byte width, byte x, byte y)
{
	for (byte col = 0; col < width; col++)
	{
		/*
		Serial.println(width);
		Serial.println(matrix[col + x-1]);
		Serial.println(target[col] << (y-1));
		*/
		matrix[col + x] = matrix[col + x] ^ (target[col] << (y));
	}
}