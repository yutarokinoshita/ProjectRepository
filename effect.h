//#pragma once

#define EFFECT_SIZE_X 32	// エフェクト横サイズ
#define EFFECT_SIZE_Y 32	// エフェクト縦サイズ

<<<<<<< HEAD
void EffectInit(void);
void EffectGameInit(void);
void FadeInit(void);
int FadeInScreen(int fadeCnt);
int FadeOutScreen(int fadeStep);
void EffectDraw(void);
void EffectControl(void);
=======
void TreasureEffectInit(void);
void TreasureEffectGameInit(void);
void FadeInit(void);
int FadeInScreen(int fadeCnt);
int FadeOutScreen(int fadeStep);
void TreasureEffectDraw(void);
void effectControl(void);
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
//void TreasureMove(int slot);	// 得点アイテム取得時モーション
void ItemEffect(XY Ipos,int Inum,bool Iflag);	// アイテムの上にエフェクトを表示する
void BlastEffect(XY Bpos);