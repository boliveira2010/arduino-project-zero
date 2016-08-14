/*
 Name:		shift_register.ino
 Created:	8/12/2016 1:00:31 PM
 Author:	baoliveira
*/

int latchPin = 2;
int clockPin = 3;
int dataPin = 4;

int col1Pin = 5;
int col2Pin = 6;
int col3Pin = 7;
int col4Pin = 8;
int col5Pin = 9;
int col6Pin = 10;
int col7Pin = 11;
int col8Pin = 12;

//int rowIds[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
int columnIds[8] = { col1Pin, col2Pin, col3Pin, col4Pin, col5Pin, col6Pin, col7Pin, col8Pin };

// a 64 bit canvas (8 bytes - 8 bit)
// each position represents a column
byte matrix[8] =
{
	B10001000,
	B01010000,
	B00100000,
	B01010000,
	B10001000,
	B00000000,
	B00000000,
	B00000000
};

const int screenHeight = 8;
const int screenWidth = 8;

// game variables

byte ship[5] =
{
	B00001,
	B00010,
	B00100,
	B00010,
	B00001,
};

int shipX = 0;
int shipY = 0;
int shipWidth = 5;
int shipHeight = 5;
short shipHdir = 0;
short shipVdir = 1;
short shipSpeed = 3;
unsigned long shipLastTime;

byte line[1] =
{
	B111
};

int lineX = 7;
int lineY = 5;
int lineWidth = 1;
int lineHeight = 3;
short lineHdir = 0;
short lineVdir = -1;
short lineSpeed = 5;
unsigned long lineLastTime;

byte fire[1] =
{
	B1
};

int fireX = 0;
int fireY = 0;
int fireWidth = 1;
int fireHeight = 1;
short fireHdir = 0;
short fireVdir = 1;
short fireSpeed = 10;
unsigned long fireLastTime;

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


	digitalWrite(col1Pin, HIGH);
	digitalWrite(col2Pin, HIGH);
	digitalWrite(col3Pin, HIGH);
	digitalWrite(col4Pin, HIGH);
	digitalWrite(col5Pin, HIGH);
	digitalWrite(col6Pin, HIGH);
	digitalWrite(col7Pin, HIGH);
	digitalWrite(col8Pin, HIGH);
	/*
	// Do this for MSBFIRST serial
	int data = 1;
	// shift out highbyte
	shiftOut(dataPin, clockPin, MSBFIRST, (data >> 8));
	// shift out lowbyte
	shiftOut(dataPin, clockPin, MSBFIRST, data);
	*/

	clearCanvas(matrix, 8);
	//paintCanvas(cross, 5);
	delay(3000);

}

bool startingShip = true;
bool startingLine = true;

// the loop function runs over and over again until power down or reset
void loop()
{
	// z order canvas being painted 
	// we need to paint it only when moving or changing form.
	// each canvas represents a game object being updated
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

		shipLastTime = millis();
		paintCanvas(ship, shipWidth, shipX, shipY);
	
	}

	// update line
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