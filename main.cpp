#include "DxLib.h"
#include "Player.h"
#include "Object.h"
#include "Scroll.h"
#include "Mapchip.h"
#include <math.h>

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "xx2x_xx_ナマエ: タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 960;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	int mokugyoSound = LoadSoundMem("mokugyo.wav");
	int mokugyoSound2 = LoadSoundMem("mokugyo.wav");
	int fanfareSound = LoadSoundMem("fanfare.wav");

	// ゲームループで使う変数の宣言
	//プレイヤーについて
	Player* player = new Player(WIN_WIDTH / 2, WIN_HEIGHT / 2, 16);

	//オブジェクトについて		//X座用,Y座標,半径,音
	Object* object1 = new Object(   0,    0, 32, mokugyoSound);
	Object* object2 = new Object(-500,  1000, 32, mokugyoSound2);
	Object* object3 = new Object( 500, -500, 32, fanfareSound);


	// 最新のキーボード情報用
	char keys[256] = {0};

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = {0};

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理 
		//プレイヤーの移動
		player->Move();

		//オブジェクトの音を鳴らす
		object1->Sound(*player);
		object2->Sound(*player);
		object3->Sound(*player);

		// 描画処理
		for (int i = -20; i <= 20; i++)
		{
			DrawLine(i * blockSize - object1->scroll->x, -1280 - object1->scroll->y,
					 i * blockSize - object1->scroll->x, 1280 - object1->scroll->y, GetColor(100, 100, 100));
			DrawLine(-1280 - object1->scroll->x, i * blockSize - object1->scroll->y,
					 1280 - object1->scroll->x, i * blockSize - object1->scroll->y, GetColor(100, 100, 100));
		}
		 
		//プレイヤーの描画
		player->Draw();

		//オブジェクトの描画
		object1->Draw();
		object2->Draw();
		object3->Draw();

		////マップの描画
		//for (int i = 0; i < 20; i++) {
		//	for (int j = 0; j < 20; j++) {
		//		if (map[i][j] == 1) {
		//			DrawBox(blockSize * i - object->scroll->x, blockSize * j - object->scroll->y, 
		//				blockSize * i + blockSize - object->scroll->x, blockSize * j + blockSize - object->scroll->y,
		//				GetColor(0, 255, 0), true);
		//		}
		//	}
		//}

		DrawFormatString(0, 0, GetColor(255, 255, 255), "x座標:%d", player->x);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "y座標:%d", player->y);
		DrawFormatString(0, 40, GetColor(255, 255, 255), "音量:%d", object1->volume);
		DrawFormatString(0, 60, GetColor(255, 255, 255), "パン値:%d", object1->pan);

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
