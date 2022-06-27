#pragma once
#include "Scroll.h"
#include "Player.h"

class Object
{
public:

	//�����o�ϐ�
	int x;
	int y;
	int radius;
	int objectDistance = 0;//�I�u�W�F�N�g�Ƃ̋���

	Scroll* scroll;

	int sound;
	int playTimer = 0;
	int volume = 200;
	int pan = 0;

	//�����o�֐�
	Object(int x, int y, int radius, int sound);
	void Draw();
	void Sound(Player player);
};