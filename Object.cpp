#include "DxLib.h"
#include "Object.h"
#include "Player.h"

Object::Object(int x, int y, int radius, int sound)
{
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->sound = sound;

	this->scroll = new Scroll(0, 0, 5);
}

//オブジェクトを描画する関数
void Object::Draw()
{
	scroll->Move();
	DrawCircle(x - scroll->x, y - scroll->y, radius, GetColor(0, 0, 255), TRUE);
}

//オブジェクトから発せられる音の関数
void Object::Sound(Player player)
{
	//一定の間隔で音を鳴らす
	if (playTimer == 1)
	{
		PlaySoundMem(sound, DX_PLAYTYPE_LOOP, TRUE);
	}
	else if (playTimer > 50)
	{
		playTimer = 1;
	}
	playTimer++;

	//オブジェクトとの距離をとる
	objectDistance =
		(((x - player.x) * (x - player.x)) + ((y - player.y) * (y - player.y))
			- (radius + player.radius) * (radius + player.radius)) / 2500;

	//距離をもとに音量を調節
	if (objectDistance > 0)
	{
		volume = -objectDistance + 255;
	}
	else
	{
		volume = objectDistance + 255;
	}

	//左右判定をもとにパン値を調節
	pan = (x - player.x) / 2;

	ChangeVolumeSoundMem(volume, sound);
	ChangePanSoundMem(pan, sound);

}