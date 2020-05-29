#include "DxLib.h"
#include "main.h"
#include "treasure.h"
#include "effect.h"

CHARACTER effect[TREASURE_MAX];
int effectImage[3];
bool fadeIn;		// フェードイン
bool fadeOut;		// フェードアウト
int fadeCnt;		// フェード用

void TreasureEffectInit(void)
{
	LoadDivGraph("image/effect.png", 3, 3, 1, EFFECT_SIZE_X, EFFECT_SIZE_Y, effectImage, false);
}

void TreasureEffectGameInit(void)
{
	// フェード初期化
	fadeIn = true;
	fadeOut = false;
	fadeCnt = 0;

	for (int ef = 0;ef < TREASURE_MAX;ef++)
	{
		effect[ef].pos.x = 0;
		effect[ef].pos.y = 0;
		effect[ef].size.x = EFFECT_SIZE_X;
		effect[ef].size.y = EFFECT_SIZE_Y;
		effect[ef].sizeOffset.x = EFFECT_SIZE_X / 2;
		effect[ef].sizeOffset.y = EFFECT_SIZE_Y / 2;
		effect[ef].Flag = true;
		effect[ef].AnimCnt = 0;
	}
}

bool FadeInSceen(int fadeStep)
{
	if (fadeCnt <= 255)
	{
		SetDrawBright(fadeCnt, fadeCnt, fadeCnt);
		fadeCnt += fadeStep;
		return true;
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
void ItemEffect(XY Ipos,int Inum,bool Iflag)
{
	//for (int ef = 0;ef < TREASURE_MAX;ef++)
	//{
		effect[Inum].pos = Ipos;
		effect[Inum].Flag = Iflag;
	//	break;
	//}
}