#ifndef Line_h
#define Line_h

#include "GameObj.h"
#include "Arduino.h"

class Line :
	public GameObj
{
private:
	
	// line bitmap
	const byte line[1] =
	{
		B111
	};

public:
	Line();
	~Line();

	void Initialize(byte* screenPtr, byte screenWidth, byte screenHeight);
	void Update();

};


#endif