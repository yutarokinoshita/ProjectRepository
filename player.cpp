#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "map.h"
#include "keycheck.h"
#include "playerAction.h"
#include "treasure.h"
#include "soil.h"

CHARACTER player1;		//プレイヤー１の構造体
int playerImage[16];	// プレイヤーの画像格納用
int playerAct[4];		// プレイヤーのアクションの画像格納用
bool turnFlag;			// 振り向き制御用
bool dashFlag;			// ダッシュを始めるまで
bool digFlag;			// 採掘可能か否か
bool moveFlag;			// 移動可能か否か
bool runFlag;			// 移動中か否か
int treasureGetImage;	// 現在のアイテム取得数表示用
int actTime;			// アクションを行う時間
int stockDrillImage;	// 所持中のドリルの画像格納用
int stockBombImage;		// 所持中の爆弾の画像格納用

void PlayerSystemInit(void)
{
	LoadDivGraph("image/moleOll.png", 16, 4, 4, PLAYER_SIZE_X, PLAYER_SIZE_Y, playerImage, false);
	LoadDivGraph("image/digAction.png", 4, 1, 4, PLAYER_SIZE_X, PLAYER_SIZE_Y, playerAct, false);
	treasureGetImage = LoadGraph("image/potato.png");
	stockDrillImage = LoadGraph("image/DrillIcon.png");
	stockBombImage = LoadGraph("image/BombIcon.png");
	player1.pos.x = 336;//112;
	player1.pos.y = 336;//112;
	player1.size.x = PLAYER_SIZE_X;
	player1.size.y = PLAYER_SIZE_Y;
	player1.sizeOffset.x = player1.size.x / 2;
	player1.sizeOffset.y = player1.size.y / 2;
	player1.moveDir = DIR_DOWN;
	player1.oldmoveDir = player1.moveDir;
	player1.moveSpeed = 2;
	player1.AnimCnt = 0;
	player1.slot = 0;
	player1.score = 0;
	player1.item = ITEM_BOMB;
	player1.itemStock = 3;
	turnFlag = false;
	dashFlag = false;
	digFlag = false;
	moveFlag = false;
	runFlag = false;
	actTime = 0;
}

void PlayerGameDraw(void)
{
	player1.AnimCnt++;
	actTime--;
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
	for (int tre = 0;tre < player1.slot;tre++)
	{
		DrawGraph(32 + 32 * tre, 0, treasureGetImage, true);
	}
	for (int Item = 0;Item < player1.itemStock;Item++)
	{
		switch (player1.item)
		{
		case ITEM_DRILL:
			DrawGraph(32 + 34 * Item, 32, stockDrillImage, true);
			break;
		case ITEM_BOMB:
			DrawGraph(32 + 34 * Item, 32, stockBombImage, true);
			break;
		default:
			break;
		}
	}
	if (actTime >= 0)
	{
		DrawGraph(player1.pos.x - player1.sizeOffset.x, player1.pos.y - player1.sizeOffset.y, playerAct[player1.moveDir], true);

	}
	else
	{
		if (dashFlag)
		{
			DrawGraph(player1.pos.x - player1.sizeOffset.x, player1.pos.y - player1.sizeOffset.y, playerImage[player1.moveDir * 4 + (player1.AnimCnt / 5) % 4], true);
		}
		else
		{
			DrawGraph(player1.pos.x - player1.sizeOffset.x, player1.pos.y - player1.sizeOffset.y, playerImage[player1.moveDir * 4 + (player1.AnimCnt / 10) % 4], true);
		}
	}
	DrawFormatString(0, 16, GetColor(255, 0, 0), "pos.x:%d,pos.y%d", player1.pos.x, player1.pos.y);
	DrawFormatString(0, 32, GetColor(255, 0, 0), "DIR%d", player1.moveDir);
	DrawFormatString(0, 48, GetColor(255, 0, 0), "DISTANCE:%d", player1.distance);
	DrawFormatString(0, 64, GetColor(255, 0, 0), "SLOT:%d", player1.slot);
	DrawFormatString(0, 80, GetColor(255, 0, 0), "SCORE:%d", player1.score);
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
			if (player1.moveDir == DIR_DOWN)
			{
				PlayerPosCopy.y += PLAYER_DISTANCE;
				if (SoilIsPass(PlayerPosCopy))
				{
					player1.distance = PLAYER_DISTANCE;
					dashFlag = true;
				}
				else
				{
					moveFlag = false;
				}
			}
			if (player1.moveDir == DIR_RIGHT)
			{
				PlayerPosCopy.x += PLAYER_DISTANCE;
				if (SoilIsPass(PlayerPosCopy))
				{
					player1.distance = PLAYER_DISTANCE;
					dashFlag = true;
				}
				else
				{
					moveFlag = false;
				}
			}
			if (player1.moveDir == DIR_UP)
			{
				PlayerPosCopy.y -= PLAYER_DISTANCE;
				if (SoilIsPass(PlayerPosCopy))
				{
					player1.distance = PLAYER_DISTANCE;
					dashFlag = true;
				}
				else
				{
					moveFlag = false;
				}
			}
			if (player1.moveDir==DIR_LEFT)
			{
				PlayerPosCopy.x -= PLAYER_DISTANCE;
				if (SoilIsPass(PlayerPosCopy))
				{
					player1.distance = PLAYER_DISTANCE;
					dashFlag = true;
				}
				else
				{
					moveFlag = false;
				}
			}
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
		actTime = 10;
	}
	if (keyDownTrigger[KEY_ID_PLAYER_ITEM] && digFlag)
	{
		if (player1.itemStock > 0)
		{
			if (CheckItemStock(player1.item))
			{
				player1.itemStock--;
				switch (player1.item)
				{
				case ITEM_DRILL:
					CliateDrill(player1.pos, player1.moveDir);
					break;
				case ITEM_BOMB:
					CliateBomb(player1.pos, player1.moveDir);
					break;
				default:
					break;
				}
			}
		}
	}

	if (TreasureGet(player1.pos, player1.slot))
	{
		player1.slot++;
	}

	if (player1.pos.y <= 112)
	{
		player1.score += player1.slot;
		OllTreasure(player1.slot);
		player1.slot = 0;
	}
}