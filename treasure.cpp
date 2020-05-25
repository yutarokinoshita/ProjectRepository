#include "DxLib.h"
#include "main.h"
#include "treasure.h"
#include "map.h"
#include "effect.h"

CHARACTER treasure[TREASURE_MAX];
int treasureImage;
//bool treasureFlag;
int treasureReset;		// �A�C�e�����c���Ă��邩�̔c���p

// �A�C�e������������
void TreasureInit(void)
{
	treasureImage = LoadGraph("image/potato.png");
	for (int x = 0;x < TREASURE_MAX;x++)
	{	
		treasure[x].pos.x = 16 + TREASURE_SIZE_X * GetRand(25);
		treasure[x].pos.y = 144 + TREASURE_SIZE_Y * GetRand(13);
		treasure[x].size.x = TREASURE_SIZE_X;
		treasure[x].size.y = TREASURE_SIZE_Y;
		treasure[x].sizeOffset.x = TREASURE_SIZE_X / 2;
		treasure[x].sizeOffset.y = TREASURE_SIZE_Y / 2;
		treasure[x].Flag = false;
		treasure[x].moveSpeed = 0;
		treasureReset = 0;
	}
}

// �A�C�e���`��
void TreasureDraw(void)
{
	for (int x = 0;x < TREASURE_MAX;x++)
	{
		if(!treasure[x].Flag)//if (!treasureFlag)
		{
			DrawGraph(treasure[x].pos.x - treasure[x].sizeOffset.x, -mapPos.y + treasure[x].pos.y - treasure[x].sizeOffset.y, treasureImage, true);
		}
	}
}

// �A�C�e�����l�����鏈��
bool TreasureGet(XY pPos,int slot)
{
	for (int x = 0;x < TREASURE_MAX;x++)
	{
		if (!treasure[x].Flag)//if (!treasureFlag)
		{
			if (treasure[x].pos.x - treasure[x].sizeOffset.x < pPos.x
				&& treasure[x].pos.x + treasure[x].sizeOffset.x > pPos.x
				&& treasure[x].pos.y - treasure[x].sizeOffset.y  < pPos.y
				&& treasure[x].pos.y + treasure[x].sizeOffset.y  > pPos.y)
			{
				if (slot <= 2)
				{
					//TreasureMove(slot);
					treasure[x].Flag = true;
					//treasureFlag = true;
					return true;
				}
			}
		}
	}
	return false;
}

// �A�C�e�����擾�����v�Z���鏈��
void OllTreasure(int slot)
{
	treasureReset += slot;
}

// �A�C�e�����[�_�[�p�̏���
void TreasureSearch(XY pPos,int Time)
{
	int TreX;
	int TreY;
	int TreXY;

	for (int x = 0;x < TREASURE_MAX;x++)
	{
		if (pPos.x > treasure[x].pos.x)
		{
				TreX = (pPos.x - treasure[x].pos.x) / 32;
		}
		else
		{
			TreX = (treasure[x].pos.x - pPos.x) / 32;
		}
			if (pPos.y > treasure[x].pos.y)
		{
			TreY = (pPos.y - treasure[x].pos.y) / 32;
		}
		else
		{
			TreY = (treasure[x].pos.y - pPos.y) / 32;
		}
		TreXY = TreX + TreY;
		if (TreXY <= 6)
		{
			ItemEffect(treasure[x].pos, x, treasure[x].Flag);
		}
		if (Time <= 0)
		{
			ItemEffect(treasure[x].pos, x, true);
		}
	}
}

// �v���C���[���ӂ̒T������
int TreasureDistance(XY pPos)
{
	int TreX;
	int TreY;
	int TreXY;
	int TreMin = 4;

	for (int x = 0;x < TREASURE_MAX;x++)
	{
		if (!treasure[x].Flag)
		{
			if (pPos.x > treasure[x].pos.x)
			{
				TreX = (pPos.x - treasure[x].pos.x) / 32;
			}
			else
			{
				TreX = (treasure[x].pos.x - pPos.x) / 32;
			}
			if (pPos.y > treasure[x].pos.y)
			{
				TreY = (pPos.y - treasure[x].pos.y) / 32;
			}
			else
			{
				TreY = (treasure[x].pos.y - pPos.y) / 32;
			}
			TreXY = TreX + TreY;
			if (TreXY < TreMin)
			{
				TreMin = TreXY;
				if (TreMin <= 0)
				{
					TreMin = 1;
				}
			}
		}
		else
		{
			TreXY=4;
		}
	}
	return TreMin;
}