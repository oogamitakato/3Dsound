#include "Scroll.h"
#include "Player.h"
#include "Dxlib.h"

Scroll::Scroll(int x, int y, int speed)
{
	this->x = x;
	this->y = y;
	this->speed = speed;
}

void Scroll::Move()
{
	if (CheckHitKey(KEY_INPUT_W) == true)
	{
		y -= speed;
	}

	if (CheckHitKey(KEY_INPUT_S) == true)
	{
		y += speed;
	}

	if (CheckHitKey(KEY_INPUT_A) == true)
	{
		x -= speed;
	}

	if (CheckHitKey(KEY_INPUT_D) == true)
	{
		x += speed;
	}
}