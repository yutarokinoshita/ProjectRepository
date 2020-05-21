#include "DxLib.h"
#include "main.h"
#include "map.h"
#include "player.h"
#include "playerAction.h"
#include "soil.h"

CHARACTER dig;
CHARACTER drill;
CHARACTER bomb;
int drillImage[8];	// ドリルの画像格納用
int bombImage[6];	// 爆弾の画像格納用
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
	dig.Flag = false;

	drill.pos.x = 0;
	drill.pos.y = 0;
	drill.size.x = ITEM_SIZE_X;
	drill.size.y = ITEM_SIZE_Y;
	drill.sizeOffset.x = ITEM_SIZE_X / 2;
	drill.sizeOffset.y = ITEM_SIZE_Y / 2;
	drill.moveDir = DIR_DOWN;
	drill.moveSpeed = 4;
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
	bomb.moveSpeed = 8;
	bomb.distance = 0;
	bomb.life = 0;
	bomb.AnimCnt = 0;
	bomb.Flag = false;
}

void ItemDrawInit(void)
{
	drill.AnimCnt++;

	//if (dig.Flag)
	//{
	//	DrawBox(dig.pos.x - dig.sizeOffset.x, dig.pos.y - dig.sizeOffset.y, dig.pos.x + dig.sizeOffset.x, dig.pos.y + dig.sizeOffset.y, GetColor(255, 255, 255), true);
	//}
	if (drill.Flag)
	{
		DrawGraph(drill.pos.x - drill.sizeOffset.x, -mapPos.y + drill.pos.y - drill.sizeOffset.y, drillImage[drill.moveDir * 2 + (drill.AnimCnt / 4) % 2],true);
	}
	if (bomb.Flag)
	{
		DrawGraph(bomb.pos.x - bomb.sizeOffset.x, -mapPos.y + bomb.pos.y - bomb.sizeOffset.y, bombImage[bomb.life / 15 % 6], true);
	}
	else
	{
		DrawBox(bomb.pos.x - bomb.sizeOffset.x - ITEM_SIZE_X, -mapPos.y + bomb.pos.y - bomb.sizeOffset.y - ITEM_SIZE_Y,
			bomb.pos.x + bomb.sizeOffset.x + ITEM_SIZE_X, -mapPos.y + bomb.pos.y + bomb.sizeOffset.y + ITEM_SIZE_Y, GetColor(0, 0, 255), false);
	}
	DrawFormatString(0, 96, GetColor(255, 0, 0), "D.Move:%d", drill.moveDir);
	DrawFormatString(0, 112, GetColor(255, 0, 0), "D.Cnt:%d", drill.AnimCnt);
}

void ItemControl(void)
{
	if (dig.Flag)
	{
		if (SoilCheckHit(dig.pos,dig.sizeOffset.x,false))
		{
		}
	}


	if (drill.Flag)
	{
		drill.distance -= drill.moveSpeed;
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
		if (SoilCheckHit(drill.pos,drill.sizeOffset.x,false))
		{
			drill.life--;
		}
		// 画面外へ出るか指定距離移動するか耐久値がなくなった場合消える
		if (drill.pos.x > SCREEN_SIZE_X + drill.sizeOffset.x
			|| -mapPos.y + drill.pos.y > SCREEN_SIZE_Y + drill.sizeOffset.y
			|| drill.pos.x < 0
			|| -mapPos.y + drill.pos.y < 0
			)//|| drill.distance <= 0
			//|| drill.life <= 0)
		{
			drill.Flag = false;
		}
	}

	if (bomb.Flag)
	{
		bomb.life--;
		if (bomb.pos.x<dig.pos.x + dig.sizeOffset.x
			&& bomb.pos.x>dig.pos.x - dig.sizeOffset.x
			&& bomb.pos.y<dig.pos.y + dig.sizeOffset.y
			&& bomb.pos.y>dig.pos.y - dig.sizeOffset.y
			&& dig.Flag)
		{
			bomb.moveDir = dig.moveDir;
			bomb.life -= BOMB_COUNT * 2 / 3;
			bomb.distance = 32;
		}
		if (bomb.distance > 0 && bomb.life > 0)
		{
			switch (bomb.moveDir)
			{
			case DIR_UP:
				bomb.distance -= bomb.moveSpeed;
				bomb.pos.y -= bomb.moveSpeed;
				break;
			case DIR_RIGHT:
				bomb.distance -= bomb.moveSpeed;
				bomb.pos.x += bomb.moveSpeed;
				break;
			case DIR_DOWN:
				bomb.distance -= bomb.moveSpeed;
				bomb.pos.y += bomb.moveSpeed;
				break;
			case DIR_LEFT:
				bomb.distance -= bomb.moveSpeed;
				bomb.pos.x -= bomb.moveSpeed;
				break;
			default:
				break;
			}
		}
		if (bomb.life <= 0)
		{
			for (int hit = 0;hit <= 9;hit++)
			{
				SoilCheckHit(bomb.pos, bomb.sizeOffset.x + ITEM_SIZE_X,true);
				PlayerHitCheck(bomb.pos, bomb.sizeOffset.x + ITEM_SIZE_X);
				bomb.distance = 0;
				bomb.Flag = false;
			}
		}
	}
	dig.Flag = false;
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
	dig.Flag = true;
}

void CliateDrill(XY Pos, DIR Dir)
{
	if (!drill.Flag)
	{
		drill.moveDir = Dir;
		drill.distance = DRILL_MOVE;
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
		drill.Flag = true;
	}
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

// アイテム使用確認
bool CheckItemStock(ITEM Item)
{
	switch (Item)
	{
	case ITEM_DRILL:
		if (!drill.Flag)
		{
			return true;
		}
		break;
	case ITEM_BOMB:
		if (!bomb.Flag)
		{
			return true;
		}
		break;
	case ITEM_CALL:
		return true;
		break;
	case ITEM_MAX:
		break;
	default:
		break;
	}
	return false;
}