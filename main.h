//#pragma once

// ��`
#define SCREEN_SIZE_X	800	// ��ʃT�C�Y��
#define SCREEN_SIZE_Y	608	// ��ʃT�C�Y�c
#define ACC_G			10	// �d�͉����x	
#define FRAME_TIME		0.2f	// 1�t���[���̎���

// �V�[���Ǘ��p
enum SCENE_ID
{
	SCENE_ID_INIT,
	SCENE_ID_TITLE,
	SCENE_ID_GAME,
	SCENE_ID_GAMEOVER,
	SCENE_ID_MAX
};
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
	ITEM_RADAR,
	ITEM_WARM,
	ITEM_MAX
};

// �\����
struct XY{
	int x;
	int y;
};

// �\����(float)
struct XY_F {
	float x;
	float y;
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
	ITEM item;			// �L�����N�^�̏����A�C�e��
	int itemStock;		// �L�����N�^�̃A�C�e��������

	XY_F velocity;		// �L�����N�^�̑��x
};

extern XY mapPos;			// �}�b�v���W

bool SystemInit(void);		// ����������
// �������V�[��
void InitScene(void);
// �^�C�g���V�[��
void TitleScene(void);
void TitleDraw(void);
// �Q�[���V�[��
void GameScene(void);
void GameDraw(void);
// �Q�[���I�[�o�[�V�[��
void GameOverScene(void);
void GameOverDraw(void);