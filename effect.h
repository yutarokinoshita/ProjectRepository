//#pragma once

#define EFFECT_SIZE_X 32	// �G�t�F�N�g���T�C�Y
#define EFFECT_SIZE_Y 32	// �G�t�F�N�g�c�T�C�Y

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
//void TreasureMove(int slot);	// ���_�A�C�e���擾�����[�V����
void ItemEffect(XY Ipos,int Inum,bool Iflag);	// �A�C�e���̏�ɃG�t�F�N�g��\������
void BlastEffect(XY Bpos);