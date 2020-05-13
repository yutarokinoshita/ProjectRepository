//-----------------------------
// TestProject
//	 by Kinosita
//-----------------------------
#include "DxLib.h"		// DxLibライブラリを使用する
#include "main.h"
#include "map.h"
#include "player.h"
// 変数
int gameCounter;

// プロトタイプ宣言
void GameMain(void);
void GameDraw(void);



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

// WinMain関数
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//----------システム処理
	SetWindowText("TestProject");
	// システム処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	// グラフィックの登録

	// 変数初期化
	gameCounter = 0;
	PlayerSystemInit();

	// ｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();

		// メイン処理
		GameMain();
		gameCounter++;

		ScreenFlip();
	}
	DxLib_End();	// DXﾗｲﾌﾞﾗﾘの終了処理
	return 0;	// このﾌﾟﾛｸﾞﾗﾑの終了
}

