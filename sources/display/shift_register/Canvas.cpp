#include "Canvas.h"



Canvas::Canvas()
{
}


Canvas::~Canvas()
{
	if (_imagePtr != 0)
	{
		delete[] _imagePtr;
	}
}


short Canvas::GetWidth()
{
	return _width;
}
void Canvas::SetWidth(short width)
{
	if (width != _width)
	{
		_width = width;
	}
}

short Canvas::GetHeight()
{
	return _height;
}
void Canvas::SetHeight(short height)
{
	if (height != _height)
	{
		_height = height;
	}
}


// care allocating new image instance
void Canvas::SetImage(const byte image[])
{
	if (_imagePtr != 0)
	{
		delete _imagePtr;
	}
	_imagePtr = new byte[_width];
	for (short i = 0; i < _width; i++)
	{
		_imagePtr[i] = image[i];
	}

}

byte* Canvas::GetImageArray()
{
	return _imagePtr;
}

void Canvas::SetScreenWidth(byte width)
{
	if (width != _screenWidth)
	{
		_screenWidth = width;
	}
}

byte Canvas::GetScreenWidth()
{
	return _screenWidth;
}

void Canvas::SetScreenHeight(byte height)
{
	_screenHeight = height;
}

byte Canvas::GetScreenHeight()
{
	return _screenHeight;
}

void Canvas::SetScreen(byte* screen)
{
	_screenPtr = screen;
}

byte* Canvas::GetScreen()
{
	return _screenPtr;
}

void Canvas::ClearScreen()
{
	byte size = GetScreenWidth();
	byte* screenPtr = GetScreen();

	for (byte pos = 0; pos < size; pos++)
	{
		
		*((byte*)(screenPtr + pos)) = 0;
	}
}

void Canvas::InvalidateRect(short x, short y)
{
	for (byte col = 0; col < _width; col++)
	{
		*((byte*)(_screenPtr + col + x)) = *((byte*)(_screenPtr + col + x)) ^ (*(byte*)(_imagePtr + col) << (y));
	}
}

void Canvas::Paint(short x, short y)
{
	for (byte col = 0; col < _width; col++)
	{
		
		Serial.print(_width);
		Serial.print("x");
		Serial.println(_height);

		Serial.println(*(_screenPtr + col + x));
		
		*((byte*)(_screenPtr + col + x)) = *((byte*)(_screenPtr + col + x)) | (*(byte*)(_imagePtr + col) << y);
		Serial.println("painted");
		Serial.println(*(_screenPtr + col + x));
		
	}

}

