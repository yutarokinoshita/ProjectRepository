#include "DxLib.h"
#include "main.h"
#include "map.h"
#include "player.h"
#include "player2.h"
#include "playerAction.h"
#include "soil.h"

CHARACTER dig;
CHARACTER drill;
CHARACTER bomb;
CHARACTER warm[WARM_MAX];
int drillImage[8];	// ドリルの画像格納用
int bombImage[6];	// 爆弾の画像格納用
int warmImage[8];	// ワームの画像格納用
void ItemSystemInit(void)
{
	LoadDivGraph("image/drill.png", 8, 2, 4, ITEM_SIZE_X, ITEM_SIZE_Y, drillImage,false);
	LoadDivGraph("image/bomb.png", 6, 6, 1, ITEM_SIZE_X, ITEM_SIZE_Y, bombImage, false);
	for (int w = 0;w < WARM_MAX;w++)
	{
		LoadDivGraph("image/warm.png", 8, 2, 4, ITEM_SIZE_X, ITEM_SIZE_Y, warmImage, false);
	}
}

void ItemGameInit(void)
{
	dig.pos.x = 0;
	dig.pos.y = 0;
	dig.size.x = ITEM_SIZE_X;
	dig.size.y = ITEM_SIZE_Y;
	dig.sizeOffset.x = ITEM_SIZE_X / 2;
	dig.sizeOffset.y = ITEM_SIZE_Y / 2;
	dig.moveDir = DIR_DOWN;
	dig.Flag = false;

	drill.pos.x = 0;
	drill.pos.y = 0;
	drill.size.x = ITEM_SIZE_X;
	drill.size.y = ITEM_SIZE_Y;
	drill.sizeOffset.x = ITEM_SIZE_X / 2;
	drill.sizeOffset.y = ITEM_SIZE_Y / 2;
	drill.moveDir = DIR_DOWN;
	drill.moveSpeed = 4;
	drill.distance = 0;
	drill.life = 0;
	drill.AnimCnt = 0;
	drill.Flag = false;

	bomb.pos.x = 0;
	bomb.pos.y = 0;
	bomb.size.x = ITEM_SIZE_X;
	bomb.size.y = ITEM_SIZE_Y;
	bomb.sizeOffset.x = ITEM_SIZE_X / 2;
	bomb.sizeOffset.y = ITEM_SIZE_Y / 2;
	bomb.moveDir = DIR_DOWN;
	bomb.moveSpeed = 8;
	bomb.distance = 0;
	bomb.life = 0;
	bomb.Flag = false;
	for (int w = 0;w < WARM_MAX;w++)
	{
		warm[w].pos.x = SCREEN_SIZE_X / 2;
		warm[w].pos.y = 48;
		warm[w].size.x = ITEM_SIZE_X;
		warm[w].size.y = ITEM_SIZE_Y;
		warm[w].sizeOffset.x = ITEM_SIZE_X / 2;
		warm[w].sizeOffset.y = ITEM_SIZE_Y / 2;
		warm[w].moveDir = DIR_DOWN;
		warm[w].moveDir = DIR_DOWN;
		warm[w].moveSpeed = 2;
		warm[w].Flag = false;
	}
}

void ItemDrawInit(void)
{
	drill.AnimCnt++;

	//if (dig.Flag)
	//{
	//	DrawBox(dig.pos.x - dig.sizeOffset.x, dig.pos.y - dig.sizeOffset.y, dig.pos.x + dig.sizeOffset.x, dig.pos.y + dig.sizeOffset.y, GetColor(255, 255, 255), true);
	//}
	if (drill.Flag)
	{
		DrawGraph(drill.pos.x - drill.sizeOffset.x, -mapPos.y + drill.pos.y - drill.sizeOffset.y, drillImage[drill.moveDir * 2 + (drill.AnimCnt / 4) % 2],true);
	}
	if (bomb.Flag)
	{
		DrawGraph(bomb.pos.x - bomb.sizeOffset.x, -mapPos.y + bomb.pos.y - bomb.sizeOffset.y, bombImage[bomb.life / 15 % 6], true);
	}
	else
	{
		DrawBox(bomb.pos.x - bomb.sizeOffset.x - ITEM_SIZE_X, -mapPos.y + bomb.pos.y - bomb.sizeOffset.y - ITEM_SIZE_Y,
			bomb.pos.x + bomb.sizeOffset.x + ITEM_SIZE_X, -mapPos.y + bomb.pos.y + bomb.sizeOffset.y + ITEM_SIZE_Y, GetColor(0, 0, 255), false);
	}
	for (int w = 0;w < WARM_MAX;w++)
	{
		if (warm[w].Flag)
		{
			warm[w].AnimCnt++;
			DrawGraph(warm[w].pos.x - warm[w].sizeOffset.x, -mapPos.y + warm[w].pos.y - warm[w].sizeOffset.y, warmImage[warm[w].moveDir * 2 + (warm[w].AnimCnt / 6) % 2], true);
		}
	}
	DrawFormatString(0, 96, GetColor(255, 0, 0), "D.Move:%d", drill.moveDir);
	DrawFormatString(0, 112, GetColor(255, 0, 0), "D.Cnt:%d", drill.AnimCnt);
	DrawFormatString(0, 300, GetColor(255, 255, 0), "warm.Cnt:%d", warm[1].AnimCnt);
}

