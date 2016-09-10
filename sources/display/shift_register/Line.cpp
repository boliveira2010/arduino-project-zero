#include "Line.h"



Line::Line()
{
}


Line::~Line()
{
}

void Line::Initialize(byte* screenPtr, byte screenWidth, byte screenHeight)
{
	// fire properties
	SetX(7);
	SetY(7);

	SetHDir(-1);
	SetVDir(0);
	SetSpeed(5);
	SetLastUpdate(0);
	SetEnabled(true);

	Canvas *canvas = GetCanvas();
	canvas->SetWidth(2);
	canvas->SetHeight(1);
	canvas->SetImage(line);
	canvas->SetScreenWidth(screenWidth);
	canvas->SetScreenHeight(screenHeight);
	canvas->SetScreen(screenPtr);

}

void Line::Update()
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


		//move horizontal
		SetX(GetX() + GetHDir());

		//control screen limits and rever direction
		if ((GetX() + GetWidth() - 1) > GetCanvas()->GetScreenWidth() - 1)
		{
			SetX(GetCanvas()->GetScreenWidth() - GetWidth());
			SetHDir(GetHDir() * (-1));
			SetX(GetX() + GetHDir());
		}
		else if (GetX() < 0)
		{
			SetX(0);
			SetHDir(GetHDir() * (-1));
			SetX(GetX() + GetHDir());
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
