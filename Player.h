#pragma once
#include "Scroll.h"

class Player
{
public:

	//�����o�ϐ�
	int x;
	int y;
	int radius;
	Scroll* scroll;

	//�����o�֐�
	Player(int x, int y, int radius);
	void Move();
	void Draw();
};