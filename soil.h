//#pragma once

void SoilSystemInit(void);
void SoilGameInit(void);
void SoilDrawInit(void);


bool SoilCheckHit(XY dPos,int size,bool Bomb);		// �n�`�U������
bool SoilIsPass(XY pPos);		// �n�`�ʉߔ���
bool SoilIsPass2(XY pPos);		// �v���C���[�Q�n�`�ʉߔ���