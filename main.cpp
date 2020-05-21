//-----------------------------
// TestProject
//	 by Kinosita
//-----------------------------
#include "DxLib.h"		// DxLibライブラリを使用する
#include "main.h"
#include "map.h"
#include "player.h"
#include "keycheck.h"
#include "playerAction.h"
#include "treasure.h"
#include "soil.h"
//#include "effect.h"

// 変数
int gameCounter;

// プロトタイプ宣言
void GameMain(void);
void GameDraw(void);

// WinMain関数
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//----------システム処理
	SetWindowText("採掘畑");
	// システム処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	// グラフィックの登録

	// 変数初期化
	gameCounter = 0;
	StageInit();
	PlayerSystemInit();
	keyInit();
	ItemSystemInit();
	TreasureInit();
	soilSystemInit();
	//TreasureEffectInit();

	// ｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();

		// メイン処理
		keyCheck();
		GameMain();
		gameCounter++;

		ScreenFlip();
	}
	DxLib_End();	// DXﾗｲﾌﾞﾗﾘの終了処理
	return 0;	// このﾌﾟﾛｸﾞﾗﾑの終了
}

void InitScene(void)
{

}

void GameDraw(void)
{
	DrawFormatString(0, 0,GetColor(255, 255, 255), "GameCounter = %d", gameCounter);


	StageDrawInit();
	soilDrawInit();
	TreasureDraw();
	//TreasureEffectDraw();
	ItemDrawInit();
	PlayerGameDraw();
	DrawFormatString(500, 0, GetColor(255, 255, 255), "%d,%d", mapPos.x,mapPos.y);
}
void GameMain(void)
{
	GameDraw();
	PlayerControl();
	ItemControl();
	//effectControl();

	// デバッグ用　後で消してよし
	if (CheckHitKey(KEY_INPUT_UP))
	{
		mapPos.y++;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		mapPos.y--;
	}
}
