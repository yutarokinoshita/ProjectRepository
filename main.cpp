//-----------------------------
// TestProject
//	 by Kinosita
//-----------------------------
#include "DxLib.h"		// DxLibライブラリを使用する
#include "main.h"
#include "map.h"
#include "player.h"
<<<<<<< HEAD
#include "keycheck.h"

=======
>>>>>>> e928399d299ad8e6ff2c5fbc3299ecb37a63f41d
// 変数
int gameCounter;

// プロトタイプ宣言
void GameMain(void);
void GameDraw(void);

<<<<<<< HEAD
=======


void GameDraw(void)
{
	DrawFormatString(0, 0,GetColor(255, 255, 255), "GameCounter = %d", gameCounter);
	StageDrawInit();
}

void GameMain(void)
{
	GameDraw();
	PlayerDrawInit();
}

>>>>>>> e928399d299ad8e6ff2c5fbc3299ecb37a63f41d
// WinMain関数
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//----------システム処理
<<<<<<< HEAD
	SetWindowText("採掘畑");
=======
	SetWindowText("TestProject");
>>>>>>> e928399d299ad8e6ff2c5fbc3299ecb37a63f41d
	// システム処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	// グラフィックの登録

	// 変数初期化
	gameCounter = 0;
	PlayerSystemInit();
<<<<<<< HEAD
	keyInit();
=======
>>>>>>> e928399d299ad8e6ff2c5fbc3299ecb37a63f41d

	// ｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();

		// メイン処理
<<<<<<< HEAD
		keyCheck();
=======
>>>>>>> e928399d299ad8e6ff2c5fbc3299ecb37a63f41d
		GameMain();
		gameCounter++;

		ScreenFlip();
	}
	DxLib_End();	// DXﾗｲﾌﾞﾗﾘの終了処理
	return 0;	// このﾌﾟﾛｸﾞﾗﾑの終了
}

<<<<<<< HEAD
void GameDraw(void)
{
	DrawFormatString(0, 0,GetColor(255, 255, 255), "GameCounter = %d", gameCounter);


	StageDrawInit();
	PlayerDrawInit();
}
void GameMain(void)
{
	GameDraw();
	PlayerControl();
}
=======
>>>>>>> e928399d299ad8e6ff2c5fbc3299ecb37a63f41d
