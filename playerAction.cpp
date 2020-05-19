#include "DxLib.h"
#include "main.h"
#include "map.h"
#include "playerAction.h"
#include "soil.h"

CHARACTER dig;
CHARACTER drill;
bool digAction;		// アクションを行う
int drillImage[8];	// ドリルの画像格納用

void ItemSystemInit(void)
{
	LoadDivGraph("image/drill.png", 8, 2, 4, ITEM_SIZE_X, ITEM_SIZE_Y, drillImage,false);
	dig.pos.x = 0;
	dig.pos.y = 0;
	dig.size.x = ITEM_SIZE_X;
	dig.size.y = ITEM_SIZE_Y;
	dig.sizeOffset.x = ITEM_SIZE_X / 2;
	dig.sizeOffset.y = ITEM_SIZE_Y / 2;
	dig.moveDir = DIR_DOWN;
	digAction = false;

	drill.pos.x = 0;
	drill.pos.y = 0;
	drill.size.x = ITEM_SIZE_X;
	drill.size.y = ITEM_SIZE_Y;
	drill.sizeOffset.x = ITEM_SIZE_X / 2;
	drill.sizeOffset.y = ITEM_SIZE_Y / 2;
	drill.moveDir = DIR_DOWN;
	drill.moveSpeed = 4;
	drill.AnimCnt = 0;
	drill.Flag = false;
}

void ItemDrawInit(void)
{
	drill.AnimCnt++;

	if (digAction)
	{
		DrawBox(dig.pos.x - dig.sizeOffset.x, dig.pos.y - dig.sizeOffset.y, dig.pos.x + dig.sizeOffset.x, dig.pos.y + dig.sizeOffset.y, GetColor(255, 255, 255), true);
	}
	if (drill.Flag)
	{
		DrawGraph(drill.pos.x - drill.sizeOffset.x, drill.pos.y - drill.sizeOffset.y, drillImage[drill.moveDir * 2 + (drill.AnimCnt / 4) % 2],true);
	}
	DrawFormatString(0, 96, GetColor(255, 0, 0), "D.Move:%d", drill.moveDir);
	DrawFormatString(0, 112, GetColor(255, 0, 0), "D.Cnt:%d", drill.AnimCnt);
}

void ItemControl(void)
{
	if (digAction)
	{
		
	
		if (SoilCheckHit(dig.pos))
		{
		}
	}
	digAction = false;

	if (drill.Flag)
	{
		switch (drill.moveDir)
		{
		case DIR_DOWN:
			drill.pos.y += drill.moveSpeed;
			break;
		case DIR_RIGHT:
			drill.pos.x += drill.moveSpeed;
			break;
		case DIR_UP:
			drill.pos.y -= drill.moveSpeed;
			break;
		case DIR_LEFT:
			drill.pos.x -= drill.moveSpeed;
			break;
		default:
			break;
		}
		if (SoilCheckHit(drill.pos))
		{

		}
	}
}

void CliateDig(XY Pos,DIR Dir)
{
	dig.moveDir = Dir;
	switch (dig.moveDir)
	{
	case DIR_DOWN:
		dig.pos.x = Pos.x;
		dig.pos.y = Pos.y + ITEM_SIZE_Y;
		break;
	case DIR_RIGHT:
		dig.pos.x = Pos.x + ITEM_SIZE_X;
		dig.pos.y = Pos.y;
		break;
	case DIR_UP:
		dig.pos.x = Pos.x ;
		dig.pos.y = Pos.y - ITEM_SIZE_Y;
		break;
	case DIR_LEFT:
		dig.pos.x = Pos.x - ITEM_SIZE_X;
		dig.pos.y = Pos.y;
		break;
	default:
		break;
	}
	digAction = true;
}

void CliateDrill(XY Pos, DIR Dir)
{
	drill.moveDir = Dir;
	switch (drill.moveDir)
	{
	case DIR_DOWN:
		drill.pos.x = Pos.x;
		drill.pos.y = Pos.y + ITEM_SIZE_Y;
		break;
	case DIR_RIGHT:
		drill.pos.x = Pos.x + ITEM_SIZE_X;
		drill.pos.y = Pos.y;
		break;
	case DIR_UP:
		drill.pos.x = Pos.x;
		drill.pos.y = Pos.y - ITEM_SIZE_Y;
		break;
	case DIR_LEFT:
		drill.pos.x = Pos.x - ITEM_SIZE_X;
		drill.pos.y = Pos.y;
		break;
	default:
		break;
	}
	drill.Flag= true;
}