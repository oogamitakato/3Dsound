#pragma once
#include "Scroll.h"

class Player
{
public:

	//ƒƒ“ƒo•Ï”
	int x;
	int y;
	int radius;
	Scroll* scroll;

	//ƒƒ“ƒoŠÖ”
	Player(int x, int y, int radius);
	void Move();
	void Draw();
};