#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "map.h"
#include "keycheck.h"
#include "playerAction.h"
#include "treasure.h"
#include "soil.h"

CHARACTER player1;	//プレイヤー１の構造体
int playerImage[16];
bool turnFlag;		// 振り向き制御用
bool dashFlag;		// ダッシュを始めるまで
bool digFlag;		// 採掘可能か否か
bool moveFlag;		// 移動可能か否か
bool runFlag;		// 移動中か否か

void PlayerSystemInit(void)
{
	LoadDivGraph("image/moleOll.png", 16, 4, 4, PLAYER_SIZE_X, PLAYER_SIZE_Y, playerImage, false);
	player1.pos.x = 112;
	player1.pos.y = 112;
	player1.size.x = PLAYER_SIZE_X;
	player1.size.y = PLAYER_SIZE_Y;
	player1.sizeOffset.x = player1.size.x / 2;
	player1.sizeOffset.y = player1.size.y / 2;
	player1.moveDir = DIR_DOWN;
	player1.oldmoveDir = player1.moveDir;
	player1.moveSpeed = 2;
	player1.AnimCnt = 0;
	turnFlag = false;
	dashFlag = false;
	digFlag = false;
	moveFlag = false;
	runFlag = false;
}

void PlayerGameDraw(void)
{
	player1.AnimCnt++;
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
	DrawGraph(player1.pos.x - player1.sizeOffset.x, player1.pos.y - player1.sizeOffset.y, playerImage[player1.moveDir * 4 + (player1.AnimCnt / 10) % 4], true);
	DrawFormatString(0, 16, GetColor(255, 0, 0), "%d,%d", player1.pos.x, player1.pos.y);
	DrawFormatString(0, 32, GetColor(255, 0, 0), "%d", player1.moveDir);
	DrawFormatString(0, 48, GetColor(255, 0, 0), "%d", player1.distance);
	// デバッグ用のプレイヤーの当たり枠
	DrawBox(player1.pos.x - player1.sizeOffset.x, player1.pos.y - player1.sizeOffset.y,
		player1.pos.x + player1.sizeOffset.x, player1.pos.y + player1.sizeOffset.y, GetColor(255, 255, 255), false);
}

