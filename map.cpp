#include "DxLib.h"
#include "main.h"
#include "map.h"

int mapImage;
int chipImage;
XY mapPos;
int map[20][20];

void StageInit(void)
{
	mapImage = LoadGraph("image/backmap.png");
}
void StageDrawInit(void)
{
	DrawGraph(0, 0, mapImage, true);
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