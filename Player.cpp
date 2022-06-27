#include "Player.h"
#include "DxLib.h"

Player::Player(int x, int y, int radius)
{
	this->x = x;
	this->y = y;
	this->radius = radius;

	this->scroll = new Scroll(0, 0, 5);
}

//プレイヤーを移動させる関数
void Player::Move()
{
	if (CheckHitKey(KEY_INPUT_W) == true)
	{
		y -= scroll->speed;
	}

	if (CheckHitKey(KEY_INPUT_S) == true)
	{
		y += scroll->speed;
	}

	if (CheckHitKey(KEY_INPUT_A) == true)
	{
		x -= scroll->speed;
	}

	if (CheckHitKey(KEY_INPUT_D) == true)
	{
		x += scroll->speed;
	}
}

//プレイヤーを描画する関数
void Player::Draw()
{
	scroll->Move();
	DrawCircle(x - scroll->x, y - scroll->y, radius, GetColor(255, 0, 0), TRUE);
}