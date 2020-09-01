#include <DxLib.h>
#include <math.h>
#include "main.h"
#include "treasure.h"
#include "effect.h"

CHARACTER effect[TREASURE_MAX];
int effectImage[3];
bool fadeIn;		// �t�F�[�h�C��
bool fadeOut;		// �t�F�[�h�A�E�g
int fadeCnt;		// �t�F�[�h�p
int kaboomImage[2];	// �����G�t�F�N�g�摜
CHARACTER bomEffect;	// ���j�G�t�F�N�g�̍\����

void EffectInit(void)
{
	LoadDivGraph("image/effect.png", 3, 3, 1, EFFECT_SIZE_X, EFFECT_SIZE_Y, effectImage, false);
	// ���j�G�t�F�N�g
	LoadDivGraph("image/kaboom.png", 2, 2, 1, 96, 96, kaboomImage, false);
}

void EffectGameInit(void)
{
	for (int ef = 0; ef < TREASURE_MAX; ef++)
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
	bomEffect.pos = { 0,0 };
	bomEffect.size.x = 96;
	bomEffect.size.y = 96;
	bomEffect.sizeOffset.x = 96 / 2;
	bomEffect.sizeOffset.y = 96 / 2;
	bomEffect.Flag = false;
	bomEffect.AnimCnt = 0;
}

void FadeInit(void)
{
	// �t�F�[�h������
	fadeIn = true;
	fadeOut = false;
	fadeCnt = 0;
}

// �t�F�[�h�C������
int FadeInScreen(int fadeStep)
{
	//if (fadeCnt >= 255)
	//{
	//	fadeCnt = 0;
	//}
	if (fadeCnt <= 255)
	{
		SetDrawBright(fadeCnt, fadeCnt, fadeCnt);
		fadeCnt += fadeStep;
	}
	return fadeCnt;
}

// �t�F�[�h�A�E�g����
int FadeOutScreen(int fadeStep)
{
	if (fadeCnt <= 255)
	{
		SetDrawBright(255 - fadeCnt, 255 - fadeCnt, 255 - fadeCnt);
		fadeCnt += fadeStep;
	}
	return fadeCnt;
}


void EffectDraw(void)
{
	for (int ef = 0;ef < TREASURE_MAX;ef++)
	{
		effect[ef].AnimCnt++;
		if (!effect[ef].Flag)
		{
			DrawGraph(-mapPos.x + effect[ef].pos.x - effect[ef].sizeOffset.x, -mapPos.y + effect[ef].pos.y - effect[ef].sizeOffset.y, effectImage[(effect[ef].AnimCnt / 10) % 3], true);
		}
	}
	if (bomEffect.Flag)
	{
		DrawGraph(-mapPos.x + bomEffect.pos.x - bomEffect.sizeOffset.x, -mapPos.y + bomEffect.pos.y - bomEffect.sizeOffset.y,
			kaboomImage[bomEffect.AnimCnt / 10 % 2], true);
	}
}

void EffectControl(void)
{
	if (bomEffect.Flag)
	{
		bomEffect.AnimCnt++;
		if (bomEffect.AnimCnt >= 30)
		{
			bomEffect.Flag = false;
		}
	}
}

// �A�C�e���̏�ɃG�t�F�N�g��\������
void ItemEffect(XY Ipos,int Inum,bool Iflag)
{
	//for (int ef = 0;ef < TREASURE_MAX;ef++)
	//{
		effect[Inum].pos = Ipos;
		effect[Inum].Flag = Iflag;
	//	break;
	//}
}

void BlastEffect(XY Bpos)
{
	if (!bomEffect.Flag)
	{
		bomEffect.pos.x = Bpos.x;// -bomEffect.sizeOffset.x;
		bomEffect.pos.y = Bpos.y;// -bomEffect.sizeOffset.y;
		bomEffect.AnimCnt = 0;
		bomEffect.Flag = true;
	}
}