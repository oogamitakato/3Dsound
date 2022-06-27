#pragma once

class Scroll
{
public:
	int x;
	int y;
	int speed;

	Scroll(int x, int y, int speed);

	void Move();
};
