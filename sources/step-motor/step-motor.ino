#include <stepper.h>

int IN4 = 11;
int IN3 = 10;
int IN2 = 9;
int IN1 = 8;
int STEP_MOTOR_BLUE = -1;
int STEP_MOTOR_PINK = -1;
int STEP_MOTOR_YELLOW = -1;
int STEP_MOTOR_ORANGE = -1;

int STEP_MOTOR_STEP = 1;
int STEP_MOTOR_DIR = 1;
int STEP_MOTOR_RPM = 60000
int STEP_MOTOR_STYLE = 1;
Stepper stepMotor1 = Stepper(2048, IN1, IN2, IN3, IN4);

void setup()
{
	Serial.begin(9600);
	initializeStepMotor(IN1, IN2, IN3, IN4);
	STEP_MOTOR_DIR = -1;
	STEP_MOTOR_RPM = STEP_MOTOR_MAX_RPM;
	//stepMotor1.setSpeed(6);

}

void loop()
{
	//stepMotor1.step(STEP_MOTOR_DIR * 2048);
	
	for (int revolution = 1; revolution <= 2048; revolution++)
	{
		rotateStepMotor(STEP_MOTOR_DIR);
		delay(STEP_MOTOR_RPM);
	}
	
	stepMotor(LOW, LOW, LOW, LOW);
	STEP_MOTOR_DIR = STEP_MOTOR_DIR * (-1);
	
	delay(2500);
}

void rotateStepMotor(int dir)
{
	if (Serial.available())
	{
		Serial.print("debug->step nr:");
		Serial.println(STEP_MOTOR_STEP);
	}

	switch (STEP_MOTOR_STEP)
	{
	case 1:
		stepMotor(HIGH, LOW, LOW, LOW);
		break;
	case 2:
		// wave
		stepMotor(LOW, HIGH, LOW, LOW);
		// full step 2 phases at a time
		// stepMotor(LOW, HIGH, HIGH, LOW);
		break;
	case 3:
		// wave
		stepMotor(LOW, LOW, HIGH, LOW);
		// full step 2 phases at a time
		//stepMotor(LOW, LOW, HIGH, HIGH);
		break;
	case 4:
		// wave 
		stepMotor(LOW, LOW, LOW, HIGH);
		// full step 2 phases at a time
		//stepMotor(HIGH, LOW, LOW, HIGH);
		break;
	case 5:
		// wave 
		stepMotor(HIGH, LOW, LOW, LOW);
		// full step 2 phases at a time
		//stepMotor(HIGH, HIGH, LOW, LOW);
		break;
	case 6:
		// wave
		stepMotor(LOW, HIGH, LOW, LOW);
		// full step 2 phases at a time
		//stepMotor(LOW, HIGH, HIGH, LOW);
		break;
	case 7:
		// wave
		stepMotor(LOW, LOW, HIGH, LOW);
		// full step 2 phases at a time
		//stepMotor(LOW, LOW, HIGH, HIGH);
		break;
	case 8:
		// wave
		stepMotor(LOW, LOW, LOW, HIGH);
		// full step 2 phases at a time
		//stepMotor(HIGH, LOW, LOW, HIGH);
		break;
	default:
		Serial.println("Error, motor step unknown.");
		break;
	}

	
	STEP_MOTOR_STEP += dir;
	if (STEP_MOTOR_STEP > 8)
		STEP_MOTOR_STEP = 1;
	else if (STEP_MOTOR_STEP <= 0)
		STEP_MOTOR_STEP = 8;

	if (Serial.available())
	{
		Serial.print("debug->next step nr:");
		Serial.println(STEP_MOTOR_STEP);
	}
}

void stepMotor(bool blue, bool pink, bool yellow, bool orange)
{
	digitalWrite(STEP_MOTOR_BLUE, blue);
	digitalWrite(STEP_MOTOR_PINK, pink);
	digitalWrite(STEP_MOTOR_YELLOW, yellow);
	digitalWrite(STEP_MOTOR_ORANGE, orange);
}

void initializeStepMotor(int blue, int pink, int yellow, int orange)
{
	STEP_MOTOR_BLUE = blue;
	STEP_MOTOR_PINK = pink;
	STEP_MOTOR_YELLOW = yellow;
	STEP_MOTOR_ORANGE = orange;

	pinMode(STEP_MOTOR_BLUE, OUTPUT);
	pinMode(STEP_MOTOR_PINK, OUTPUT);
	pinMode(STEP_MOTOR_YELLOW, OUTPUT);
	pinMode(STEP_MOTOR_ORANGE, OUTPUT);

	// set initial position
	stepMotor(HIGH, LOW, LOW, LOW);
}