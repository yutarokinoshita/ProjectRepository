//#pragma once

// ��`
#define SCREEN_SIZE_X	800	// ��ʃT�C�Y��
#define SCREEN_SIZE_Y	608	// ��ʃT�C�Y�c

// �����Ǘ��p
enum DIR {
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
	DIR_MAX
};

enum ITEM {
	ITEM_DRILL,
	ITEM_BOMB,
	ITEM_CALL,
	ITEM_MAX
};

// �\����
struct XY{
	int x;
	int y;
};

// �L�����N�^�\����
struct CHARACTER {
	DIR moveDir;		// �L�����N�^�̌���
	DIR oldmoveDir;		// �L�����N�^��1�t���[���O�̌���
	XY pos;				// �L�����N�^���W
	XY size;			// �L�����N�^�摜�̃T�C�Y
	XY sizeOffset;		// �L�����N�^�̒�������O���܂�
	int moveSpeed;		// �L�����N�^�̈ړ����x
	bool Flag;			// �L�����N�^�̏�Ԃ̊m�F
	int life;			// �L�����N�^�̃��C�t
	int distance;		// �L�����N�^���ړ��ł��鋗��
	int AnimCnt;		// �L�����N�^�̃A�j���[�V����
	int slot;			// �L�����N�^�̓��_�A�C�e���ێ���
	int score;			// �L�����N�^�̃X�R�A
	XY effectMoveSpeed;	// �L�����N�^�̓���Ȉړ�
	ITEM item;			// �L�����N�^�̏����A�C�e��
	int itemStock;		// �L�����N�^�̃A�C�e��������
};