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
	SetY(5);

	SetHDir(0);
	SetVDir(-1);
	SetSpeed(5);
	SetLastUpdate(0);
	SetEnabled(true);

	Canvas *canvas = GetCanvas();
	canvas->SetWidth(1);
	canvas->SetHeight(3);
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
