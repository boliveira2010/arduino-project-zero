#include "Fire.h"

Fire::Fire()
{
	
	
}


Fire::~Fire()
{
}

void Fire::Initialize(byte* screenPtr, byte screenWidth, byte screenHeight)
{
	// fire properties
	SetX(0);
	SetY(0);
	
	SetHDir(0);
	SetVDir(1);
	SetSpeed(12);
	SetLastUpdate(0);
	SetEnabled(false);
	
	Canvas *canvas = GetCanvas();
	canvas->SetWidth(1);
	canvas->SetHeight(1);
	canvas->SetImage(fire);
	canvas->SetScreenWidth(screenWidth);
	canvas->SetScreenHeight(screenHeight);
	canvas->SetScreen(screenPtr);

	/*
	if ((canvas->GetScreen()) != screenPtr)
	{
		Serial.println(" test 1 - pointers diferentes");
	}
	if (*(canvas->GetScreen()) != *screenPtr)
	{
		Serial.println(" test 2 - valores de pointers diferentes");
	}
	Serial.println("fim fire init");
	*/
}

void Fire::Update()
{
	if (GetEnabled() && (millis() - GetLastUpdate()) > 1000 / GetSpeed())
	{
		if (GetLastUpdate() != 0)
			GetCanvas()->InvalidateRect(GetX(), GetY());

		SetY(GetY() + GetVDir());
		
		if ((GetY() + GetHeight() - 1) > GetCanvas()->GetScreenHeight() - 1)
		{
			SetEnabled(false);
			SetLastUpdate(0);
		}
		else if (GetY() < 0)
		{
			SetEnabled(false);
			SetLastUpdate(0);
		}

		if (GetEnabled())
		{
			/*
			Serial.print(GetX());
			Serial.print(",");
			Serial.print(GetY());
			*/
			GetCanvas()->Paint(GetX(), GetY());
			SetLastUpdate(millis());
		}
	}

}
