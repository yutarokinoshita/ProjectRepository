#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "player2.h"
#include "map.h"
#include "keycheck.h"
#include "playerAction.h"
#include "treasure.h"
#include "soil.h"


#define PLAYER_DEF_SPEED	4		// プレイヤー2の初期速度
#define PLAYER_DASH_SPEED	4		// プレイヤー2の走行中速度
#define SLOT_MAX			3		// プレイヤー2のアイテム最大所持数
#define INIT_VELOCITY		30.0f	// プレイヤー2のリアクション跳躍の初速度
#define ACT_SPEED			30		// プレイヤー2の採掘速度

CHARACTER player2;		//プレイヤー２の構造体
int player2Image[16];	// プレイヤー２の画像格納用
int player2Act[4];		// プレイヤー２のアクションの画像格納用
bool turnFlag2;			// 振り向き制御用
bool digFlag2;			// 採掘可能か否か
bool moveFlag2;			// 移動可能か否か
bool runFlag2;			// 移動中か否か
bool itemFlag2;			// アイテムを取得するためのフラグ 
int treasureGetImage2;	// 現在のアイテム取得数表示用
int actTime2;			// アクションを行う時間
int damage2Image[4];	// ダメージ時のプレイヤー画像格納用
XY	player2DamagePos;	// プレイヤーがダメージを受けた地点の座標
int p2Xreturn;			// プレイヤー２をスタート地点の真下に戻す

void PlayerSystemInit2(void)
{
	LoadDivGraph("image/ratOll.png", 16, 4, 4, PLAYER_SIZE_2_X, PLAYER_SIZE_2_Y, player2Image, false);
	treasureGetImage2 = LoadGraph("image/potato.png");
	LoadDivGraph("image/ratdigAction.png", 4, 1, 4, PLAYER_SIZE_2_X, PLAYER_SIZE_2_Y, player2Act, false);
	LoadDivGraph("image/ratDamage.png", 4, 4, 1, PLAYER_SIZE_2_X, PLAYER_SIZE_2_Y, damage2Image, false);
}

void PlayerGameInit2(void)
{
	player2.pos = { 272,112 };
	player2.size.x = PLAYER_SIZE_2_X;
	player2.size.y = PLAYER_SIZE_2_Y;
	player2.sizeOffset.x = player2.size.x / 2;
	player2.sizeOffset.y = player2.size.y / 2;
	player2.moveDir = DIR_DOWN;
	player2.oldmoveDir = player2.moveDir;
	player2.moveSpeed = PLAYER_DEF_SPEED;
	player2.distance = 0;
	player2.Flag = false;
	player2.AnimCnt = 0;
	player2.slot = 0;
	player2.score = 0;
	player2.item = ITEM_WARM;
	player2.itemStock = WARM_MAX;
	player2.velocity = { 0,0 };
	turnFlag2 = false;
	digFlag2 = false;
	moveFlag2 = false;
	runFlag2 = false;
	itemFlag2 = false;
	actTime2 = 0;
	player2DamagePos = player2.pos;
	p2Xreturn = 272;
}

void PlayerGameDraw2(void)
{
	player2.AnimCnt++;
	actTime2--;

	for (int tre = 0;tre < player2.slot;tre++)
	{
		DrawGraph(SCREEN_SIZE_X - 32 - 32 * tre, 0, treasureGetImage2, true);
	}
if (player2.Flag)
	{
		// ダメージ時に表示する処理
		DrawGraph(player2.pos.x - player2.sizeOffset.x, -mapPos.y + player2.pos.y - player2.sizeOffset.y, damage2Image[(player2.AnimCnt / 5) % 4], true);
	}
else
{
	if (actTime2 > 0)
	{
		DrawGraph(player2.pos.x - player2.sizeOffset.x, -mapPos.y + player2.pos.y - player2.sizeOffset.y, player2Act[player2.moveDir], true);
	}
	else
	{
		DrawGraph(player2.pos.x - player2.sizeOffset.x, -mapPos.y + player2.pos.y - player2.sizeOffset.y, player2Image[player2.moveDir * 4 + (player2.AnimCnt / 20) % 4], true);
	}
}
	//DrawFormatString(0, 16, GetColor(255, 0, 0), "pos.x:%d,pos.y%d", player2.pos.x, player2.pos.y);
	//DrawFormatString(0, 32, GetColor(255, 0, 0), "DIR%d", player2.moveDir);
	//DrawFormatString(0, 48, GetColor(255, 0, 0), "DISTANCE:%d", player2.distance);
	//DrawFormatString(0, 64, GetColor(255, 0, 0), "SLOT:%d", player2.slot);
	//DrawFormatString(0, 80, GetColor(255, 0, 0), "SCORE:%d", player2.score);
	//DrawFormatString(120, 0, GetColor(255, 0, 0), "%d", itemFlag2);
	//DrawFormatString(0, 128, GetColor(255, 0, 0), "%d", player2.Flag);
	//DrawFormatString(0, 154, GetColor(255, 0, 0), "%d", radarSearch2);
	//DrawFormatString(0, 170, GetColor(255, 0, 0), "Search:%d", SearchTime2);
	//DrawFormatString(0, 186, GetColor(0, 255, 0), "Speed:%d", player2.moveSpeed);
	DrawFormatString(0, 218, GetColor(0, 255, 0), "p2Search:%d", (TreasureXsearch(player2.pos)));
	// デバッグ用のプレイヤーの当たり枠
	DrawBox(player2.pos.x - player2.sizeOffset.x, -mapPos.y + player2.pos.y - player2.sizeOffset.y,
		player2.pos.x + player2.sizeOffset.x, -mapPos.y + player2.pos.y + player2.sizeOffset.y, GetColor(255, 255, 255), false);
}

