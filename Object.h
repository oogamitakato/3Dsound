#pragma once
#include "Scroll.h"
#include "Player.h"

class Object
{
public:

	//メンバ変数
	int x;
	int y;
	int radius;
	int objectDistance = 0;//オブジェクトとの距離

	Scroll* scroll;

	int sound;
	int playTimer = 0;
	int volume = 200;
	int pan = 0;

	//メンバ関数
	Object(int x, int y, int radius, int sound);
	void Draw();
	void Sound(Player player);
};