#include "DxLib.h"
#include "main.h"
#include "map.h"

int mapImage;		// ƒ}ƒbƒv‰æ‘œ
int cloudImage;	// ‰_‰æ‘œ
CHARACTER cloud[CLOUD_MAX];
int chipImage;
XY mapPos;
int map[20][20];

void StageInit(void)
{
	mapImage = LoadGraph("image/backmap.png");
	cloudImage = LoadGraph("image/cloud.png");
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
	for (int x = 0;x < 25;x++)
	{
		for (int y = 4;y < 20;y++)
		{
			DrawBox(32 * x, 32 * y, 32 * x + 32, 32 * y + 32, GetColor(0, 255, 0), false);
			DrawBox(32 * x, 32 * y, 32 * x + 32, 32 * y + 32, GetColor(0, 255, 0), true);
			//if (x == 18)
			//{
			//	DrawBox(32 * x, 32 * y, 32 * x + 32, 32 * y + 32, GetColor(255, 0, 0), true);
			//}
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				DrawBox(32 * x, 32 * y, 32 * x + 32, 32 * y + 32, GetColor(0, 255, 0), false);
			}
		}
	}
}