#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "player2.h"
#include "map.h"
#include "keycheck.h"
#include "playerAction.h"
#include "treasure.h"
#include "soil.h"


#define PLAYER_DEF_SPEED	2	// プレイヤーの初期速度
#define PLAYER_DASH_SPEED	4	// プレイヤーの走行中速度
#define SLOT_MAX			3	// アイテム最大所持数
#define INIT_VELOCITY		30.0f	// リアクション跳躍の初速度

CHARACTER player1;		//プレイヤー１の構造体
int playerImage[16];	// プレイヤーの画像格納用
int playerAct[4];		// プレイヤーのアクションの画像格納用
bool turnFlag;			// 振り向き制御用
bool digFlag;			// 採掘可能か否か
bool moveFlag;			// 移動可能か否か
bool runFlag;			// 移動中か否か
bool itemFlag;			// アイテムを取得するためのフラグ 
int treasureGetImage;	// 現在のアイテム取得数表示用
int actTime;			// アクションを行う時間
int stockDrillImage;	// 所持中のドリルの画像格納用
int stockBombImage;		// 所持中の爆弾の画像格納用
int stockCallImage;		// 所持中の通信機の画像格納用
int stockSearchImage;	// 所持中のレーダーアイテムの画像格納用
int selectImage[2];		// アイテム選択画面の画像格納用
int damageImage[4];		// ダメージ時のプレイヤー画像格納用
int radarImage[4];		// レーダー画像格納用
XY	playerDamagePos;	// プレイヤーがダメージを受けた地点の座標
int DamageSpeed;		// ダメージを受けた際の移動速度
int radarSearch;		// アイテムまでの距離
int SearchTime;			// レーダーアイテムの使用時間

void PlayerSystemInit(void)
{
	LoadDivGraph("image/moleOll.png", 16, 4, 4, PLAYER_SIZE_X, PLAYER_SIZE_Y, playerImage, false);
	LoadDivGraph("image/digAction.png", 4, 1, 4, PLAYER_SIZE_X, PLAYER_SIZE_Y, playerAct, false);
	treasureGetImage = LoadGraph("image/potato.png");
	stockDrillImage = LoadGraph("image/DrillIcon.png");
	stockBombImage = LoadGraph("image/BombIcon.png");
	stockCallImage = LoadGraph("image/CallIcon.png");
	stockSearchImage = LoadGraph("image/SearchIcon.png");
	LoadDivGraph("image/ItemSelect.png", 2, 2, 1, SELECT_SIZE_X, SELECT_SIZE_Y, selectImage, false);
	LoadDivGraph("image/moleDamage.png", 4, 4, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, damageImage, false);
	LoadDivGraph("image/RadarIcon.png", 4, 4, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, radarImage, false);
}

