//-----------------------------
// TestProject
//	 by Kinosita
//-----------------------------
#include <DxLib.h>		// DxLibライブラリを使用する
#include <stdio.h>		// ファイル操作に使用するヘッダー
#include <string.h>		// 文字列操作に使用するヘッダー
#include "main.h"
#include "map.h"
#include "player.h"
#include "player2.h"
#include "keycheck.h"
#include "playerAction.h"
#include "treasure.h"
#include "soil.h"
#include "effect.h"
#include "string.h"

#define INIT_VELOCITY		70.0f	// リアクション跳躍の初速度

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
<<<<<<< HEAD
int jumpStopTime1;	// リザルト時にプレイヤー1を頂点で停止させる時間の処理用
int jumpStopTime2;	// リザルト時にプレイヤー2頂点で停止させる時間の処理用
=======
int jumpStopTime;	// リザルト時に頂点で停止させる時間の処理用
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
int jumpImage2[4];	// リザルト時のプレイヤー2画像格納用
int winImage2[2];	// リザルト時のプレイヤー2勝利画像格納用
int loseImage2[2];	// リザルト時のプレイヤー2勝利画像格納用
CHARACTER result2;	// リザルト時に呼ぶプレイヤー１の構造体
<<<<<<< HEAD
int HiScore;		// ハイスコア
bool newScoreFlag;	// ハイスコアが更新された際に使用
int titleImage;		// タイトル画像格納用
int startImage;		// スタート画像格納用
bool stopFlag;		// ゲームを一時停止させるためのフラグ
bool p1ResultEnd;	// プレイヤー1のリザルト終了フラグ
bool p2ResultEnd;	// プレイヤー2のリザルト終了フラグ
int namedTime;		// 称号が表示されるまでの時間
=======
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1

// プロトタイプ宣言

// WinMain関数
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	if (!SystemInit())
	{
		return 0;
	}

	// ハイスコアのロード
	HiScoreLoad();
	
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
	EffectInit();
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

	// リザルト用グラの読み込み
	// プレイヤー1
	LoadDivGraph("image/moleDamage.png", 4, 4, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, jumpImage1, false);
	LoadDivGraph("image/moleWin.png", 2, 2, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, winImage1, false);
	LoadDivGraph("image/moleLose.png", 2, 2, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, loseImage1, false);
	// プレイヤー2
	LoadDivGraph("image/ratDamage.png", 4, 4, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, jumpImage2, false);
	LoadDivGraph("image/ratWin.png", 2, 2, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, winImage2, false);
	LoadDivGraph("image/ratLose.png", 2, 2, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, loseImage2, false);
	// タイトル読み込み
	titleImage = LoadGraph("image/titlelogo.png");
	startImage = LoadGraph("image/startbutton.png");
	// 称号初期化
	StringInit();

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
<<<<<<< HEAD
	EffectGameInit();
	StringGameInit();
	FadeInit();
	StartTime = 240;
	GameTime = 720;
=======
	TreasureEffectGameInit();
	FadeInit();
	StartTime = 240;
	GameTime = 300;
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
	EndTime = 60;
	bonus = 0;
	p1Point = 0;
	p2Point = 0;
	sceneID = SCENE_ID_TITLE;

	result1.pos = { 200, SCREEN_SIZE_Y /2 };
	result1.velocity = { 0,0 };
	result2.pos = { SCREEN_SIZE_X - 232, SCREEN_SIZE_Y /2 }; //SCREEN_SIZE_Y - 132 };
	result2.velocity = { 0,0 };
<<<<<<< HEAD
	jumpStopTime1 = 0;
	jumpStopTime2 = 0;
	p1Result = 0;
	p2Result = 0;
	p1ResultEnd = false;
	p2ResultEnd = false;

	newScoreFlag = false;
	stopFlag = false;
	namedTime = 0;
