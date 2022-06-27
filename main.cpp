#include "DxLib.h"
#include "Player.h"
#include "Object.h"
#include "Scroll.h"
#include <math.h>

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "xx2x_xx_�i�}�G: �^�C�g��";

// �E�B���h�E����
const int WIN_WIDTH = 1280;

// �E�B���h�E�c��
const int WIN_HEIGHT = 960;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int mokugyoSound = LoadSoundMem("mokugyo.wav");
	int mokugyoSound2 = LoadSoundMem("mokugyo.wav");
	int fanfareSound = LoadSoundMem("fanfare.wav");

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	//�v���C���[�ɂ���
	Player* player = new Player(WIN_WIDTH / 2, WIN_HEIGHT / 2, 16);

	//�I�u�W�F�N�g�ɂ���
	Object* object = new Object(0, 0, 32, mokugyoSound);
	Object* object2 = new Object(-500, 0, 32, mokugyoSound2);
	Object* object3 = new Object(500, -500, 32, fanfareSound);


	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = {0};

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = {0};

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V���� 
		//�v���C���[�̈ړ�
		player->Move();
		object->Sound(*player);
		object2->Sound(*player);
		object3->Sound(*player);

		// �`�揈��
		for (int i = -20; i <= 20; i++)
		{
			DrawLine(i * 50 - object->scroll->x, -1000 - object->scroll->y,
					 i * 50 - object->scroll->x, 1000 - object->scroll->y, GetColor(100, 100, 100));
			DrawLine(-1000 - object->scroll->x, i * 50 - object->scroll->y,
					 1000 - object->scroll->x, i * 50 - object->scroll->y, GetColor(100, 100, 100));
		}
		 
		//�v���C���[�̕`��
		player->Draw();

		//�I�u�W�F�N�g�̕`��
		object->Draw();
		object2->Draw();
		object3->Draw();

		DrawFormatString(0, 0, GetColor(255, 255, 255), "x���W:%d", player->x);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "y���W:%d", player->y);
		DrawFormatString(0, 40, GetColor(255, 255, 255), "����:%d", object->volume);
		DrawFormatString(0, 60, GetColor(255, 255, 255), "�p���l:%d", object->pan);

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