void PlayerControl2(void)
{
	digFlag2 = true;
	////if (player1.pos.y < 112)
	////{
	////	player1.pos.y = 112;
	////}
	//if (player1.pos.x < 16)
	//{
	//	player1.pos.x = 16;
	//}
	//if (player1.pos.x > 784)
	//{
	//	player1.pos.x = 784;
	//}
	////if (player1.pos.y >= 592)
	////{
	////	player1.pos.y = 592;
	////}

	XY PlayerPosCopy = player2.pos;

	// ダメージリアクション
	if (player2.Flag)
	{
		// 速度の変更
		player2.velocity.y -= ACC_G * FRAME_TIME;
		// 移動距離の追加
		player2.pos.y -= player2.velocity.y * FRAME_TIME;
		if (player2DamagePos.y < player2.pos.y)
		{
			player2.pos = player2DamagePos;
			// 移動中にダメージを受けた際に微妙にずれる座標を調整
			if (moveFlag2)
			{
				if (player2.moveDir == DIR_DOWN || player2.moveDir == DIR_RIGHT)
				{
					player2.pos.x += (player2.pos.x + player2.sizeOffset.x) % 32;
					player2.pos.y += (player2.pos.y + player2.sizeOffset.y) % 32;
				}
				if (player2.moveDir == DIR_UP || player2.moveDir == DIR_LEFT)
				{
					player2.pos.x -= (player2.pos.x + player2.sizeOffset.x) % 32;
					player2.pos.y -= (player2.pos.y + player2.sizeOffset.y) % 32;
				}
				player2.distance = 0;
				moveFlag2 = false;
			}
			player2.Flag = false;
		}
	}
	else
	{
		player2DamagePos = player2.pos;
	}

	// アイテムのある方向に進み続け、３つ所持したら上に戻る
	//if (player2.distance <= 0 && actTime2 <= 0)
	if ((player2.pos.x+16)%32 == 0 && (player2.pos.y + 16) % 32 == 0 && actTime2 <= 0)
	{
		if (player2.slot == SLOT_MAX)
		{
			player2.moveDir = DIR_UP;
			PlayerPosCopy.y -= PLAYER_DISTANCE_2;
			if (SoilIsPass(PlayerPosCopy))
			{
				player2.distance += PLAYER_DISTANCE_2;
			}
			else
			{
				actTime2 = ACT_SPEED;
			}
		}
		else
		{
			if (TreasureYsearch(player2.pos))
			{
				if (TreasureXsearch(player2.pos) > 0)
				{
					player2.moveDir = DIR_LEFT;
					PlayerPosCopy.x -= PLAYER_DISTANCE_2;
					if (SoilIsPass(PlayerPosCopy))
					{
						player2.distance += PLAYER_DISTANCE_2;
						//player2.pos.x -= player2.moveSpeed;
					}
					else
					{
						actTime2 = ACT_SPEED;
					}
				}
				if (TreasureXsearch(player2.pos) < 0)
				{
					player2.moveDir = DIR_RIGHT;
					PlayerPosCopy.x += PLAYER_DISTANCE_2;
					if (SoilIsPass(PlayerPosCopy))
					{
						player2.distance += PLAYER_DISTANCE_2;
						//player2.pos.x += player2.moveSpeed;
					}
					else
					{
						actTime2 = ACT_SPEED;
					}
				}
			}
			else
			{
				player2.moveDir = DIR_DOWN;
				PlayerPosCopy.y += PLAYER_DISTANCE_2;
				if (SoilIsPass(PlayerPosCopy))
				{
					player2.distance += PLAYER_DISTANCE_2;
					//player2.pos.y += player2.moveSpeed;
				}
				else
				{
					actTime2 = ACT_SPEED;
				}
			}
		}
	}
	DrawFormatString(0, 234, GetColor(0, 255, 0), "p2CopyX:%d,p2CopyY:%d", PlayerPosCopy.x, PlayerPosCopy.y);

	// プレイヤーの移動処理
	//if (player2.distance > 0 && !player2.Flag && player2.AnimCnt % 8 == 0 && actTime2 <= 0)
	if (!(player2.pos.x + 16) % 32 == 0 && !(player2.pos.y + 16) % 32 == 0 && !player2.Flag && player2.AnimCnt % 8 == 0 && actTime2 <= 0)
	{
		//player1.distance = PLAYER_DISTANCE;
		switch (player2.moveDir)
		{
		case DIR_DOWN:
			digFlag2 = false;
			player2.distance -= player2.moveSpeed;
			player2.pos.y += player2.moveSpeed;
			break;
		case DIR_RIGHT:
			digFlag2 = false;
			player2.distance -= player2.moveSpeed;
			player2.pos.x += player2.moveSpeed;
			break;
		case DIR_UP:
			digFlag2 = false;
			player2.distance -= player2.moveSpeed;
			player2.pos.y -= player2.moveSpeed;
			break;
		case DIR_LEFT:
			digFlag2 = false;
			player2.distance -= player2.moveSpeed;
			player2.pos.x -= player2.moveSpeed;
			break;
		default:
			break;
		}
		runFlag2 = true;
	}
	// 穴掘りアクション
	if (actTime2==ACT_SPEED)
	{
		CliateDig(player2.pos, player2.moveDir);
	}
	if (actTime2 > 0)
	{
		actTime2--;
	}
	// 現在の向きを記録
	//player2.oldmoveDir = player2.moveDir;

	// 得点アイテム取得時の処理
	if (!player2.Flag)
	{
		if (TreasureGet(player2.pos, player2.slot))
		{
			player2.slot++;
		}
	}

	// 得点アイテムの回収処理
	if (player2.pos.y <= 112 && !player2.Flag)
	{
		player2.score += player2.slot;
		OllTreasure(player2.slot);
		player2.slot = 0;
	}

	// アイテム使用
	if (player2.AnimCnt % 300 == 0)
	{
		if (player2.itemStock > 0)
		{
			CliateWarm(player2.pos);
		}
	}

	// テスト用
	if (keyDownTrigger[KEY_ID_SPACE] && !player2.Flag)
	{
		player2.Flag = true;
		player2.velocity.y = INIT_VELOCITY;
	}
	if (CheckHitKey(KEY_INPUT_C))
	{
		player2.Flag = false;
	}
	if (CheckHitKey(KEY_INPUT_B))
	{
		player2.moveSpeed = 0;
	}
}

// プレイヤーの当たり判定
bool PlayerHitCheck2(XY pos, int size)
{
	//if (player1.pos.x - player1.sizeOffset.x<pos.x + size
	//	&& player1.pos.x + player1.sizeOffset.x > pos.x - size
	//	&& player1.pos.y - player1.sizeOffset.y <pos.y + size
	//	&& player1.pos.y + player1.sizeOffset.y > pos.y - size
	//	&& !player1.Flag)
	if (player2.pos.x - player2.sizeOffset.x <pos.x + size
		&& player2.pos.x + player2.sizeOffset.x > pos.x - size
		&& player2.pos.y - player2.sizeOffset.y <pos.y + size
		&& player2.pos.y + player2.sizeOffset.y > pos.y - size
		&& !player2.Flag
		&& !itemFlag2)
	{
		if (player2.slot > 0 && !player2.Flag)
		{
			player2.slot--;

		}
		player2.Flag = true;
		player2.velocity.y = INIT_VELOCITY;
		return true;
	}
	return false;
}

// アイテム：ワーム命中時得点入手
void Player2ItemPoint()
{
	if (player2.slot < SLOT_MAX)
	{
		player2.slot++;
	}
}