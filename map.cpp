#include <DxLib.h>
#include "main.h"
#include "map.h"

int mapImage;							// �w�i�摜
int cloudImage;							// �_�摜
int gloundImage;						// �n�ʂ̉摜
XY cloud[CLOUD_MAX];					// �_���W
int cloudMoveCnt;						// �_�̈ړ�
//int soilImage[7];		
//CHARACTER soil[MAP_SIZE_X][MAP_SIZE_Y];
XY mapPos;

void StageSystemInit(void)
{
	mapImage = LoadGraph("image/backmap.png");
	cloudImage = LoadGraph("image/cloud.png");
	gloundImage = LoadGraph("image/gloundTile.png");

}

void StageGameInit(void)
{
	for (int clo = 0;clo < CLOUD_MAX;clo++)
	{
		cloud[clo].x = 0 + CLOUD_SIZE_X * clo;
		cloud[clo].y = 32;
	}
	cloudMoveCnt = 0;
}

void StageDrawInit(void)
{
	cloudMoveCnt++;
	DrawGraph(0, -mapPos.y, mapImage, true);
	for (int clo = 0;clo < CLOUD_MAX;clo++)
	{
		DrawGraph(cloud[clo].x, -mapPos.y + cloud[clo].y, cloudImage, true);
		if (cloudMoveCnt % 8 == 0)
		{
			cloud[clo].x--;
		}
		if (cloud[clo].x <= -CLOUD_SIZE_X)
		{
			cloud[clo].x = SCREEN_SIZE_X;
		}
	}
	for (int x = 0;x < MAP_SIZE_X;x++)
	{
		for (int y = 0;y < MAP_SIZE_Y;y++)
		{
			DrawGraph(0 + CHIP_SIZE_X * x, -mapPos.y + 128 + CHIP_SIZE_Y * y, gloundImage, true);
		}
	}
}