void PlayerGameInit(void)
{
	player1.pos = { 112,112 };
	player1.size.x = PLAYER_SIZE_X;
	player1.size.y = PLAYER_SIZE_Y;
	player1.sizeOffset.x = player1.size.x / 2;
	player1.sizeOffset.y = player1.size.y / 2;
	player1.moveDir = DIR_DOWN;
	player1.oldmoveDir = player1.moveDir;
	player1.moveSpeed = PLAYER_DEF_SPEED;
	player1.distance = 0;
	player1.Flag = false;
	player1.AnimCnt = 0;
	player1.slot = 0;
	player1.score = 0;
	player1.item = ITEM_DRILL;
	player1.itemStock = 3;
	player1.type = P_1;
	player1.velocity = { 0,0 };
	DamageSpeed = 0;
	turnFlag = false;
	digFlag = false;
	moveFlag = false;
	runFlag = false;
	itemFlag = false;
	actTime = 0;
	playerDamagePos = player1.pos;
	radarSearch = 0;
	SearchTime = 0;
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
		case ITEM_CALL:
			DrawGraph(32 + 34 * Item, 32, stockCallImage, true);
			break;
		case ITEM_RADAR:
			DrawGraph(32 + 34 * Item, 32, stockSearchImage, true);
			break;
		default:
			break;
		}
	}

	if (itemFlag)
	{
		DrawGraph(player1.pos.x - SELECT_SIZE_X / 2, -mapPos.y + player1.pos.y - SELECT_SIZE_Y/2, selectImage[player1.AnimCnt / 10 % 2], true);
	}
	else if (player1.Flag)
	{
		// ダメージ時に表示する処理
		DrawGraph(player1.pos.x - player1.sizeOffset.x, -mapPos.y + player1.pos.y - player1.sizeOffset.y, damageImage[(player1.AnimCnt / 5) % 4], true);
	}
	else
	{
		if (actTime >= 0)
		{
			DrawGraph(player1.pos.x - player1.sizeOffset.x, -mapPos.y + player1.pos.y - player1.sizeOffset.y, playerAct[player1.moveDir], true);

		}
		else
		{
			if (player1.moveSpeed>=PLAYER_DASH_SPEED)
			{
				DrawGraph(player1.pos.x - player1.sizeOffset.x, -mapPos.y + player1.pos.y - player1.sizeOffset.y, playerImage[player1.moveDir * 4 + (player1.AnimCnt / 5) % 4], true);
			}
			else
			{
				DrawGraph(player1.pos.x - player1.sizeOffset.x, -mapPos.y + player1.pos.y - player1.sizeOffset.y, playerImage[player1.moveDir * 4 + (player1.AnimCnt / 10) % 4], true);
			}
		}
	}

	DrawGraph(144, 32, radarImage[radarSearch], true);
	DrawFormatString(0, 16, GetColor(255, 0, 0), "pos.x:%d,pos.y%d", player1.pos.x, player1.pos.y);
	DrawFormatString(0, 32, GetColor(255, 0, 0), "DIR%d", player1.moveDir);
	DrawFormatString(0, 48, GetColor(255, 0, 0), "DISTANCE:%d", player1.distance);
	DrawFormatString(0, 64, GetColor(255, 0, 0), "SLOT:%d", player1.slot);
	DrawFormatString(0, 80, GetColor(255, 0, 0), "SCORE:%d", player1.score);
	DrawFormatString(120, 0, GetColor(255, 0, 0), "%d", itemFlag);
	DrawFormatString(0, 128, GetColor(255, 0, 0), "%d", player1.Flag);
	DrawFormatString(0, 154, GetColor(255, 0, 0), "%d", radarSearch);
	DrawFormatString(0, 170, GetColor(255, 0, 0), "Search:%d", SearchTime);
	DrawFormatString(0, 186, GetColor(0, 255, 0), "Speed:%d", player1.moveSpeed);
	//DrawFormatString(0, 202, GetColor(0, 255, 0), "DSpeed:%d", DamageSpeed);
	// デバッグ用のプレイヤーの当たり枠
	DrawBox(player1.pos.x - player1.sizeOffset.x, -mapPos.y + player1.pos.y - player1.sizeOffset.y,
		player1.pos.x + player1.sizeOffset.x, -mapPos.y + player1.pos.y + player1.sizeOffset.y, GetColor(255, 255, 255), false);
}

