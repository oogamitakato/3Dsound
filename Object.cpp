#include "DxLib.h"
#include "Object.h"
#include "Player.h"

int Object::objectDiveder = 2500;
int Object::maxPlayTimer = 50;
int Object::maxVolume = 255;

Object::Object(int x, int y, int radius, int sound)
{
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->sound = sound;

	this->scroll = new Scroll(0, 0, 5);
}

//�I�u�W�F�N�g��`�悷��֐�
void Object::Draw()
{
	scroll->Move();
	DrawCircle(x - scroll->x, y - scroll->y, radius, GetColor(0, 0, 255), TRUE);
}

//�I�u�W�F�N�g���甭�����鉹�̊֐�
void Object::Sound(Player player)
{
	//���̊Ԋu�ŉ���炷
	if (playTimer == 1)
	{
		PlaySoundMem(sound, DX_PLAYTYPE_LOOP, TRUE);
	}
	else if (playTimer > maxPlayTimer)
	{
		playTimer = 1;
	}

	playTimer++;

	//�I�u�W�F�N�g�Ƃ̋������Ƃ�
	objectDistance =
		(((x - player.x) * (x - player.x)) + ((y - player.y) * (y - player.y))
			- (radius + player.radius) * (radius + player.radius)) / objectDiveder;

	//���������Ƃɉ��ʂ𒲐�
	if (objectDistance > 0)
	{
		volume = -objectDistance + maxVolume;
	}
	else
	{
		volume = objectDistance + maxVolume;
	}

	//���E��������ƂɃp���l�𒲐�
	pan = (x - player.x) / 2;

	ChangeVolumeSoundMem(volume, sound);
	ChangePanSoundMem(pan, sound);

}