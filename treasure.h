//#pragma once

#define TREASURE_SIZE_X 32
#define TREASURE_SIZE_Y 32
#define TREASURE_MAX	100	// �A�C�e���z�u�ő吔

void TreasureSystemInit(void);
void TreasureGameInit(void);
void TreasureDraw(void);
bool TreasureGet(XY pPos, int slot);
void OllTreasure(int slot);
void TreasureSearch(XY pPos,int Time);	// ���[�_�[�p�̏���
int TreasureDistance(XY pPos);	// �v���C���[���ӂ̒T������
bool TreasureYsearch(XY Pos);	// CPU�p���_�A�C�e���̏c�ʒu��T�鏈��
int TreasureXsearch(XY Pos);	// ���_�A�C�e���̉��ʒu��T��ړ�����