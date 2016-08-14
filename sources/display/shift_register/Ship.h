#ifndef Ship_h
#define Ship_h

#include "GameObj.h"
#include "Arduino.h"

class Ship :
	public GameObj
{
private:
	// ship bitmap
	const byte ship[5] =
	{
		B00001,
		B00010,
		B00100,
		B00010,
		B00001,
	};

public:
	Ship();
	~Ship();

	void Initialize(byte* screenPtr, byte screenWidth, byte screenHeight);
	void Update();

};

#endif