void PlayerControl(void)
{
	digFlag = true;
	if (player1.pos.y < 112)
	{
		player1.pos.y = 112;
	}
	if (player1.pos.x < 16)
	{
		player1.pos.x = 16;
	}
	if (player1.pos.x > 784)
	{
		player1.pos.x = 784;
	}
	if (player1.pos.y > 584)
	{
		player1.pos.y = 584;
	}

	XY PlayerPosCopy = player1.pos;

	if (!moveFlag)
	{
		if (keyDownTrigger[KEY_ID_P1DOWN])
		{
			player1.moveDir = DIR_DOWN;
			// 向きが変わった場合ダッシュをやめる
			if (player1.moveDir == player1.oldmoveDir)
			{
				PlayerPosCopy.y += PLAYER_DISTANCE;
				if (SoilIsPass(PlayerPosCopy))
				{
					moveFlag = true;
					player1.distance = PLAYER_DISTANCE;
				}
			}
			else
			{
				dashFlag = false;
			}
		}
		if (keyDownTrigger[KEY_ID_P1RIGHT])
		{
			player1.moveDir = DIR_RIGHT;
			if (player1.moveDir == player1.oldmoveDir)
			{
				PlayerPosCopy.x += PLAYER_DISTANCE;
				if (SoilIsPass(PlayerPosCopy))
				{
					moveFlag = true;
					player1.distance = PLAYER_DISTANCE;
				}
			}
			else
			{
				dashFlag = false;
			}
		}
		if (keyDownTrigger[KEY_ID_P1UP])
		{
			player1.moveDir = DIR_UP;
			if (player1.moveDir == player1.oldmoveDir)
			{
				PlayerPosCopy.y -= PLAYER_DISTANCE;
				if (SoilIsPass(PlayerPosCopy))
				{
					moveFlag = true;
					player1.distance = PLAYER_DISTANCE;
				}
			}
			else
			{
				dashFlag = false;
			}
		}
		if (keyDownTrigger[KEY_ID_P1LEFT])
		{
			player1.moveDir = DIR_LEFT;
			if (player1.moveDir == player1.oldmoveDir)
			{
				PlayerPosCopy.x -= PLAYER_DISTANCE;
				if (SoilIsPass(PlayerPosCopy))
				{
					moveFlag = true;
					player1.distance = PLAYER_DISTANCE;
				}
			}
			else
			{
				dashFlag = false;
			}
		}
	}


	if (moveFlag && player1.distance > 0)
	{
		//player1.distance = PLAYER_DISTANCE;
		switch (player1.moveDir)
		{
		case DIR_DOWN:
			digFlag = false;
				if (dashFlag)
				{
					player1.distance -= player1.moveSpeed * 2;
					player1.pos.y += player1.moveSpeed * 2;
				}
				else
				{
					player1.distance -= player1.moveSpeed;
					player1.pos.y += player1.moveSpeed;
				}
			break;
		case DIR_RIGHT:
			digFlag = false;
			if (dashFlag)
			{
				player1.distance -= player1.moveSpeed * 2;
				player1.pos.x += player1.moveSpeed * 2;
			}
			else
			{
				player1.distance -= player1.moveSpeed;
				player1.pos.x += player1.moveSpeed;

			}
			break;
		case DIR_UP:
			digFlag = false;
			if (player1.pos.y >= 112)
			{
				if (dashFlag)
				{
					player1.distance -= player1.moveSpeed * 2;
					player1.pos.y -= player1.moveSpeed * 2;
				}
				else
				{
					player1.distance -= player1.moveSpeed;
					player1.pos.y -= player1.moveSpeed;
				}
			}
			else
			{
				player1.distance = 0;
			}
			break;
		case DIR_LEFT:
			digFlag = false;
			if (dashFlag)
			{
				player1.distance -= player1.moveSpeed * 2;
				player1.pos.x -= player1.moveSpeed * 2;
			}
			else
			{
				player1.distance -= player1.moveSpeed;
				player1.pos.x -= player1.moveSpeed;
			}
			break;
		default:
			break;
		}
		runFlag = true;
	}

	// 現在の向きを記録
	player1.oldmoveDir = player1.moveDir;

	// ボタンを離したときダッシュを止める
	if (keyUpTrigger[KEY_ID_P1DOWN]|| keyUpTrigger[KEY_ID_P1RIGHT]|| keyUpTrigger[KEY_ID_P1UP]|| keyUpTrigger[KEY_ID_P1LEFT])
	{
		dashFlag = false;
	}
	// 移動していないとき採掘ができる
	//if (!keyNew[KEY_ID_P1DOWN] && !keyNew[KEY_ID_P1RIGHT] && !keyNew[KEY_ID_P1UP] && !keyNew[KEY_ID_P1LEFT])
	//{
	//	digFlag = true;
	//}

	if (player1.distance <= 0 && moveFlag)
	{
		if (keyNew[KEY_ID_P1DOWN] && player1.moveDir == DIR_DOWN
			||keyNew[KEY_ID_P1RIGHT] && player1.moveDir == DIR_RIGHT
			||keyNew[KEY_ID_P1UP] && player1.moveDir == DIR_UP
			||keyNew[KEY_ID_P1LEFT] && player1.moveDir == DIR_LEFT)
		{
			player1.distance = PLAYER_DISTANCE;
			dashFlag = true;
		}
		else
		{
			runFlag = false;
			moveFlag = false;
		}
	}

	if (keyDownTrigger[KEY_ID_PLAYER_ACTION] && digFlag)
	{
		CliateDig(player1.pos, player1.moveDir);
	}

}