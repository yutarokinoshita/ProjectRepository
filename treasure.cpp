#include <DxLib.h>
#include "main.h"
#include "treasure.h"
#include "map.h"
#include "soil.h"
#include "effect.h"

CHARACTER treasure[TREASURE_MAX];
int treasureImage;
//bool treasureFlag;
int treasureReset;		// アイテムが残っているかの把握用

// アイテム初期化処理
void TreasureSystemInit(void)
{
	treasureImage = LoadGraph("image/potato.png");
}

void TreasureGameInit(void)
{
	for (int x = 0;x < TREASURE_MAX;x++)
	{
		treasure[x].pos.x = 16 + TREASURE_SIZE_X * GetRand(24);
		if (x < 30)
		{ 
			treasure[x].pos.y = 16 + CHIP_SIZE_Y * 4 + TREASURE_SIZE_Y * GetRand(13);
		}
		if (30 <= x && x < 75)
		{
			treasure[x].pos.y = (16 + CHIP_SIZE_Y * STRATA_1) + TREASURE_SIZE_Y * GetRand(STRATA_2 - STRATA_1);
		}
		if (75 <= x)
		{
			treasure[x].pos.y = (16 + CHIP_SIZE_Y * STRATA_2) + TREASURE_SIZE_Y * GetRand(MAP_SIZE_Y - STRATA_2);
		}
		treasure[x].size.x = TREASURE_SIZE_X;
		treasure[x].size.y = TREASURE_SIZE_Y;
		treasure[x].sizeOffset.x = TREASURE_SIZE_X / 2;
		treasure[x].sizeOffset.y = TREASURE_SIZE_Y / 2;
		treasure[x].Flag = false;
		treasure[x].moveSpeed = 0;
		treasureReset = 0;
	}
}

// アイテム描画
void TreasureDraw(void)
{
	for (int x = 0;x < TREASURE_MAX;x++)
	{
		if(!treasure[x].Flag)//if (!treasureFlag)
		{
			DrawGraph(treasure[x].pos.x - treasure[x].sizeOffset.x, -mapPos.y + treasure[x].pos.y - treasure[x].sizeOffset.y, treasureImage, true);
		}
	}
}

// アイテムを獲得する処理
bool TreasureGet(XY pPos,int slot)
{
	for (int x = 0;x < TREASURE_MAX;x++)
	{
		if (!treasure[x].Flag)//if (!treasureFlag)
		{
			//if (treasure[x].pos.x - treasure[x].sizeOffset.x < pPos.x
			//	&& treasure[x].pos.x + treasure[x].sizeOffset.x > pPos.x
			//	&& treasure[x].pos.y - treasure[x].sizeOffset.y  < pPos.y
			//	&& treasure[x].pos.y + treasure[x].sizeOffset.y  > pPos.y)
			if (treasure[x].pos.x == pPos.x && treasure[x].pos.y == pPos.y)
			{
				if (slot <= 2)
				{
					//TreasureMove(slot);
					treasure[x].Flag = true;
					//treasureFlag = true;
					return true;
				}
			}
		}
	}
	return false;
}

// アイテム総取得数を計算する処理
void OllTreasure(int slot)
{
	treasureReset += slot;
}

// アイテムレーダー用の処理
void TreasureSearch(XY pPos,int Time)
{
	int TreX;
	int TreY;
	int TreXY;

	for (int x = 0;x < TREASURE_MAX;x++)
	{
		if (pPos.x > treasure[x].pos.x)
		{
				TreX = (pPos.x - treasure[x].pos.x) / 32;
		}
		else
		{
			TreX = (treasure[x].pos.x - pPos.x) / 32;
		}
			if (pPos.y > treasure[x].pos.y)
		{
			TreY = (pPos.y - treasure[x].pos.y) / 32;
		}
		else
		{
			TreY = (treasure[x].pos.y - pPos.y) / 32;
		}
		TreXY = TreX + TreY;
		if (TreXY <= 6)
		{
			ItemEffect(treasure[x].pos, x, treasure[x].Flag);
		}
		if (Time <= 0)
		{
			ItemEffect(treasure[x].pos, x, true);
		}
	}
}

// プレイヤー周辺の探索処理
int TreasureDistance(XY pPos)
{
	int TreX;
	int TreY;
	int TreXY;
	int TreMin = 4;

	for (int x = 0;x < TREASURE_MAX;x++)
	{
		if (!treasure[x].Flag)
		{
			if (pPos.x > treasure[x].pos.x)
			{
				TreX = (pPos.x - treasure[x].pos.x) / 32;
			}
			else
			{
				TreX = (treasure[x].pos.x - pPos.x) / 32;
			}
			if (pPos.y > treasure[x].pos.y)
			{
				TreY = (pPos.y - treasure[x].pos.y) / 32;
			}
			else
			{
				TreY = (treasure[x].pos.y - pPos.y) / 32;
			}
			TreXY = TreX + TreY;
			if (TreXY < TreMin)
			{
				TreMin = TreXY;
				if (TreMin <= 0)
				{
					TreMin = 1;
				}
			}
		}
		else
		{
			TreXY=4;
		}
	}
	return TreMin;
}

// CPU用得点アイテムの縦位置を探る処理
bool TreasureYsearch(XY Pos)
{
	for (int x = 0;x < TREASURE_MAX;x++)
	{
		if (!treasure[x].Flag)
		{
			if (Pos.y == treasure[x].pos.y)
			{
				if ((Pos.x - treasure[x].pos.x) / 32 <= 5 && (Pos.x - treasure[x].pos.x) / 32 >= -5)
				{
					return true;
				}
			}
		}
	}
	return false;
}

// 得点アイテムの横位置を探り移動する
int TreasureXsearch(XY Pos)
{
	int treX;
	for (int x = 0;x < TREASURE_MAX;x++)
	{
		if (!treasure[x].Flag && treasure[x].pos.y == Pos.y)
		{
			treX = Pos.x - treasure[x].pos.x;
			return treX;
		}
	}
	return 0;
}