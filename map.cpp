#include "DxLib.h"
#include "main.h"
#include "map.h"

int mapImage;							// ”wŒi‰æ‘œ
int cloudImage;							// ‰_‰æ‘œ
int gloundImage;						// ’n–Ê‚Ì‰æ‘œ
XY cloud[CLOUD_MAX];
int soilImage[7];		
CHARACTER soil[MAP_SIZE_X][MAP_SIZE_Y];
XY mapPos;

void StageInit(void)
{
	mapImage = LoadGraph("image/backmap.png");
	cloudImage = LoadGraph("image/cloud.png");
	gloundImage = LoadGraph("image/gloundTile.png");
	LoadDivGraph("image/soil.png", 7, 7, 1, CHIP_SIZE_X, CHIP_SIZE_Y,soilImage,false);
	for (int clo = 0;clo < CLOUD_MAX;clo++)
	{
		cloud[clo].x = 0 + CLOUD_SIZE_X * clo;
		cloud[clo].y = 32;
	}
	for (int x = 0;x < MAP_SIZE_X;x++)
	{
		for (int y = 0;y < MAP_SIZE_Y;y++)
		{
			soil[x][y].pos.x = 0 + CHIP_SIZE_X * x;
			soil[x][y].pos.y = 128 + CHIP_SIZE_Y * y;
			soil[x][y].DamageFlag = false;
		}
	}
}
void StageDrawInit(void)
{
	DrawGraph(0, 0, mapImage, true);
	for (int clo = 0;clo < CLOUD_MAX;clo++)
	{
		DrawGraph(cloud[clo].x, cloud[clo].y, cloudImage, true);
		cloud[clo].x--;
		if (cloud[clo].x <= -CLOUD_SIZE_X)
		{
			cloud[clo].x = SCREEN_SIZE_X;
		}
	}
	for (int x = 0;x < MAP_SIZE_X;x++)
	{
		for (int y = 0;y < MAP_SIZE_Y;y++)
		{
			DrawGraph(0 + CHIP_SIZE_X * x, 128 + CHIP_SIZE_Y * y, gloundImage, true);
			//DrawBox(32 * x, 32 * y, 32 * x + 32, 32 * y + 32, GetColor(0, 255, 0), false);
			//DrawBox(32 * x, 32 * y, 32 * x + 32, 32 * y + 32, GetColor(0, 255, 0), true);
			////if (x == 18)
			////{
			////	DrawBox(32 * x, 32 * y, 32 * x + 32, 32 * y + 32, GetColor(255, 0, 0), true);
			////}
			//if (CheckHitKey(KEY_INPUT_SPACE))
			//{
			//	DrawBox(32 * x, 32 * y, 32 * x + 32, 32 * y + 32, GetColor(0, 255, 0), false);
			//}
			if (y <= 5)
			{
				DrawGraph(soil[x][y].pos.x, soil[x][y].pos.y, soilImage[0], true);
			}
			if (5 < y && y <= 10)
			{
				DrawGraph(soil[x][y].pos.x, soil[x][y].pos.y, soilImage[1], true);
			}
			if (10 < y)
			{
				DrawGraph(soil[x][y].pos.x, soil[x][y].pos.y, soilImage[3], true);
			}
		}
	}
}

//bool SoilCheckHit(XY dPos, int dSize)
//{
//	for (int x = 0;x < MAP_SIZE_X;x++)
//	{
//		for (int y = 0;y < MAP_SIZE_Y;y++)
//		{
//			if (!soil[x][y].DamageFlag)
//			{
//				switch (soilImage)
//				{
//				default:
//					break;
//				}
//			}
//		}
//	}
//}