#include "DxLib.h"
#include "main.h"
#include "treasure.h"

CHARACTER treasure;
int treasureImage;

void TreasureInit(void)
{
	treasureImage = LoadGraph("image/potato.png");
	treasure.pos.x = 208;
	treasure.pos.y = 208;
	treasure.size.x = TREASURE_SIZE_X;
	treasure.size.y = TREASURE_SIZE_Y;
	treasure.sizeOffset.x = TREASURE_SIZE_X / 2;
	treasure.sizeOffset.y = TREASURE_SIZE_Y / 2;
}

void TreasureDraw(void)
{
	DrawGraph(treasure.pos.x - treasure.sizeOffset.x, treasure.pos.y - treasure.sizeOffset.y, treasureImage, true);
}