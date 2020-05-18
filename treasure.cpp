#include "DxLib.h"
#include "main.h"
#include "treasure.h"

CHARACTER treasure[10];
int treasureImage;
bool treasureFlag;
int treasureReset;		// アイテムが残っているかの把握用

// アイテム初期化処理
void TreasureInit(void)
{
	treasureImage = LoadGraph("image/potato.png");
	for (int x = 0;x < 10;x++)
	{	
		treasure[x].pos.x = 208 + TREASURE_SIZE_X * x;
		treasure[x].pos.y = 208;
		treasure[x].size.x = TREASURE_SIZE_X;
		treasure[x].size.y = TREASURE_SIZE_Y;
		treasure[x].sizeOffset.x = TREASURE_SIZE_X / 2;
		treasure[x].sizeOffset.y = TREASURE_SIZE_Y / 2;
		treasure[x].DamageFlag = false;
		treasureFlag = false;
		treasureReset = 0;
	}
}

// アイテム描画
void TreasureDraw(void)
{
	for (int x = 0;x < 10;x++)
	{
		if(!treasure[x].DamageFlag)//if (!treasureFlag)
		{
			DrawGraph(treasure[x].pos.x - treasure[x].sizeOffset.x, treasure[x].pos.y - treasure[x].sizeOffset.y, treasureImage, true);
		}
	}
}

// アイテムを獲得する処理
bool TreasureGet(XY pPos,int slot)
{
	for (int x = 0;x < 10;x++)
	{
		if (!treasure[x].DamageFlag)//if (!treasureFlag)
		{
			if (treasure[x].pos.x - treasure[x].sizeOffset.x < pPos.x
				&& treasure[x].pos.x + treasure[x].sizeOffset.x > pPos.x
				&& treasure[x].pos.y - treasure[x].sizeOffset.y  < pPos.y
				&& treasure[x].pos.y + treasure[x].sizeOffset.y  > pPos.y)
			{
				if (slot <= 2)
				{
					treasure[x].DamageFlag = true;
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