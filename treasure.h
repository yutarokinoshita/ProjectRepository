//#pragma once

#define TREASURE_SIZE_X 32
#define TREASURE_SIZE_Y 32
#define TREASURE_MAX	30	// �A�C�e���z�u�ő吔

void TreasureInit(void);
void TreasureDraw(void);
bool TreasureGet(XY pPos, int slot);
void OllTreasure(int slot);
void TreasureSearch(XY pPos,int Time);	// ���[�_�[�p�̏���
int TreasureDistance(XY pPos);	// �v���C���[���ӂ̒T������