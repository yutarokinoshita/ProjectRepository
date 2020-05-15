#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "keycheck.h"
#include "playerAction.h"

#define dashStart	16	// ダッシュを始めるまでの時間

CHARACTER player1;	//プレイヤー１の構造体
int playerImage;
bool turnFlag;		// 振り向き制御用
int dashCnt;		// ダッシュを始めるまで
bool digFlag;		// 採掘可能か否か

void PlayerSystemInit(void)
{
	playerImage = LoadGraph("image/mole.png");
	player1.pos.x = 16;
	player1.pos.y = 16;
	player1.size.x = PLAYER_SIZE_X;
	player1.size.y = PLAYER_SIZE_Y;
	player1.sizeOffset.x = player1.size.x / 2;
	player1.sizeOffset.y = player1.size.y / 2;
	player1.moveDir = DIR_DOWN;
	player1.oldmoveDir = player1.moveDir;
	player1.moveSpeed = 32;
	turnFlag = false;
	dashCnt = 0;
	digFlag = false;
}

void PlayerDrawInit(void)
{
	// 仮置きのプレイヤー
	//if (player1.moveDir == DIR_DOWN)
	//{
	//	DrawBox(player1.pos.x, player1.pos.y, player1.pos.x + 32, player1.pos.y + 32, GetColor(255, 0, 0), true);
	//}
	//if (player1.moveDir == DIR_RIGHT)
	//{
	//	DrawBox(player1.pos.x, player1.pos.y, player1.pos.x + 32, player1.pos.y + 32, GetColor(0, 255, 255), true);
	//}
	//if (player1.moveDir == DIR_UP)
	//{
	//	DrawBox(player1.pos.x, player1.pos.y, player1.pos.x + 32, player1.pos.y + 32, GetColor(0, 0, 255), true);
	//}
	//if (player1.moveDir == DIR_LEFT)
	//{
	//	DrawBox(player1.pos.x, player1.pos.y, player1.pos.x + 32, player1.pos.y + 32, GetColor(255, 255, 255), true);
	//}
	DrawGraph(player1.pos.x - player1.sizeOffset.x, player1.pos.y - player1.sizeOffset.y, playerImage, true);
	DrawFormatString(0, 16, GetColor(255, 0, 0), "%d,%d", player1.pos.x, player1.pos.y);
	DrawFormatString(0, 32, GetColor(255, 0, 0), "%d", player1.moveDir);
}

void PlayerControl(void)
{
	bool moveFlag = false;
	digFlag = false;

	if (keyNew[KEY_ID_P1DOWN])
	{
		player1.moveDir = DIR_DOWN;
		// 向きが変わった場合ダッシュをやめる
		if (player1.moveDir == player1.oldmoveDir)
		{
			moveFlag = true;
		}
		else
		{
			dashCnt = 0;
		}
	}
	if (keyNew[KEY_ID_P1RIGHT])
	{
		player1.moveDir = DIR_RIGHT;
		if (player1.moveDir == player1.oldmoveDir)
		{
			moveFlag = true;
		}
		else
		{
			dashCnt = 0;
		}
	}
	if (keyNew[KEY_ID_P1UP])
	{
		player1.moveDir = DIR_UP;
		if (player1.moveDir == player1.oldmoveDir)
		{
			moveFlag = true;
		}
		else
		{
			dashCnt = 0;
		}
	}
	if (keyNew[KEY_ID_P1LEFT])
	{
		player1.moveDir = DIR_LEFT;
		if (player1.moveDir == player1.oldmoveDir)
		{
			moveFlag = true;
		}
		else
		{
			dashCnt = 0;
		}
	}


	if (moveFlag)
	{
		switch (player1.moveDir)
		{
		case DIR_DOWN:
			dashCnt++;
			if (dashCnt <= dashStart)
			{
				player1.pos.y += player1.moveSpeed;
			}
			else
			{
				player1.pos.y += player1.moveSpeed * 2;
			}
			break;
		case DIR_RIGHT:
			dashCnt++;
			if (dashCnt <= dashStart)
			{
				player1.pos.x += player1.moveSpeed;
			}
			else
			{
				player1.pos.x += player1.moveSpeed * 2;
			}
			break;
		case DIR_UP:
			dashCnt++;
			if (dashCnt <= dashStart)
			{
				player1.pos.y -= player1.moveSpeed;
			}
			else
			{
				player1.pos.y -= player1.moveSpeed * 2;
			}
			break;
		case DIR_LEFT:
			dashCnt++;
			if (dashCnt <= dashStart)
			{
				player1.pos.x -= player1.moveSpeed;
			}
			else
			{
				player1.pos.x -= player1.moveSpeed * 2;
			}
			break;
		default:
			break;
		}
	}

	// 現在の向きを記録
	player1.oldmoveDir = player1.moveDir;

	// ボタンを離したときダッシュを止める
	if (keyUpTrigger[KEY_ID_P1DOWN]|| keyUpTrigger[KEY_ID_P1RIGHT]|| keyUpTrigger[KEY_ID_P1UP]|| keyUpTrigger[KEY_ID_P1LEFT])
	{
		dashCnt = 0;
	}
	// 移動していないとき採掘ができる
	if (!keyNew[KEY_ID_P1DOWN] && !keyNew[KEY_ID_P1RIGHT] && !keyNew[KEY_ID_P1UP] && !keyNew[KEY_ID_P1LEFT])
	{
		digFlag = true;
	}

	if (keyDownTrigger[KEY_ID_PLAYER_ACTION] && digFlag)
	{
		CliateDig(player1.pos, player1.moveDir);
	}

}