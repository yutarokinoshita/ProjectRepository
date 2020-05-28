//#pragma once

#define EFFECT_SIZE_X 32	// エフェクト横サイズ
#define EFFECT_SIZE_Y 32	// エフェクト縦サイズ

void TreasureEffectInit(void);
void TreasureEffectGameInit(void);
void TreasureEffectDraw(void);
void effectControl(void);
//void TreasureMove(int slot);	// 得点アイテム取得時モーション
void ItemEffect(XY Ipos,int Inum,bool Iflag);	// アイテムの上にエフェクトを表示する