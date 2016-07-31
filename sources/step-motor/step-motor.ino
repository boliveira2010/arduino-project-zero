//#include <stepper.h>
//Stepper stepMotor1 = Stepper(2048, IN1, IN2, IN3, IN4);

const int stepMotor_MaxFrequency = 2;
const int stepMotor_Revolution = 2048;
const int stepMotor_Mode_Wave = 0;
const int stepMotor_Mode_Full = 1;

int STEP_MOTOR_BLUE = 8;
int STEP_MOTOR_PINK = 9;
int STEP_MOTOR_YELLOW = 10;
int STEP_MOTOR_ORANGE = 11;

int stepMotor_Step = 1;
int stepMotor_Dir = 1;
int stepMotor_Frequency = 2;

void setup()
{
	Serial.begin(9600);
	initializeStepMotor(8, 9, 10, 11);
	stepMotor_Dir = -1;

	//stepMotor1.setSpeed(6);
}

void loop()
{
	//stepMotor1.step(STEP_MOTOR_DIR * 2048);
	stepMotor_Frequency = 4;
	rotationTest();
	
	delay(2500);
}

void rotationTest()
{
	// make two revolutions
	rotateStepMotor(stepMotor_Revolution * 2, stepMotor_Mode_Full, stepMotor_Dir);

	// turn off motor
	energizeStepMotor(LOW, LOW, LOW, LOW);
	// invert direction
	stepMotor_Dir = stepMotor_Dir * (-1);
}

// rotates the shaft in the defined direction with the selected mode.
// mode 0 - wave, 1 - full step
void rotateStepMotor(unsigned int steps, int mode, int dir)
{
	for (int currStep = 1; currStep <= steps; currStep++)
	{
		switch (stepMotor_Step)
		{
		case 1:
			energizeStepMotor(HIGH, LOW, LOW, LOW);
			break;
		case 2:
			// wave
			if (mode == 0)
				energizeStepMotor(LOW, HIGH, LOW, LOW);
			else if (mode == 1)
			{
				// full step 2 phases at a time
				energizeStepMotor(LOW, HIGH, HIGH, LOW);
			}
			break;
		case 3:
			// wave
			if (mode == 0)
				energizeStepMotor(LOW, LOW, HIGH, LOW);
			else if (mode == 1)
			{
				// full step 2 phases at a time
				energizeStepMotor(LOW, LOW, HIGH, HIGH);
			}

			break;
		case 4:
			// wave
			if (mode == 0)
				energizeStepMotor(LOW, LOW, LOW, HIGH);
			else if (mode == 1)
			{
				// full step 2 phases at a time
				energizeStepMotor(HIGH, LOW, LOW, HIGH);
			}

			break;
		default:
			Serial.println("Error, motor step unknown.");
			break;
		}

		// apply direction
		stepMotor_Step += dir;

		// check limits
		if (stepMotor_Step > 4)
			stepMotor_Step = 1;
		else if (stepMotor_Step <= 0)
			stepMotor_Step = 4;
	}
}

// energizes the defined phases to perform rotation
void energizeStepMotor(bool blue, bool pink, bool yellow, bool orange)
{
	digitalWrite(STEP_MOTOR_BLUE, blue);
	digitalWrite(STEP_MOTOR_PINK, pink);
	digitalWrite(STEP_MOTOR_YELLOW, yellow);
	digitalWrite(STEP_MOTOR_ORANGE, orange);
	delay(stepMotor_Frequency);
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
	energizeStepMotor(HIGH, LOW, LOW, LOW);
	energizeStepMotor(LOW, HIGH, LOW, LOW);
	energizeStepMotor(LOW, LOW, HIGH, LOW);
	energizeStepMotor(LOW, LOW, LOW, HIGH);
	energizeStepMotor(LOW, LOW, LOW, LOW);
}