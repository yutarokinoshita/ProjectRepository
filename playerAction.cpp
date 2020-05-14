#include "DxLib.h"
#include "main.h"
#include "map.h"
#include "playerAction.h"

CHARACTER dig;
bool digAction;		// アクションを行う

void DigSystemInit(void)
{
	dig.pos.x = 0;
	dig.pos.y = 0;
	dig.size.x = 32;
	dig.size.y = 32;
	dig.moveDir = DIR_DOWN;
	digAction = false;
}

void DigControl(void)
{
	if (digAction)
	{
		DrawBox(dig.pos.x, dig.pos.y, dig.pos.x + 32, dig.pos.y + 32, GetColor(255, 255, 255), true);
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
		dig.pos.y = Pos.y + dig.size.y;
		break;
	case DIR_RIGHT:
		dig.pos.x = Pos.x + dig.size.x;
		dig.pos.y = Pos.y;
		break;
	case DIR_UP:
		dig.pos.x = Pos.x;
		dig.pos.y = Pos.y - dig.size.y;
		break;
	case DIR_LEFT:
		dig.pos.x = Pos.x - dig.size.x;
		dig.pos.y = Pos.y;
	default:
		break;
	}
	digAction = true;
}