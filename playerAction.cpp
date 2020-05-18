#include "DxLib.h"
#include "main.h"
#include "map.h"
#include "playerAction.h"
#include "soil.h"

CHARACTER dig;
bool digAction;		// アクションを行う

void DigSystemInit(void)
{
	dig.pos.x = 0;
	dig.pos.y = 0;
	dig.size.x = DIG_SIZE_X;
	dig.size.y = DIG_SIZE_Y;
	dig.sizeOffset.x = DIG_SIZE_X / 2;
	dig.sizeOffset.y = DIG_SIZE_Y / 2;
	dig.moveDir = DIR_DOWN;
	digAction = false;
}

void DigControl(void)
{
	if (digAction)
	{
		DrawBox(dig.pos.x-dig.sizeOffset.x, dig.pos.y-dig.sizeOffset.y, dig.pos.x + dig.sizeOffset.x, dig.pos.y + dig.sizeOffset.y, GetColor(255, 255, 255), true);
	
		if (SoilCheckHit(dig.pos))
		{

		}
	}

	digAction = false;
}

void CliateDig(XY Pos,DIR Dir)
{
	dig.moveDir = Dir;
	switch (dig.moveDir)
	{
	case DIR_DOWN:
		dig.pos.x = Pos.x;
		dig.pos.y = Pos.y + DIG_SIZE_Y;
		break;
	case DIR_RIGHT:
		dig.pos.x = Pos.x + DIG_SIZE_X;
		dig.pos.y = Pos.y;
		break;
	case DIR_UP:
		dig.pos.x = Pos.x ;
		dig.pos.y = Pos.y - DIG_SIZE_Y;
		break;
	case DIR_LEFT:
		dig.pos.x = Pos.x - DIG_SIZE_X;
		dig.pos.y = Pos.y;
	default:
		break;
	}
	digAction = true;
}