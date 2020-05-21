//#pragma once

#define ITEM_SIZE_X 32
#define ITEM_SIZE_Y 32
#define DRILL_MOVE	256	// �h�����̔򋗗�
#define DRILL_LIFE	6	// �h�����̑ϋv�l
#define BOMB_COUNT	90	// ���e�̋N���܂ł̎���

void ItemSystemInit(void);
void ItemDrawInit(void);
void ItemControl(void);
void CliateDig(XY Pos,DIR Dir);		// �̌@�A�N�V��������
void CliateDrill(XY Pos, DIR Dir);	// �h��������
void CliateBomb(XY Pos, DIR Dir);	// ���e����
bool CheckItemStock(ITEM Item);		// �A�C�e���g�p�m�F