//#pragma once

#define PLAYER_SIZE_X 32		// �v���C���[���T�C�Y
#define PLAYER_SIZE_Y 32		// �v���C���[�c�T�C�Y
#define SELECT_SIZE_X 96		// �A�C�e����[��ʉ��T�C�Y
#define SELECT_SIZE_Y 96		// �A�C�e����[��ʏc�T�C�Y

#define PLAYER_DISTANCE 32		// ��x�̓��͂ňړ����鋗��
#define DASH_START	16			// �_�b�V�����n�߂�܂ł̎���

void PlayerSystemInit(void);

void PlayerGameDraw(void);
void PlayerControl(void);

void PlayerGameDraw(void);
