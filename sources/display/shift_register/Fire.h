#ifndef Fire_h
#define Fire_h

#include "GameObj.h"

class Fire :
	public GameObj
{
protected:
	// fire bitmap

	const byte fire[1] =
	{
		B1
	};

public:
	
	Fire();
	~Fire();

	void Initialize(byte* screenPtr, byte screenWidth, byte screenHeight);
	void Update();
};

#endif