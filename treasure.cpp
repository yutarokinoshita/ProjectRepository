#include "DxLib.h"
#include "main.h"
#include "treasure.h"

CHARACTER treasure;
int treasureImage;
bool treasureFlag;

void TreasureInit(void)
{
	treasureImage = LoadGraph("image/potato.png");
	treasure.pos.x = 208;
	treasure.pos.y = 208;
	treasure.size.x = TREASURE_SIZE_X;
	treasure.size.y = TREASURE_SIZE_Y;
	treasure.sizeOffset.x = TREASURE_SIZE_X / 2;
	treasure.sizeOffset.y = TREASURE_SIZE_Y / 2;
	treasureFlag = false;
}

void TreasureDraw(void)
{
	if (!treasureFlag)
	{
		DrawGraph(treasure.pos.x - treasure.sizeOffset.x, treasure.pos.y - treasure.sizeOffset.y, treasureImage, true);
	}
}

bool TreasureGet(XY pPos,int slot)
{
	if (!treasureFlag)
	{
		if (treasure.pos.x - treasure.sizeOffset.x < pPos.x
			&& treasure.pos.x + treasure.sizeOffset.x > pPos.x
			&& treasure.pos.y - treasure.sizeOffset.y  < pPos.y
			&& treasure.pos.y + treasure.sizeOffset.y  > pPos.y)
		{
			if (slot <= 2)
			{
				treasureFlag = true;
				return true;
			}
		}
	}
	return false;
}