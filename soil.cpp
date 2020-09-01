#include <DxLib.h>
#include "main.h"
#include "map.h"
#include "soil.h"

int soilImage[7];
CHARACTER soil[MAP_SIZE_X][MAP_SIZE_Y];

void SoilSystemInit(void)
{
	LoadDivGraph("image/soil.png", 7, 7, 1, CHIP_SIZE_X, CHIP_SIZE_Y, soilImage, false);
}

void SoilGameInit(void)
{
	for (int x = 0;x < MAP_SIZE_X;x++)
	{
		for (int y = 0;y < MAP_SIZE_Y;y++)
		{
			soil[x][y].pos.x = 0 + CHIP_SIZE_X * x;
			soil[x][y].pos.y = CHIP_SIZE_Y * y;
			soil[x][y].size.x = CHIP_SIZE_X;
			soil[x][y].size.y = CHIP_SIZE_Y;
			soil[x][y].sizeOffset.x = CHIP_SIZE_X / 2;
			soil[x][y].sizeOffset.y = CHIP_SIZE_Y / 2;
			soil[x][y].Flag = false;
			if (y <= 2)
			{
				soil[x][y].life = -1;
			}
			if (y == 3)
			{
				soil[x][y].life = 0;
			}
			if (y >= 4 && y <= STRATA_1)
			{
				soil[x][y].life = 1;
			}
			if (STRATA_1 < y && y <= STRATA_2)
			{
				soil[x][y].life = 2;
			}
			if (STRATA_2 < y)
			{
				soil[x][y].life = 3;
			}
			//if (y == 18)
			//{
			//	soil[x][y].life = 0;
			//}
		}
	}
}

void SoilDrawInit(void)
{
	for (int x = 0;x < MAP_SIZE_X;x++)
	{
		for (int y = 0;y < MAP_SIZE_Y;y++)
		{

			if (soil[x][y].life >= 1)
			{
				if (y <= STRATA_1)
				{
					DrawGraph(soil[x][y].pos.x, -mapPos.y + soil[x][y].pos.y, soilImage[0], true);
				}
				if (STRATA_1 < y && y <= STRATA_2)
				{
					if (soil[x][y].life == 2)
					{
						DrawGraph(soil[x][y].pos.x, -mapPos.y + soil[x][y].pos.y, soilImage[1], true);
					}
					if (soil[x][y].life == 1)
					{
						DrawGraph(soil[x][y].pos.x, -mapPos.y + soil[x][y].pos.y, soilImage[2], true);
					}
				}
				if (STRATA_2 < y)
				{
					if (soil[x][y].life == 3)
					{
						DrawGraph(soil[x][y].pos.x, -mapPos.y + soil[x][y].pos.y, soilImage[3], true);
					}
					if (soil[x][y].life == 2)
					{
						DrawGraph(soil[x][y].pos.x, -mapPos.y + soil[x][y].pos.y, soilImage[4], true);
					}
					if (soil[x][y].life == 1)
					{
						DrawGraph(soil[x][y].pos.x, -mapPos.y + soil[x][y].pos.y, soilImage[5], true);
					}
				}
				//if (y == 18)
				//{
				//	DrawGraph(soil[x][y].pos.x, -mapPos.y + soil[x][y].pos.y, soilImage[6], true);
				//}
				// デバッグ用当たり枠
				//DrawBox(soil[x][y].pos.x , soil[x][y].pos.y ,
				//	soil[x][y].pos.x + soil[x][y].size.x, soil[x][y].pos.y + soil[x][y].size.y, GetColor(0, 0, 255), false);
				//DrawFormatString(soil[x][y].pos.x, -mapPos.y + soil[x][y].pos.y, GetColor(255, 255, 255), "%d", y);
			}
		}
	}
}


// 地形攻撃判定
bool SoilCheckHit(XY dPos,int size,bool Bomb)
{
	for (int x = 0;x < MAP_SIZE_X;x++)
	{
		for (int y = 0;y < MAP_SIZE_Y;y++)
		{
			if (!soil[x][y].life == 0)
			{
				if (soil[x][y].pos.x < dPos.x + size
					&& soil[x][y].pos.x + soil[x][y].size.x > dPos.x - size
					&& soil[x][y].pos.y  < dPos.y + size
					&& soil[x][y].pos.y + soil[x][y].size.y > dPos.y - size)
				{
					if (Bomb)
					{
						if (soil[x][y].life >= 0)
						{
							soil[x][y].life = 0;
						}
					}
					else
					{
						soil[x][y].life--;
					}
					if (soil[x][y].life <= 0)
					{
						soil[x][y].Flag = true;
					}
					return true;
				}
			}
		}
	}
	return false;
}

// 地形通過判定
bool SoilIsPass(XY pPos)
{
	for (int x = 0;x < MAP_SIZE_X;x++)
	{
		for (int y = 0;y < MAP_SIZE_Y;y++)
		{
			if (soil[x][y].pos.x  < pPos.x
				&& soil[x][y].pos.x + soil[x][y].size.x > pPos.x
				&& soil[x][y].pos.y  < pPos.y
				&& soil[x][y].pos.y + soil[x][y].size.y  > pPos.y)
			{
				if (soil[x][y].life == 0)
				{
					return true;
				}
			}
		}
	}
	return false;
}

// プレイヤー２地形通過判定
bool SoilIsPass2(XY pPos)
{
	for (int x = 0;x < MAP_SIZE_X;x++)
	{
		for (int y = 0;y < MAP_SIZE_Y;y++)
		{
			if (pPos.y==soil[x][y].pos.y+soil[x][y].sizeOffset.y&& pPos.x == soil[x][y].pos.x + soil[x][y].sizeOffset.x)
			{
				if (soil[x][y].life == 0)
				{
					return false;
				}
			}
		}
	}
	return true;
}