=======
	jumpStopTime = 30;
	p1Result = 0;
	p2Result = 0;
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
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

	DrawGraph((SCREEN_SIZE_X - 464) / 2, SCREEN_SIZE_Y  / 2- 148, titleImage, true);
	DrawGraph((SCREEN_SIZE_X - 456) / 2, (SCREEN_SIZE_Y + 128) / 2, startImage, true);
	DrawFormatString(SCREEN_SIZE_X / 2-128, 448, GetColor(255, 255, 255), "ハイスコア %d", HiScore);
}


void GameScene(void)
{
<<<<<<< HEAD
	stopFlag = false;
	if (keyNew[KEY_ID_SPACE] || EndTime <= 0)
	{
		// デバッグ用スコア
		p1Point = 15;
		p2Point = 10;
		//bonus = 20;

		if (FadeOutScreen(5) >= 255)
		{
			// リザルトで表示する称号を選択する
			StringResult(p1Point, bonus, p2Point);
			// ゲーム終了確定時に敵討伐数ボーナスを加算
			if (bonus >= 10)
			{
				p1Point += bonus / 5;
=======
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
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
			}
			// 終了時にジャンプの初速度を追加
			result1.velocity.y = INIT_VELOCITY;
			result2.velocity.y = INIT_VELOCITY;
<<<<<<< HEAD
			// 得点に応じた停止時間を与える
			jumpStopTime1 = p1Point * 3;
			jumpStopTime2 = p2Point * 3;

			mapPos = { 0,0 };
			// ハイスコアが出た場合更新する
			if (HiScore < p1Point)
			{
				HiScore = p1Point;

				HiScoreSave();

				newScoreFlag = true;
			}
=======
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1

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
			PlayerControl();
			// 停止処理が行われた際プレイヤー以外を止める
			if (!stopFlag)
			{
				GameTime--;
				//GameDraw();
				PlayerControl2();
				ItemControl();
				//effectControl();
				if (WarmHitPoint())
				{
					bonus++;
				}
				p1Point += PlayerScere();
				p2Point += PlayerScere2();
				EffectControl();
			}
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
	ItemDrawInit();
	if (!stopFlag)
	{
		PlayerGameDraw();
	}
	PlayerGameDraw2();
<<<<<<< HEAD
	EffectDraw();
	if (stopFlag)
	{
		PlayerGameDraw();
	}

	if ((GameTime+60)/60 <= 10)
	{
		DrawFormatString(SCREEN_SIZE_X / 2 - 32, 32, GetColor(255, 0, 0), "%d", (GameTime+60) / 60);
	}
	else
	{
		DrawFormatString(SCREEN_SIZE_X / 2 - 32, 32, GetColor(255, 128, 128), "%d", (GameTime+60) / 60);
=======
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
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
	}

	if (GameTime <= 0)
	{
		DrawFormatString(SCREEN_SIZE_X / 2- 96, SCREEN_SIZE_Y / 2 , GetColor(255, 255, 255), "タイムアップ！");
	}
	if (StartTime > 0)
	{
		if (StartTime >= 60)
		{
			DrawFormatString(SCREEN_SIZE_X / 2-32, SCREEN_SIZE_Y / 2, GetColor(255, 255, 255), "%d", StartTime / 60);
		}
		else
		{
			DrawFormatString(SCREEN_SIZE_X / 2 - 32, SCREEN_SIZE_Y / 2, GetColor(255, 255, 255), "GO!");
		}
	}

	// 以下デバッグ用表示
	DrawFormatString(500, 0, GetColor(255, 255, 255), "%d,%d", mapPos.x,mapPos.y);
	DrawFormatString(0, 300, GetColor(0, 255, 0), "bonus:%d",bonus );
	DrawFormatString(0, 332, GetColor(0,255, 0), "p1Point:%d", p1Point);
	DrawFormatString(0, 364, GetColor(0,255, 0), "p2Point:%d", p2Point);
	DrawFormatString(0, 396, GetColor(0, 255, 0), "start:%d", StartTime/60);
}

void GameOverScene(void)
{
<<<<<<< HEAD
	//XY jumpPosCopy = {0,0};
	if (FadeInScreen(5) >= 0)
	{
		if (p1ResultEnd && p2ResultEnd)
		{
			if (keyDownTrigger[KEY_ID_SPACE] && FadeInScreen(5) >= 255)
			{
				InitScene();
				sceneID = SCENE_ID_TITLE;
			}
=======
	XY jumpPosCopy = {0,0};
	if (FadeInScreen(5) >= 0)
	{
		if (keyDownTrigger[KEY_ID_SPACE] && FadeInScreen(5) >= 255)
		{
			InitScene();
			sceneID = SCENE_ID_TITLE;
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
		}
		//bonus = 0;

	// 得点ゲージの増加処理
		if (p1Point > 0)
		{
<<<<<<< HEAD
			if (result1.AnimCnt % 3 == 0 && result1.velocity.y == 0)
			{
				p1Point--;
				p1Result += 10;
			}
		}
		if (p2Point > 0)
		{
			if (result2.AnimCnt % 3 == 0 && result2.velocity.y == 0)
			{
				p2Point--;
				p2Result += 10;
			}
=======
			p1Point--;
			p1Result += 10;
		}
		if (p2Point > 0)
		{
			p2Point--;
			p2Result += 10;
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
		}
		//if (result1.pos.y+10 > SCREEN_SIZE_Y - 100 - p1Result)

		// リザルトのプレイヤーアニメーション処理
		// プレイヤー1の処理
<<<<<<< HEAD
		if (result1.velocity.y != 0 || jumpStopTime1 < 0)
		{
			// 速度の変更
			result1.velocity.y -= ACC_G * FRAME_TIME;
			//if (p1Point > 0)
			//{
			//	if (result1.velocity.y == 0)
			//	{
			//		result1.velocity.y = 0;
			//	}
			//}
=======
		if (result1.velocity.y != 0 || jumpStopTime < 0)
		{
			// 速度の変更
			result1.velocity.y -= ACC_G * FRAME_TIME;
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
			// 移動距離の追加
			result1.pos.y -= result1.velocity.y * FRAME_TIME;
		}
		else
		{
<<<<<<< HEAD
			jumpStopTime1--;
		}
		// ジャンプを止めゲージに乗せる処理
		if (result1.pos.y >= SCREEN_SIZE_Y - 132 - p1Result - 32)
		{
			//jumpStopFlag = true;
			result1.pos.y = SCREEN_SIZE_Y - 132 - p1Result - 32;
			p1ResultEnd = true;
		}
		// プレイヤー2の処理
		if (result2.velocity.y != 0 || jumpStopTime2 < 0)
		{
			// 速度の変更
			result2.velocity.y -= ACC_G * FRAME_TIME;
			// 移動距離の追加
			result2.pos.y -= result2.velocity.y * FRAME_TIME;
			//}
		}
		else
		{
			jumpStopTime2--;
		}
		// ジャンプを止めゲージに乗せる処理
		if (result2.pos.y >= SCREEN_SIZE_Y - 132 - p2Result - 32)
		{
			result2.pos.y = SCREEN_SIZE_Y - 132 - p2Result - 32;
			p2ResultEnd = true;
		}
		GameOverDraw();
		if (p1ResultEnd && p2ResultEnd)
		{
			StringDraw();
		}
=======
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
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
	}
}

void GameOverDraw(void)
{
	result1.AnimCnt++;
	result2.AnimCnt++;

	StageDrawInit();
	SoilDrawInit();

<<<<<<< HEAD
	DrawBox(100, 100, SCREEN_SIZE_X - 100, SCREEN_SIZE_Y - 100, GetColor(255, 255, 255), true);
=======
	DrawBox(100, 100, SCREEN_SIZE_X - 100, SCREEN_SIZE_Y - 100, GetColor(0, 255, 255), true);
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
	//SetDrawBright(100, 100, 100);
	DrawFormatString(0, 316, GetColor(255, 255, 0), "p1Point:%d", p1Point);
	DrawFormatString(0, 348, GetColor(255, 255, 0), "p2Point:%d", p2Point);
	DrawFormatString(0, 380, GetColor(255, 255, 0), "bonus:%d", bonus);
	DrawFormatString(0, 422, GetColor(255, 255, 0), "total:%d", p1Point + bonus / 10);
<<<<<<< HEAD
	// 得点の描画
	DrawFormatString(200, SCREEN_SIZE_Y - 132, GetColor(0, 0, 0), "%2d", p1Result / 10);
	DrawFormatString(SCREEN_SIZE_X - 232, SCREEN_SIZE_Y - 132, GetColor(0, 0, 0), "%2d", p2Result / 10);
	DrawFormatString(SCREEN_SIZE_X/2, 200, GetColor(0, 0, 0), "YOU WIN");

	// 着地時に画像を変更する
	// プレイヤー1の画像
	if (result1.pos.y <= SCREEN_SIZE_Y - 132 - p1Result)
	{
		if (result1.pos.y >= SCREEN_SIZE_Y - 132 - p1Result - 32)
=======

	// 着地時に画像を変更する
	// プレイヤー1の画像
	if (result1.pos.y <= SCREEN_SIZE_Y - 100 - p1Result)
	{
		if (result1.pos.y >= SCREEN_SIZE_Y - 100 - p1Result - 32)
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
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
<<<<<<< HEAD
	if (result2.pos.y <= SCREEN_SIZE_Y - 132 - p2Result)
	{
		if (result2.pos.y >= SCREEN_SIZE_Y - 132 - p2Result - 32)
=======
	if (result2.pos.y <= SCREEN_SIZE_Y - 100 - p2Result)
	{
		if (result2.pos.y >= SCREEN_SIZE_Y - 100 - p2Result - 32)
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
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
<<<<<<< HEAD
	DrawBox(200, SCREEN_SIZE_Y - 132, 200+32, SCREEN_SIZE_Y - 132 - p1Result, GetColor(0, 128, 0), true);
	// プレイヤー2のゲージ
	DrawBox(SCREEN_SIZE_X - 200 - 32, SCREEN_SIZE_Y - 132, SCREEN_SIZE_X - 200, SCREEN_SIZE_Y - 132 - p2Result, GetColor(0, 0, 128), true);
	//DrawBox(182 + 32, SCREEN_SIZE_Y - 100,182+ 64, SCREEN_SIZE_Y - 100 - p2Point, GetColor(255, 255, 255), true);
}

void HiScoreSave()
{
	FILE *fp;

	// ハイスコア用ファイルを開く
	fp = fopen("HiScore.dat", "wb");

	// 開けない場合ここで終了
	if (fp == NULL) return;

	// ハイスコアの書き出し
	fwrite(&HiScore, sizeof(HiScore), 1, fp);

	// ファイルを閉じる
	fclose(fp);
}

void HiScoreLoad()
{

	FILE* fp;

	// ハイスコア用ファイルを開く
	fp = fopen("HiScore.dat", "rb");

	// 開けない場合仮の数値をセット
	if (fp == NULL)
	{
		HiScore = 15;
	}
	else
	{
		// ファイル読み込み
		fread(&HiScore, sizeof(HiScore), 1, fp);

		// ファイルを閉じる
		fclose(fp);
	}
}

// 呼び出し中はゲームを一時停止させる
void GameStop()
{
	stopFlag = true;
=======
	DrawBox(200, SCREEN_SIZE_Y - 132, 200+32, SCREEN_SIZE_Y - 100 - p1Result, GetColor(0, 255, 0), true);
	// プレイヤー2のゲージ
	DrawBox(SCREEN_SIZE_X - 200, SCREEN_SIZE_Y - 132, SCREEN_SIZE_X - 200 - 32, SCREEN_SIZE_Y - 100 - p2Result, GetColor(0, 255, 0), true);
	//DrawBox(182 + 32, SCREEN_SIZE_Y - 100,182+ 64, SCREEN_SIZE_Y - 100 - p2Point, GetColor(255, 255, 255), true);
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
}