//#pragma once

#define STRATA_1	17	// �P�w�܂�
#define STRATA_2	25	// �Q�w�܂�

void SoilSystemInit(void);
void SoilGameInit(void);
void SoilDrawInit(void);


bool SoilCheckHit(XY dPos,int size,bool Bomb);		// �n�`�U������
bool SoilIsPass(XY pPos);		// �n�`�ʉߔ���
bool SoilIsPass2(XY pPos);		// �v���C���[�Q�n�`�ʉߔ���