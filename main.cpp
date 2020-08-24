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

#define INIT_VELOCITY		70.0f	// リアクション跳躍の初速度

// 変数
SCENE_ID sceneID;
int StartTime;		// ゲーム開始までの時間
int GameTime;		// ゲーム終了までの時間
int EndTime;		// ゲーム終了時の時間
int p1Point;		// プレイヤー１の得点
int p2Point;		// プレイヤー２の得点
int p1Result;		// プレイヤー１の結果
int p2Result;		// プレイヤー２の結果
int bonus;			// ボーナス得点
int jumpImage1[4];	// リザルト時のプレイヤー1画像格納用
int winImage1[2];	// リザルト時のプレイヤー1勝利画像格納用
int loseImage1[2];	// リザルト時のプレイヤー1勝利画像格納用
CHARACTER result1;	// リザルト時に呼ぶプレイヤー１の構造
int jumpStopTime;	// リザルト時に頂点で停止させる時間の処理用
int jumpImage2[4];	// リザルト時のプレイヤー2画像格納用
int winImage2[2];	// リザルト時のプレイヤー2勝利画像格納用
int loseImage2[2];	// リザルト時のプレイヤー2勝利画像格納用
CHARACTER result2;	// リザルト時に呼ぶプレイヤー１の構造体

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
	SetFontSize(32);
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
	// 地面情報初期化
	SoilSystemInit();
	// エフェクト情報初期化
	TreasureEffectInit();
	// 変数初期化
	sceneID = SCENE_ID_INIT;
	// リザルト用グラの読み込み
	// プレイヤー1
	LoadDivGraph("image/moleDamage.png", 4, 4, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, jumpImage1, false);
	LoadDivGraph("image/moleWin.png", 2, 2, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, winImage1, false);
	LoadDivGraph("image/moleLose.png", 2, 2, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, loseImage1, false);
	// プレイヤー2
	LoadDivGraph("image/moleDamage.png", 4, 4, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, jumpImage2, false);
	LoadDivGraph("image/moleWin.png", 2, 2, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, winImage2, false);
	LoadDivGraph("image/moleLose.png", 2, 2, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, loseImage2, false);

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
	FadeInit();
	StartTime = 240;
	GameTime = 300;
	EndTime = 60;
	bonus = 0;
	p1Point = 0;
	p2Point = 0;
	sceneID = SCENE_ID_TITLE;

	result1.pos = { 200, SCREEN_SIZE_Y /2 };
	result1.velocity = { 0,0 };
	result2.pos = { SCREEN_SIZE_X - 232, SCREEN_SIZE_Y /2 }; //SCREEN_SIZE_Y - 132 };
	result2.velocity = { 0,0 };
	jumpStopTime = 30;
	p1Result = 0;
	p2Result = 0;
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
	StageDrawInit();
	SoilDrawInit();
}


void GameScene(void)
{
	if (keyNew[KEY_ID_SPACE] || EndTime <= 0)
	{
		p1Point = 15;
		p2Point = 10;
		bonus = 20;

		if (FadeOutScreen(5) >= 255)
		{
			// ゲーム終了確定時に敵討伐数ボーナスを加算
			if (bonus >= 10)
			{
				p1Point += bonus / 10;
			}
			// 終了時にジャンプの初速度を追加
			result1.velocity.y = INIT_VELOCITY;
			result2.velocity.y = INIT_VELOCITY;

			FadeInit();
			sceneID = SCENE_ID_GAMEOVER;
		}
	}

	if (StartTime > 0)
	{
		StartTime--;
	}
	else
	{
		if (GameTime >= 0)
		{
			GameTime--;
			//GameDraw();
			PlayerControl();
			PlayerControl2();
			ItemControl();
			//effectControl();
			if (WarmHitPoint())
			{
				bonus++;
			}
			p1Point += PlayerScere();
			p2Point += PlayerScere2();
		}
		else
		{
			EndTime--;
		}
	}
		GameDraw();

}

void GameDraw(void)
{
	//DrawFormatString(0, 0,GetColor(255, 255, 255), "GameCounter = %d", gameCounter);


	StageDrawInit();
	TreasureDraw();
	SoilDrawInit();
	TreasureEffectDraw();
	ItemDrawInit();
	PlayerGameDraw();
	PlayerGameDraw2();
	//DrawFormatString(500, 0, GetColor(255, 255, 255), "%d,%d", mapPos.x,mapPos.y);
	//DrawFormatString(0, 300, GetColor(255, 255, 0), "bonus:%d",bonus );
	//DrawFormatString(0, 316, GetColor(255, 255, 0), "p1Point:%d", p1Point);
	//DrawFormatString(0, 332, GetColor(255, 255, 0), "p2Point:%d", p2Point);
	//DrawFormatString(0, 348, GetColor(255, 255, 0), "start:%d", StartTime/60);
	if (GameTime/60 <= 10)
	{
		DrawFormatString(SCREEN_SIZE_X / 2 - 32, 32, GetColor(255, 0, 0), "%d", GameTime / 60);
	}
	else
	{
		DrawFormatString(SCREEN_SIZE_X / 2 - 32, 32, GetColor(0, 0, 0), "%d", GameTime / 60);
	}

	if (GameTime <= 0)
	{
		DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, GetColor(255, 255, 255), "タイムアップ！");
	}
}

