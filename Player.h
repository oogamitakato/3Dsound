#pragma once
#include "Scroll.h"

class Player
{
public:

	//メンバ変数
	int x;
	int y;
	int radius;
	Scroll* scroll;

	//メンバ関数
	Player(int x, int y, int radius);
	void Move();
	void Draw();
};