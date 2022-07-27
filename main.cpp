#include "DxLib.h"
#include "Player.h"
#include "Object.h"
#include "Scroll.h"
#include "Astar.h"
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

	int goalCountTmp = 0;

	// 画像などのリソースデータの変数宣言と読み込み
	int mokugyoSound = LoadSoundMem("mokugyo.wav");
	int mokugyoSound2 = LoadSoundMem("mokugyo.wav");
	int fanfareSound = LoadSoundMem("fanfare.wav");

	// ゲームループで使う変数の宣言
	//プレイヤーについて
	Player* player = new Player(WIN_WIDTH / 2 + BlockSize / 2, WIN_HEIGHT / 2 + BlockSize / 2, 16);

	//オブジェクトについて
	Object* object1 = new Object(BlockSize * 3 + BlockSize / 2, BlockSize * 4 + BlockSize / 2, 32, mokugyoSound);
	//Object* object2 = new Object(BlockSize * 10 + BlockSize / 2, BlockSize * 10 + BlockSize / 2, 32, fanfareSound);;
	//Object* object3 = new Object( 500, -500, 32, fanfareSound);

	Cell start = Cell(player->x / BlockSize, player->y / BlockSize);
	Cell goal = Cell(object1->x / BlockSize, object1->y / BlockSize);
	CreateMap();
	AStar(start, goal, *object1);


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

		for (int i = 0; i < MapHeight; i++)
		{
			if (player->y == BlockSize * i || player->x == BlockSize * i)
			{
				start = Cell(player->x / BlockSize, player->y / BlockSize);
				goal = Cell(object1->x / BlockSize, object1->y / BlockSize);
				
				AStar(start, goal, *object1);
			}
		}
	
		//オブジェクトの音を鳴らす
		object1->Sound(*player);
		//object2->Sound(*player);
		//object3->Sound(*player);

		// 描画処理
		for (int i = 0; i <= MapHeight - 1; i++)
		{
			DrawLine(i * BlockSize - object1->scroll->x,-object1->scroll->y,
					 i * BlockSize - object1->scroll->x, MapHeight * BlockSize - object1->scroll->y, GetColor(100, 100, 100));
			DrawLine(-object1->scroll->x, i * BlockSize - object1->scroll->y,
				MapWidth * BlockSize - object1->scroll->x, i * BlockSize - object1->scroll->y, GetColor(100, 100, 100));

			for (int j = 0; j <= MapWidth - 1; j++)
			{
				if (CostTable[j][i] == 0)
				{
					DrawBox(i * BlockSize - object1->scroll->x, j * BlockSize - object1->scroll->y,
						i * BlockSize - object1->scroll->x + BlockSize, j * BlockSize - object1->scroll->y + BlockSize,
						GetColor(255, 0, 255), true);
				}
			}
		}
		 
		//プレイヤーの描画
		player->Draw();

		//オブジェクトの描画
		object1->Draw();
		//object2->Draw();
		//object3->Draw();

		/*DrawFormatString(0, 0, GetColor(255, 255, 255), "x座標:%d", player->x);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "y座標:%d", player->y);
		DrawFormatString(0, 40, GetColor(255, 255, 255), "音量:%d", object1->volume);
		DrawFormatString(0, 60, GetColor(255, 255, 255), "パン値:%d", object1->pan);*/

		AStarDraw(start, goal, *object1);
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
