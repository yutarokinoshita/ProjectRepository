//-----------------------------
// TestProject
//	 by Kinosita
//-----------------------------
#include "DxLib.h"		// DxLibライブラリを使用する
#include "main.h"
#include "map.h"
#include "player.h"
#include "player2.h"
#include "keycheck.h"
#include "playerAction.h"
#include "treasure.h"
#include "soil.h"
#include "effect.h"

// 変数
SCENE_ID sceneID;
int StartTime;		// ゲーム開始までの時間

// プロトタイプ宣言

// WinMain関数
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	if (!SystemInit())
	{
		return 0;
	}

	// ｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		keyCheck();
		ClsDrawScreen();
		// メイン処理
		switch (sceneID)
		{
		case SCENE_ID_INIT:
			InitScene();
			sceneID = SCENE_ID_TITLE;
			break;
		case SCENE_ID_TITLE:
			TitleScene();
			break;
		case SCENE_ID_GAME:
			GameScene();
			break;
		case SCENE_ID_GAMEOVER:
			GameOverScene();
			break;
		case SCENE_ID_MAX:
			break;
		default:
			break;
		}



		ScreenFlip();
	}
	DxLib_End();	// DXﾗｲﾌﾞﾗﾘの終了処理
	return 0;	// このﾌﾟﾛｸﾞﾗﾑの終了
}

bool SystemInit(void)
{
	//----------システム処理
	SetWindowText("採掘畑");
	// システム処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	// キーの追加
	keyInit();
	// グラフィックの登録
	// ステージ情報初期化
	StageSystemInit();
	// プレイヤー情報初期化
	PlayerSystemInit();
	PlayerSystemInit2();
	// アイテム情報初期化
	ItemSystemInit();
	// 得点アイテム情報初期化
	TreasureSystemInit();
	// 地面商法初期化
	SoilSystemInit();
	// エフェクト情報初期化
	TreasureEffectInit();
	// 変数初期化
	sceneID = SCENE_ID_INIT;

	return true;
}

void InitScene(void)
{
	StageGameInit();
	PlayerGameInit();
	PlayerGameInit2();
	ItemGameInit();
	TreasureGameInit();
	SoilGameInit();
	TreasureEffectGameInit();
	StartTime = 2400;
}

void TitleScene(void)
{
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		sceneID = SCENE_ID_GAME;
	}
	TitleDraw();
}

void TitleDraw(void)
{
	DrawBox(100, 100, SCREEN_SIZE_X - 100, SCREEN_SIZE_Y - 100, GetColor(255, 255, 255), true);
}


void GameScene(void)
{
	if (keyDownTrigger[KEY_ID_SPACE] || StartTime <= 0)
	{
		sceneID = SCENE_ID_GAMEOVER;
	}
	StartTime--;
	//GameDraw();
	PlayerControl();
	PlayerControl2();
	ItemControl();
	//effectControl();
	GameDraw();
}

void GameDraw(void)
{
	//DrawFormatString(0, 0,GetColor(255, 255, 255), "GameCounter = %d", gameCounter);


	StageDrawInit();
	SoilDrawInit();
	TreasureDraw();
	TreasureEffectDraw();
	ItemDrawInit();
	PlayerGameDraw();
	PlayerGameDraw2();
	DrawFormatString(500, 0, GetColor(255, 255, 255), "%d,%d", mapPos.x,mapPos.y);
}

void GameOverScene(void)
{
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		InitScene();
		sceneID = SCENE_ID_TITLE;
	}
	GameOverDraw();
}

void GameOverDraw(void)
{
	DrawBox(100, 100, SCREEN_SIZE_X - 100, SCREEN_SIZE_Y - 100, GetColor(0, 255, 255), true);
}