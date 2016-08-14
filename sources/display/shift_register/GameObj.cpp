
#include "GameObj.h"



GameObj::GameObj()
{
	_enabled = false;
	_lastUpdate = 0;
	_x = -1;
	_y = -1;
	_hdir = 0;
	_vdir = 0;
	_speed = 0;
}


GameObj::~GameObj()
{
	
}

void GameObj::SetCanvas(Canvas *canvas)
{
	_canvas = *canvas;
}

Canvas *GameObj::GetCanvas()
{
	return &_canvas;
}