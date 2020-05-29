//#pragma once

#define ITEM_SIZE_X 32
#define ITEM_SIZE_Y 32
#define DRILL_MOVE	256	// �h�����̔򋗗�
#define DRILL_LIFE	6	// �h�����̑ϋv�l
#define BOMB_COUNT	90	// ���e�̋N���܂ł̎���
#define WARM_MAX	6	// ���[���̑���

void ItemSystemInit(void);
void ItemGameInit(void);
void ItemDrawInit(void);
void ItemControl(void);
bool WarmControl(XY Pos,int Size);					// ���[���̒ǔ��y�ђD�揈��
void CliateDig(XY Pos,DIR Dir,TYPE Type,int Life);	// �̌@�A�N�V��������
void CliateDrill(XY Pos, DIR Dir);					// �h��������
void CliateBomb(XY Pos, DIR Dir);					// ���e����
void CliateWarm(XY Pos);							// ���[������

bool CheckItemStock(ITEM Item);						// �A�C�e���g�p�m�F

bool WarmHitCheck(void);							// ���[�������蔻��