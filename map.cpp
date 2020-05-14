#include "DxLib.h"
#include "main.h"
#include "map.h"

int mapImage;								// ”wŒi‰æ‘œ
int cloudImage;							// ‰_‰æ‘œ
int gloundImage;	// ’n–Ê‚Ì‰æ‘œ
CHARACTER cloud[CLOUD_MAX];
int soilImage[7];		
XY mapPos;

void StageInit(void)
{
	mapImage = LoadGraph("image/backmap.png");
	cloudImage = LoadGraph("image/cloud.png");
	gloundImage = LoadGraph("image/gloundTile.png");
	LoadDivGraph("image/soil.png", 7, 7, 1, CHIP_SIZE_X, CHIP_SIZE_Y,soilImage,false);
	for (int clo = 0;clo < CLOUD_MAX;clo++)
	{
		cloud[clo].pos.x = 0 + CLOUD_SIZE_X * clo;
		cloud[clo].pos.y = 32;
	}
}
void StageDrawInit(void)
{
	DrawGraph(0, 0, mapImage, true);
	for (int clo = 0;clo < CLOUD_MAX;clo++)
	{
		DrawGraph(cloud[clo].pos.x, cloud[clo].pos.y, cloudImage, true);
		cloud[clo].pos.x--;
		if (cloud[clo].pos.x <= -CLOUD_SIZE_X)
		{
			cloud[clo].pos.x = SCREEN_SIZE_X;
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
				DrawGraph(0 + CHIP_SIZE_X * x, 128 + CHIP_SIZE_Y * y, soilImage[0], true);
			}
			if (5 < y && y <= 10)
			{
				DrawGraph(0 + CHIP_SIZE_X * x, 128 + CHIP_SIZE_Y * y, soilImage[1], true);
			}
			if (10 < y)
			{
				DrawGraph(0 + CHIP_SIZE_X * x, 128 + CHIP_SIZE_Y * y, soilImage[3], true);
			}
		}
	}
}