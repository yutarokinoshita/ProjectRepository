//#pragma once

#define EFFECT_SIZE_X 32	// �G�t�F�N�g���T�C�Y
#define EFFECT_SIZE_Y 32	// �G�t�F�N�g�c�T�C�Y

void TreasureEffectInit(void);
void TreasureEffectGameInit(void);
void TreasureEffectDraw(void);
void effectControl(void);
//void TreasureMove(int slot);	// ���_�A�C�e���擾�����[�V����
void ItemEffect(XY Ipos,int Inum,bool Iflag);	// �A�C�e���̏�ɃG�t�F�N�g��\������