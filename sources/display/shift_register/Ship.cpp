#include "Ship.h"



Ship::Ship()
{
}


Ship::~Ship()
{
}

void Ship::Initialize(byte* screenPtr, byte screenWidth, byte screenHeight)
{
	// fire properties
	SetX(1);
	SetY(0);

	SetHDir(0);
	SetVDir(1);
	SetSpeed(3);
	SetLastUpdate(0);
	SetEnabled(true);

	Canvas *canvas = GetCanvas();
	canvas->SetWidth(5);
	canvas->SetHeight(5);
	canvas->SetImage(ship);
	canvas->SetScreenWidth(screenWidth);
	canvas->SetScreenHeight(screenHeight);
	canvas->SetScreen(screenPtr);
}

void Ship::Update()
{
	if (GetEnabled() && (millis() - GetLastUpdate()) > 1000 / GetSpeed())
	{
		if (GetLastUpdate() != 0)
			GetCanvas()->InvalidateRect(GetX(), GetY());

		SetY(GetY() + GetVDir());

		if ((GetY() + GetHeight() - 1) > GetCanvas()->GetScreenHeight() - 1)
		{
			SetY(GetCanvas()->GetScreenHeight() - GetHeight());
			SetVDir(GetVDir() * (-1));
			SetY(GetY() + GetVDir());
		}
		else if (GetY() < 0)
		{
			SetY(0);
			SetVDir(GetVDir() * (-1));
			SetY(GetY() + GetVDir());
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
