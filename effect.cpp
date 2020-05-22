#include "DxLib.h"
#include "main.h"
#include "treasure.h"
#include "effect.h"

CHARACTER effect[TREASURE_MAX];
int effectImage[3];
//int MoveCnt;		// 移動時間

void TreasureEffectInit(void)
{
	LoadDivGraph("image/effect.png", 3, 3, 1, EFFECT_SIZE_X, EFFECT_SIZE_Y, effectImage, false);
	for (int ef = 0;ef < TREASURE_MAX;ef++)
	{
		effect[ef].pos.x = 0;
		effect[ef].pos.y = 0;
		effect[ef].size.x = EFFECT_SIZE_X;
		effect[ef].size.y = EFFECT_SIZE_Y;
		effect[ef].sizeOffset.x = EFFECT_SIZE_X / 2;
		effect[ef].sizeOffset.y = EFFECT_SIZE_Y / 2;
		effect[ef].Flag = false;
		effect[ef].AnimCnt = 0;
	}
}

void TreasureEffectDraw(void)
{
	for (int ef = 0;ef < TREASURE_MAX;ef++)
	{
		effect[ef].AnimCnt++;
		if (!effect[ef].Flag)
		{
			DrawGraph(-mapPos.x + effect[ef].pos.x - effect[ef].sizeOffset.x, -mapPos.y + effect[ef].pos.y - effect[ef].sizeOffset.y, effectImage[(effect[ef].AnimCnt / 10) % 3], true);
		}
	}
}

void effectControl(void)
{
}

// アイテムの上にエフェクトを表示する
void ItemEffect(XY Ipos)
{
	for (int ef = 0;ef < TREASURE_MAX;ef++)
	{
		effect[ef].pos = Ipos;
		break;
	}
}

// 仮の処理　必要なければ消去可
// 得点アイテム取得時モーション
//void TreasureMove(int slot)
//{
//	for (int ef = 0;ef < TREASURE_MAX;ef++)
//	{
//		if (!treasureEffect[ef].Flag)
//		{
//			treasureEffect[ef].pos.x = 32 + 32 * slot;
//			treasureEffect[ef].pos.y = 32;
//			treasureEffect[ef].Flag = true;
//			break;
//		}
//	}
//}