void ItemControl(void)
{
	if (dig.Flag)
	{
		if (bomb.pos.x<dig.pos.x + dig.sizeOffset.x
			&& bomb.pos.x>dig.pos.x - dig.sizeOffset.x
			&& bomb.pos.y<dig.pos.y + dig.sizeOffset.y
			&& bomb.pos.y>dig.pos.y - dig.sizeOffset.y
			&& dig.Flag)
		{
			bomb.moveDir = dig.moveDir;
			bomb.life -= BOMB_COUNT * 2 / 3;
			bomb.distance = 32;
		}
		else
		{
			if (SoilCheckHit(dig.pos, dig.sizeOffset.x, false))
			{
				dig.Flag = false;
			}
		}
	}
	dig.Flag = false;


	if (drill.Flag)
	{
		drill.distance -= drill.moveSpeed;
		switch (drill.moveDir)
		{
		case DIR_DOWN:
			drill.pos.y += drill.moveSpeed;
			break;
		case DIR_RIGHT:
			drill.pos.x += drill.moveSpeed;
			break;
		case DIR_UP:
			drill.pos.y -= drill.moveSpeed;
			break;
		case DIR_LEFT:
			drill.pos.x -= drill.moveSpeed;
			break;
		default:
			break;
		}
		if (SoilCheckHit(drill.pos, drill.sizeOffset.x, false) || PlayerHitCheck(drill.pos, drill.sizeOffset.x) || PlayerHitCheck2(drill.pos, drill.sizeOffset.x))
		{
			drill.life--;
		}
		// 画面外へ出るか指定距離移動するか耐久値がなくなった場合消える
		if (drill.pos.x > SCREEN_SIZE_X + drill.sizeOffset.x
			|| -mapPos.y + drill.pos.y > SCREEN_SIZE_Y + drill.sizeOffset.y
			|| drill.pos.x < 0
			|| -mapPos.y + drill.pos.y < 0
			)//|| drill.distance <= 0
			//|| drill.life <= 0)
		{
			drill.Flag = false;
		}
	}

	if (bomb.Flag)
	{
		bomb.life--;
		//if (bomb.pos.x<dig.pos.x + dig.sizeOffset.x
		//	&& bomb.pos.x>dig.pos.x - dig.sizeOffset.x
		//	&& bomb.pos.y<dig.pos.y + dig.sizeOffset.y
		//	&& bomb.pos.y>dig.pos.y - dig.sizeOffset.y
		//	&& dig.Flag)
		//{
		//	bomb.moveDir = dig.moveDir;
		//	bomb.life -= BOMB_COUNT * 2 / 3;
		//	bomb.distance = 32;
		//}
		if (bomb.distance > 0 && bomb.life > 0)
		{
			switch (bomb.moveDir)
			{
			case DIR_UP:
				bomb.distance -= bomb.moveSpeed;
				bomb.pos.y -= bomb.moveSpeed;
				break;
			case DIR_RIGHT:
				bomb.distance -= bomb.moveSpeed;
				bomb.pos.x += bomb.moveSpeed;
				break;
			case DIR_DOWN:
				bomb.distance -= bomb.moveSpeed;
				bomb.pos.y += bomb.moveSpeed;
				break;
			case DIR_LEFT:
				bomb.distance -= bomb.moveSpeed;
				bomb.pos.x -= bomb.moveSpeed;
				break;
			default:
				break;
			}
		}
		if (bomb.life <= 0)
		{
			for (int hit = 0;hit <= 9;hit++)
			{
				SoilCheckHit(bomb.pos, bomb.sizeOffset.x + ITEM_SIZE_X,true);
				PlayerHitCheck(bomb.pos, bomb.sizeOffset.x + ITEM_SIZE_X);
				PlayerHitCheck2(bomb.pos, bomb.sizeOffset.x + ITEM_SIZE_X);
				bomb.distance = 0;
				bomb.Flag = false;
			}
		}
	}
	
}

