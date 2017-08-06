const int outPinPowerPhotoResistor = 2;
int counter;

void setup()
{
	Serial.begin(9600);
	pinMode(outPinPowerPhotoResistor, OUTPUT);
	digitalWrite(outPinPowerPhotoResistor, HIGH);
	Serial.println("POWER IS ON");
	int counter = 10;
}

void loop()
{
	delay(5000);
	digitalWrite(outPinPowerPhotoResistor, LOW);
	delay(5000);
	digitalWrite(outPinPowerPhotoResistor, HIGH);
	counter--;
	if (counter <= 0)
	{
		counter = 10;
		delay(250);
		digitalWrite(outPinPowerPhotoResistor, LOW);
		delay(250);
		digitalWrite(outPinPowerPhotoResistor, HIGH);
		delay(250);
		digitalWrite(outPinPowerPhotoResistor, LOW);
		delay(250);
		digitalWrite(outPinPowerPhotoResistor, HIGH);
		delay(250);
		digitalWrite(outPinPowerPhotoResistor, LOW);
		delay(250);
		digitalWrite(outPinPowerPhotoResistor, HIGH);
		delay(500);
	}
}