void PlayerControl(void)
{
	digFlag = true;
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

	XY PlayerPosCopy = player1.pos;

	// ダメージリアクション
	if (player1.Flag)
	{
		// 速度の変更
		player1.velocity.y -= ACC_G * FRAME_TIME;
		// 移動距離の追加
		player1.pos.y -= player1.velocity.y * FRAME_TIME;
		if (playerDamagePos.y < player1.pos.y)
		{
			player1.pos = playerDamagePos;
			// 移動中にダメージを受けた際に微妙にずれる座標を調整
			if (moveFlag)
			{
				//if (player1.moveDir == DIR_DOWN || player1.moveDir == DIR_RIGHT)
				//{
				//	player1.pos.x += (player1.pos.x + player1.sizeOffset.x) % 32;
				//	player1.pos.y += (player1.pos.y + player1.sizeOffset.y) % 32;
				//}
				//if (player1.moveDir == DIR_UP || player1.moveDir == DIR_LEFT)
				//{
				//	player1.pos.x -= (player1.pos.x + player1.sizeOffset.x) % 32;
				//	player1.pos.y -= (player1.pos.y + player1.sizeOffset.y) % 32;
				//}
				switch (player1.moveDir)
				{
				case DIR_DOWN:
					player1.pos.y += player1.distance + DamageSpeed;
					if (player1.pos.y - mapPos.y > SCREEN_SIZE_Y - (CHIP_SIZE_Y * 5 - player1.sizeOffset.y)
						&& player1.pos.y <= CHIP_SIZE_Y * (MAP_SIZE_Y - 5) + player1.sizeOffset.y)
					{
						mapPos.y += player1.distance + DamageSpeed;
					}
					break;
				case DIR_RIGHT:
					player1.pos.x += player1.distance + DamageSpeed;
					break;
				case DIR_UP:
					player1.pos.y -= player1.distance + DamageSpeed;
					if (player1.pos.y - mapPos.y < CHIP_SIZE_Y * 5 - player1.sizeOffset.y && mapPos.y>0)
					{
						mapPos.y -= player1.distance + DamageSpeed;
					}
					break;
				case DIR_LEFT:
					player1.pos.x -= player1.distance + DamageSpeed;
					break;
				default:
					break;
				}
				player1.distance = 0;
				moveFlag = false;
			}
			player1.Flag = false;
		}
	}
	else
	{
		playerDamagePos = player1.pos;
	}

	// プレイヤーが移動方向を向いていない場合は方向転換を行い向いている場合は移動を行う
	if (!moveFlag && !player1.Flag)
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
				player1.moveSpeed = PLAYER_DEF_SPEED;
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
				player1.moveSpeed = PLAYER_DEF_SPEED;
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
				player1.moveSpeed = PLAYER_DEF_SPEED;
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
				player1.moveSpeed = PLAYER_DEF_SPEED;
			}
		}
	}

	// プレイヤーの移動処理

	if (moveFlag && player1.distance > 0 && !player1.Flag)
	{
		//player1.distance = PLAYER_DISTANCE;
		switch (player1.moveDir)
		{
		case DIR_DOWN:
			digFlag = false;
			player1.distance -= player1.moveSpeed;
			player1.pos.y += player1.moveSpeed;
			if (player1.pos.y - mapPos.y > SCREEN_SIZE_Y - (CHIP_SIZE_Y * 5 - player1.sizeOffset.y) 
				&& player1.pos.y <= CHIP_SIZE_Y * (MAP_SIZE_Y - 5) + player1.sizeOffset.y)
			{
				mapPos.y += player1.moveSpeed;
			}
			break;
		case DIR_RIGHT:
			digFlag = false;
			player1.distance -= player1.moveSpeed;
			player1.pos.x += player1.moveSpeed;
			break;
		case DIR_UP:
			digFlag = false;
			player1.distance -= player1.moveSpeed;
			player1.pos.y -= player1.moveSpeed;
			if (player1.pos.y - mapPos.y < CHIP_SIZE_Y * 5 - player1.sizeOffset.y && mapPos.y>0)
			{
				mapPos.y -= player1.moveSpeed;
			}
			break;
		case DIR_LEFT:
			digFlag = false;
			player1.distance -= player1.moveSpeed;
			player1.pos.x -= player1.moveSpeed;
			break;
		default:
			break;
		}
		runFlag = true;
	}

	// 一定座標でアイテムボタンを押した場合
	if (player1.pos.y < 144 && player1.distance == 0 && keyDownTrigger[KEY_ID_P1_ITEM] && !player1.Flag)
	{
		itemFlag = true;
	}
	if (itemFlag)
	{
		player1.moveDir = DIR_UP;
		player1.distance = 0;
		if (keyUpTrigger[KEY_ID_P1UP])
		{
			player1.item = ITEM_DRILL;
			player1.itemStock = 3;
			player1.moveDir = DIR_DOWN;
			itemFlag = false;
		}
		if (keyUpTrigger[KEY_ID_P1RIGHT])
		{
			player1.item = ITEM_BOMB;
			player1.itemStock = 2;
			player1.moveDir = DIR_DOWN;
			itemFlag = false;
		}
		if (keyUpTrigger[KEY_ID_P1DOWN])
		{
			player1.item = ITEM_CALL;
			player1.itemStock = 1;
			player1.moveDir = DIR_DOWN;
			itemFlag = false;
		}
		if (keyUpTrigger[KEY_ID_P1LEFT])
		{
			player1.item = ITEM_RADAR;
			player1.itemStock = 1;
			player1.moveDir = DIR_DOWN;
			itemFlag = false;
		}
	}

	// 現在の向きを記録
	player1.oldmoveDir = player1.moveDir;

	// ボタンを離したときダッシュを止める
	if (keyUpTrigger[KEY_ID_P1DOWN]|| keyUpTrigger[KEY_ID_P1RIGHT]|| keyUpTrigger[KEY_ID_P1UP]|| keyUpTrigger[KEY_ID_P1LEFT])
	{
		player1.moveSpeed = PLAYER_DEF_SPEED;
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
					player1.moveSpeed = PLAYER_DASH_SPEED;
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
					player1.moveSpeed = PLAYER_DASH_SPEED;
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
					player1.moveSpeed = PLAYER_DASH_SPEED;
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
					player1.moveSpeed = PLAYER_DASH_SPEED;
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

	// 穴掘りアクション
	if (keyDownTrigger[KEY_ID_P1_ACTION] && digFlag && !player1.Flag)
	{
		actTime = 10;
		CliateDig(player1.pos, player1.moveDir,player1.type,actTime);

	}

	// アイテム使用
	if (keyDownTrigger[KEY_ID_P1_ITEM] && digFlag && !itemFlag && !player1.Flag)
	{
		if (player1.itemStock > 0)
		{
			if (CheckItemStock(player1.item))
			{
				switch (player1.item)
				{
				case ITEM_DRILL:
					CliateDrill(player1.pos, player1.moveDir);
					//player1.itemStock--;
					break;
				case ITEM_BOMB:
					CliateBomb(player1.pos, player1.moveDir);
					//player1.itemStock--;
					break;
				case ITEM_CALL:
					if (player1.slot > 0)
					{
						player1.slot--;
						player1.score++;
						//player1.itemStock--;
					}
					break;
				case ITEM_RADAR:
					SearchTime = 60;
					//TreasureSearch(player1.pos,60);
					break;
				default:
					break;
				}
			}
		}
	}

	// 得点アイテム取得時の処理
	if (!player1.Flag)
	{
		if (TreasureGet(player1.pos, player1.slot))
		{
			player1.slot++;
		}
	}

	// 得点アイテムの回収処理
	if (player1.pos.y <= 112 && !player1.Flag)
	{
		player1.score += player1.slot;
		OllTreasure(player1.slot);
		player1.slot = 0;
	}

	//	 レーダー処理
	if ((player1.pos.x - 16) % 32 == 0 && (player1.pos.y - 16) % 32 == 0 && !player1.Flag)
	{
		if (TreasureDistance(player1.pos) < 4)
		{
			radarSearch = TreasureDistance(player1.pos);
		}
		else
		{
			radarSearch = 0;
		}
	}

	if (SearchTime >= 0)
	{
		SearchTime--;
		TreasureSearch(player1.pos, SearchTime);
	}

	// ワームが当たった時の処理
	if (WarmControl(player1.pos, player1.sizeOffset.x) && player1.slot > 0 && !player1.Flag)
	{
		player1.slot--;
		Player2ItemPoint();
	}

	// テスト用
	if (keyDownTrigger[KEY_ID_SPACE] && !player1.Flag)
	{
		player1.Flag = true;
		player1.velocity.y = INIT_VELOCITY;
		DamageSpeed = player1.moveSpeed;
	}
	if (CheckHitKey(KEY_INPUT_C))
	{
		player1.Flag = false;
	}
	if (CheckHitKey(KEY_INPUT_B))
	{
		player1.moveSpeed = 0;
	}


	//if (player1.Flag)
	//{
	//	if (player1.slot > 0)
	//	{
	//		player1.slot--;
	//		
	//	}
	//}
	//player1.Flag = false;
}

// プレイヤーの当たり判定
bool PlayerHitCheck(XY pos, int size)
{
	//if (player1.pos.x - player1.sizeOffset.x<pos.x + size
	//	&& player1.pos.x + player1.sizeOffset.x > pos.x - size
	//	&& player1.pos.y - player1.sizeOffset.y <pos.y + size
	//	&& player1.pos.y + player1.sizeOffset.y > pos.y - size
	//	&& !player1.Flag)
	if (player1.pos.x - player1.sizeOffset.x <pos.x + size
		&& player1.pos.x + player1.sizeOffset.x > pos.x - size
		&& player1.pos.y - player1.sizeOffset.y <pos.y + size
		&& player1.pos.y + player1.sizeOffset.y > pos.y - size
		&& !player1.Flag
		&& !itemFlag)
	{
		if (player1.slot > 0 && !player1.Flag)
		{
			player1.slot--;
			
		}
		player1.Flag = true;
		player1.velocity.y = INIT_VELOCITY;
		DamageSpeed = player1.moveSpeed;
		return true;
	}
	return false;
}