// ワームの追尾及び奪取
bool WarmControl(XY Pos, int Size)
{
	int X = 0;
	int Y = 0;
	for (int w = 0;w < WARM_MAX;w++)
	{
		if (warm[w].Flag)
		{
			if (warm[w].AnimCnt % 2 == 0)
			{
				// 横から追尾するタイプ
				if (w % 2 == 0)
				{
					X = Pos.x - warm[w].pos.x;
					if (X > 0)
					{
						warm[w].moveDir = DIR_RIGHT;
						warm[w].pos.x += warm[w].moveSpeed;
					}
					if (X < 0)
					{
						warm[w].moveDir = DIR_LEFT;
						warm[w].pos.x -= warm[w].moveSpeed;
					}
					if (X == 0)
					{
						Y = Pos.y - warm[w].pos.y;
						if (Y > 0)
						{
							warm[w].moveDir = DIR_DOWN;
							warm[w].pos.y += warm[w].moveSpeed;
						}
						else if (Y < 0)
						{
							warm[w].moveDir = DIR_UP;
							warm[w].pos.y -= warm[w].moveSpeed;
						}
					}
				}
				// 縦から追尾するタイプ
				if (w % 2 == 1)
				{
					Y = Pos.y - warm[w].pos.y;
					if (Y > 0)
					{
						warm[w].moveDir = DIR_DOWN;
						warm[w].pos.y += warm[w].moveSpeed;
					}
					if (Y < 0)
					{
						warm[w].moveDir = DIR_UP;
						warm[w].pos.y -= warm[w].moveSpeed;
					}
					if (Y == 0)
					{
						X = Pos.x - warm[w].pos.x;
						if (X > 0)
						{
							warm[w].moveDir = DIR_RIGHT;
							warm[w].pos.x += warm[w].moveSpeed;
						}
						else if (X < 0)
						{
							warm[w].moveDir = DIR_LEFT;
							warm[w].pos.x -= warm[w].moveSpeed;
						}
					}
				}
			}
			if (warm[w].pos.x - warm[w].sizeOffset.x <Pos.x + Size
				&& warm[w].pos.x + warm[w].sizeOffset.x > Pos.x - Size
				&& warm[w].pos.y - warm[w].sizeOffset.y <Pos.y + Size
				&& warm[w].pos.y + warm[w].sizeOffset.y > Pos.y - Size)
			{
				warm[w].Flag = false;
				return true;
			}
		}

	}
	return false;
}
void CliateDig(XY Pos,DIR Dir)
{
	dig.moveDir = Dir;
	switch (dig.moveDir)
	{
	case DIR_DOWN:
		dig.pos.x = Pos.x;
		dig.pos.y = Pos.y + ITEM_SIZE_Y;
		break;
	case DIR_RIGHT:
		dig.pos.x = Pos.x + ITEM_SIZE_X;
		dig.pos.y = Pos.y;
		break;
	case DIR_UP:
		dig.pos.x = Pos.x ;
		dig.pos.y = Pos.y - ITEM_SIZE_Y;
		break;
	case DIR_LEFT:
		dig.pos.x = Pos.x - ITEM_SIZE_X;
		dig.pos.y = Pos.y;
		break;
	default:
		break;
	}
	dig.Flag = true;
}

// ドリルの生成
void CliateDrill(XY Pos, DIR Dir)
{
	if (!drill.Flag)
	{
		drill.moveDir = Dir;
		drill.distance = DRILL_MOVE;
		switch (drill.moveDir)
		{
		case DIR_DOWN:
			drill.pos.x = Pos.x;
			drill.pos.y = Pos.y + ITEM_SIZE_Y;
			break;
		case DIR_RIGHT:
			drill.pos.x = Pos.x + ITEM_SIZE_X;
			drill.pos.y = Pos.y;
			break;
		case DIR_UP:
			drill.pos.x = Pos.x;
			drill.pos.y = Pos.y - ITEM_SIZE_Y;
			break;
		case DIR_LEFT:
			drill.pos.x = Pos.x - ITEM_SIZE_X;
			drill.pos.y = Pos.y;
			break;
		default:
			break;
		}
		drill.distance = DRILL_MOVE;
		drill.life = DRILL_LIFE;
		drill.Flag = true;
	}
}

// 爆弾の生成
void CliateBomb(XY Pos, DIR Dir)
{
	bomb.moveDir = Dir;
	switch (bomb.moveDir)
	{
	case DIR_DOWN:
		bomb.pos.x = Pos.x;
		bomb.pos.y = Pos.y + ITEM_SIZE_Y;
		break;
	case DIR_RIGHT:
		bomb.pos.x = Pos.x + ITEM_SIZE_X;
		bomb.pos.y = Pos.y;
		break;
	case DIR_UP:
		bomb.pos.x = Pos.x;
		bomb.pos.y = Pos.y - ITEM_SIZE_Y;
		break;
	case DIR_LEFT:
		bomb.pos.x = Pos.x - ITEM_SIZE_X;
		bomb.pos.y = Pos.y;
		break;
	default:
		break;
	}
	bomb.life = BOMB_COUNT;
	bomb.Flag = true;
}

// ワームの生成
void CliateWarm(XY Pos)
{
	for (int w = 0;w < WARM_MAX;w++)
	{
		if (!warm[w].Flag)
		{
			warm[w].pos = Pos;
			warm[w].Flag = true;
			warm[w].AnimCnt = 0;
			break;
		}
	}
}

// アイテム使用確認
bool CheckItemStock(ITEM Item)
{
	switch (Item)
	{
	case ITEM_DRILL:
		if (!drill.Flag)
		{
			return true;
		}
		break;
	case ITEM_BOMB:
		if (!bomb.Flag)
		{
			return true;
		}
		break;
	case ITEM_CALL:
		return true;
		break;
	case ITEM_RADAR:
		return true;
	case ITEM_MAX:
		break;
	default:
		break;
	}
	return false;
}