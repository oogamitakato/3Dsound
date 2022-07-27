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

	//ブロックのサイズ
	const int BlockSize = 128;

	static int objectDiveder;
	static int maxPlayTimer;
	static int maxVolume;
    int volume;
	int playTimer = 0;
	int sound;
	int pan = 0;

	//メンバ関数
	Object(int x, int y, int radius, int sound);
	void Draw();
	void Sound(Player player);
};