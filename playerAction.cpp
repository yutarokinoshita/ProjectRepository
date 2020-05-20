#include "DxLib.h"
#include "main.h"
#include "map.h"
#include "playerAction.h"
#include "soil.h"

CHARACTER dig;
CHARACTER drill;
CHARACTER bomb;
bool digAction;		// ÉAÉNÉVÉáÉìÇçsÇ§
int drillImage[8];	// ÉhÉäÉãÇÃâÊëúäiî[óp
int bombImage[6];	// îöíeÇÃâÊëúäiî[óp
void ItemSystemInit(void)
{
	LoadDivGraph("image/drill.png", 8, 2, 4, ITEM_SIZE_X, ITEM_SIZE_Y, drillImage,false);
	LoadDivGraph("image/bomb.png", 6, 6, 1, ITEM_SIZE_X, ITEM_SIZE_Y, bombImage, false);
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
	drill.moveSpeed = 0;
	drill.distance = 0;
	drill.life = 0;
	drill.AnimCnt = 0;
	drill.Flag = false;

	bomb.pos.x = 0;
	bomb.pos.y = 0;
	bomb.size.x = ITEM_SIZE_X;
	bomb.size.y = ITEM_SIZE_Y;
	bomb.sizeOffset.x = ITEM_SIZE_X / 2;
	bomb.sizeOffset.y = ITEM_SIZE_Y / 2;
	bomb.moveDir = DIR_DOWN;
	bomb.moveSpeed = 0;
	bomb.distance = 0;
	bomb.life = 0;
	bomb.AnimCnt = 0;
	bomb.Flag = false;
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
		//DrawGraph(drill.pos.x - drill.sizeOffset.x, drill.pos.y - drill.sizeOffset.y, drillImage[drill.moveDir * 2 + (drill.AnimCnt / 4) % 2],true);
	}
	if (bomb.Flag)
	{
		DrawGraph(bomb.pos.x - bomb.sizeOffset.x, bomb.pos.y - bomb.sizeOffset.y, bombImage[bomb.life / 15 % 6], true);
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
			drill.life--;
		}
	}

	if (bomb.Flag)
	{
		bomb.life--;
		if (bomb.life <= 0)
		{
			bomb.Flag = false;
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
	drill.distance = DRILL_MOVE;
	drill.life = DRILL_LIFE;
	drill.Flag= true;
}

void CliateBomb(XY Pos, DIR Dir)
{
	bomb.moveDir = Dir;
	switch (bomb.moveDir)
	{
	case DIR_DOWN:
		bomb.pos.x = Pos.x;
		bomb.pos.y = Pos.y + ITEM_SIZE_Y;
		break;
	case DIR_RIGHT:
		bomb.pos.x = Pos.x + ITEM_SIZE_X;
		bomb.pos.y = Pos.y;
		break;
	case DIR_UP:
		bomb.pos.x = Pos.x;
		bomb.pos.y = Pos.y - ITEM_SIZE_Y;
		break;
	case DIR_LEFT:
		bomb.pos.x = Pos.x - ITEM_SIZE_X;
		bomb.pos.y = Pos.y;
		break;
	default:
		break;
	}
	bomb.life = BOMB_COUNT;
	bomb.Flag = true;
}