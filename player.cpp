#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "keycheck.h"

#define dashStart	16	// ダッシュを始めるまでの時間

CHARACTER player1;	//プレイヤー１の構造体
bool turnFlag;		// 振り向き制御用
int dashCnt;		// ダッシュを始めるまで

void PlayerSystemInit(void)
{
	player1.pos.x = 200;
	player1.pos.y = 200;
	player1.moveDir = DIR_DOWN;
	player1.moveSpeed = 2;
	turnFlag = false;
	dashCnt = 0;
}

void PlayerDrawInit(void)
{
	// 仮置きのプレイヤー
	if (player1.moveDir == DIR_DOWN)
	{
		DrawBox(player1.pos.x, player1.pos.y, player1.pos.x + 32, player1.pos.y + 32, GetColor(255, 0, 0), true);
	}
	if (player1.moveDir == DIR_RIGHT)
	{
		DrawBox(player1.pos.x, player1.pos.y, player1.pos.x + 32, player1.pos.y + 32, GetColor(0, 255, 255), true);
	}
	if (player1.moveDir == DIR_UP)
	{
		DrawBox(player1.pos.x, player1.pos.y, player1.pos.x + 32, player1.pos.y + 32, GetColor(0, 0, 255), true);
	}
	if (player1.moveDir == DIR_LEFT)
	{
		DrawBox(player1.pos.x, player1.pos.y, player1.pos.x + 32, player1.pos.y + 32, GetColor(255, 255, 255), true);
	}
	DrawFormatString(0, 16, GetColor(255, 0, 0), "%d,%d", player1.pos.x, player1.pos.y);
	DrawFormatString(0, 32, GetColor(255, 0, 0), "%d", player1.moveDir);
}

void PlayerControl(void)
{

	if (keyNew[KEY_ID_P1DOWN])
	{
		player1.moveDir = DIR_DOWN;
		dashCnt++;
		if (dashCnt <= dashStart)
		{
			player1.pos.y += player1.moveSpeed;
		}
		else
		{
			player1.pos.y += player1.moveSpeed * 2;
		}
	}
	if (keyNew[KEY_ID_P1RIGHT])
	{
		player1.moveDir = DIR_RIGHT;
		dashCnt++;
		if (dashCnt <= dashStart)
		{
			player1.pos.x += player1.moveSpeed;
		}
		else
		{
			player1.pos.x += player1.moveSpeed*2;
		}
	}
	if (keyNew[KEY_ID_P1UP])
	{
		player1.moveDir = DIR_UP;
		dashCnt++;
		if (dashCnt <= dashStart)
		{
			player1.pos.y -= player1.moveSpeed;
		}
		else
		{
			player1.pos.y -= player1.moveSpeed*2;
		}
	}
	if (keyNew[KEY_ID_P1LEFT])
	{
		player1.moveDir = DIR_LEFT;
		dashCnt++;
		if (dashCnt <= dashStart)
		{
			player1.pos.x -= player1.moveSpeed;
		}
		else
		{
			player1.pos.x -= player1.moveSpeed*2;
		}
	}

	// ボタンを離したときダッシュを止める
	if (keyUpTrigger[KEY_ID_P1DOWN]|| keyUpTrigger[KEY_ID_P1RIGHT]|| keyUpTrigger[KEY_ID_P1UP]|| keyUpTrigger[KEY_ID_P1LEFT])
	{
		dashCnt = 0;
	}

	if (keyDownTrigger[KEY_ID_PLAYER_ACSION])
	{
		if (player1.moveDir == DIR_DOWN)
		{
			DrawBox(player1.pos.x, player1.pos.y+32, player1.pos.x + 32, player1.pos.y + 64, GetColor(255, 255, 255), true);
		}
		if (player1.moveDir == DIR_RIGHT)
		{
			DrawBox(player1.pos.x+32, player1.pos.y, player1.pos.x + 64, player1.pos.y + 32, GetColor(255, 255, 255), true);
		}
		if (player1.moveDir == DIR_UP)
		{
			DrawBox(player1.pos.x, player1.pos.y-32, player1.pos.x + 32, player1.pos.y, GetColor(255, 255, 255), true);
		}
		if (player1.moveDir == DIR_LEFT)
		{
			DrawBox(player1.pos.x-32, player1.pos.y, player1.pos.x, player1.pos.y + 32, GetColor(255, 255, 255), true);
		}
	}
}