void GameOverScene(void)
{
	XY jumpPosCopy = {0,0};
	if (FadeInScreen(5) >= 0)
	{
		if (keyDownTrigger[KEY_ID_SPACE] && FadeInScreen(5) >= 255)
		{
			InitScene();
			sceneID = SCENE_ID_TITLE;
		}
		//bonus = 0;

	// 得点ゲージの増加処理
		if (p1Point > 0)
		{
			p1Point--;
			p1Result += 10;
		}
		if (p2Point > 0)
		{
			p2Point--;
			p2Result += 10;
		}
		//if (result1.pos.y+10 > SCREEN_SIZE_Y - 100 - p1Result)

		// リザルトのプレイヤーアニメーション処理
		// プレイヤー1の処理
		if (result1.velocity.y != 0 || jumpStopTime < 0)
		{
			// 速度の変更
			result1.velocity.y -= ACC_G * FRAME_TIME;
			// 移動距離の追加
			result1.pos.y -= result1.velocity.y * FRAME_TIME;
		}
		else
		{
			jumpStopTime--;
		}
		// ジャンプを止めゲージに乗せる処理
		if (result1.pos.y >= SCREEN_SIZE_Y - 100 - p1Result - 32)
		{
			//jumpStopFlag = true;
			result1.pos.y = SCREEN_SIZE_Y - 100 - p1Result - 32;
		}
		// プレイヤー2の処理
		if (result2.velocity.y != 0 || jumpStopTime < 0)
		{
				// 速度の変更
				result2.velocity.y -= ACC_G * FRAME_TIME;
				// 移動距離の追加
				result2.pos.y -= result2.velocity.y * FRAME_TIME;
			//}
		}
		// ジャンプを止めゲージに乗せる処理
		if (result2.pos.y >= SCREEN_SIZE_Y - 100 - p2Result - 32)
		{
			result2.pos.y = SCREEN_SIZE_Y - 100 - p2Result - 32;
		}
		GameOverDraw();
	}
}

void GameOverDraw(void)
{
	result1.AnimCnt++;
	result2.AnimCnt++;

	StageDrawInit();
	SoilDrawInit();

	DrawBox(100, 100, SCREEN_SIZE_X - 100, SCREEN_SIZE_Y - 100, GetColor(0, 255, 255), true);
	//SetDrawBright(100, 100, 100);
	DrawFormatString(0, 316, GetColor(255, 255, 0), "p1Point:%d", p1Point);
	DrawFormatString(0, 348, GetColor(255, 255, 0), "p2Point:%d", p2Point);
	DrawFormatString(0, 380, GetColor(255, 255, 0), "bonus:%d", bonus);
	DrawFormatString(0, 422, GetColor(255, 255, 0), "total:%d", p1Point + bonus / 10);

	// 着地時に画像を変更する
	// プレイヤー1の画像
	if (result1.pos.y <= SCREEN_SIZE_Y - 100 - p1Result)
	{
		if (result1.pos.y >= SCREEN_SIZE_Y - 100 - p1Result - 32)
		{
			if (p1Result > p2Result)
			{
				DrawGraph(result1.pos.x, result1.pos.y, winImage1[(result1.AnimCnt / 15) % 2], true);
			}
			else
			{
				DrawGraph(result1.pos.x, result1.pos.y, loseImage1[(result1.AnimCnt / 15) % 2], true);
			}
		}
		else
		{
			DrawGraph(result1.pos.x, result1.pos.y, jumpImage1[(result1.AnimCnt / 5) % 4], true);
		}
	}
	// プレイヤー2の画像
	if (result2.pos.y <= SCREEN_SIZE_Y - 100 - p2Result)
	{
		if (result2.pos.y >= SCREEN_SIZE_Y - 100 - p2Result - 32)
		{
			if (p2Result > p1Result)
			{
				DrawGraph(result2.pos.x, result2.pos.y, winImage2[(result2.AnimCnt / 15) % 2], true);
			}
			else
			{
				DrawGraph(result2.pos.x, result2.pos.y, loseImage2[(result2.AnimCnt / 15) % 2], true);
			}
		}
		else
		{
			DrawGraph(result2.pos.x, result2.pos.y, jumpImage2[(result2.AnimCnt / 5) % 4], true);
		}
	}

	// 得点のゲージの表示
	// プレイヤー1のゲージ
	DrawBox(200, SCREEN_SIZE_Y - 132, 200+32, SCREEN_SIZE_Y - 100 - p1Result, GetColor(0, 255, 0), true);
	// プレイヤー2のゲージ
	DrawBox(SCREEN_SIZE_X - 200, SCREEN_SIZE_Y - 132, SCREEN_SIZE_X - 200 - 32, SCREEN_SIZE_Y - 100 - p2Result, GetColor(0, 255, 0), true);
	//DrawBox(182 + 32, SCREEN_SIZE_Y - 100,182+ 64, SCREEN_SIZE_Y - 100 - p2Point, GetColor(255, 255, 255), true);
}