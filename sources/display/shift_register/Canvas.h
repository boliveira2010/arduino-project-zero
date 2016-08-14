#ifndef Canvas_h
#define Canvas_h
#include "Arduino.h"

class Canvas
{
protected:
	byte* _screenPtr = 0;
	byte _screenWidth = 0;
	byte _screenHeight = 0;
	byte* _imagePtr = 0;
	short _width;
	short _height;
public:
	Canvas();
	~Canvas();

	short GetWidth();
	void SetWidth(short width);
	short GetHeight();
	void SetHeight(short height);

	void SetImage(const byte image[]);
	byte* GetImageArray();

	void SetScreenWidth(byte width);
	byte GetScreenWidth();

	void SetScreenHeight(byte height);
	byte GetScreenHeight();


	void SetScreen(byte* screen);
	byte* GetScreen();

	void ClearScreen();
	void InvalidateRect(short x, short y);
	void Paint(short x, short y);
};

#endif