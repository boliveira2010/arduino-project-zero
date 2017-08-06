#ifndef GameObj_h
#define GameObj_h

#include "Arduino.h"
#include "Canvas.h"

//base class gameobj
class GameObj
{
private:
	Canvas _canvas;
	
	bool _enabled;
	unsigned long _lastUpdate;
	short _x;
	short _y;
	short _hdir;
	short _vdir;
	short _speed;
protected:
	void SetCanvas(Canvas *canvas);
	Canvas *GetCanvas();

public:
	// returns if the object is enabled 
	bool GetEnabled()
	{
		return _enabled;
	}
	
	void SetEnabled(bool enabled)
	{
		if (enabled != _enabled)
		{
			_enabled = enabled;
		}
	}
	
	unsigned long GetLastUpdate()
	{
		return _lastUpdate;
	}

	void SetLastUpdate(unsigned long lastUpdate)
	{
		if (lastUpdate != _lastUpdate)
		{
			_lastUpdate = lastUpdate;
		}
	}

	short GetX()
	{
		return _x;
	}
	void SetX(short x)
	{
		if (x != _x)
		{
			_x = x;
		}
	}

	short GetY()
	{
		return _y;
	}
	void SetY(short y)
	{
		if (y != _y)
		{
			_y = y;
		}
	}

	short GetWidth()
	{
		return _canvas.GetWidth();
	}
	

	short GetHeight()
	{
		return _canvas.GetHeight();
	}

	
	short GetVDir()
	{
		return _vdir;
	}
	void SetVDir(short vdir)
	{
		if (vdir != _vdir)
		{
			_vdir = vdir;
		}
	}

	short GetHDir()
	{
		return _hdir;
	}
	void SetHDir(short hdir)
	{
		if (hdir != _hdir)
		{
			_hdir = hdir;
		}
	}

	short GetSpeed()
	{
		return _speed;
	}
	void SetSpeed(short speed)
	{
		if (speed != _speed)
		{
			_speed = speed;
		}
	}
	

	
	GameObj();

	~GameObj();
	
	// initialization of the game object
	virtual void Initialize(byte* screenPtr, byte screenWidth, byte screenHeight)
	{
		SetX(0);
		SetY(0);
		SetHDir(0);
		SetVDir(0);
		SetSpeed(0);
		SetLastUpdate(0);
		SetEnabled(false);
	};

	// updates the game object
	virtual void Update() = 0;
};

#endif