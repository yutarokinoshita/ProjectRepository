//#pragma once

#define PLAYER_SIZE_2_X 32		// �v���C���[�Q���T�C�Y
#define PLAYER_SIZE_2_Y 32		// �v���C���[�Q�c�T�C�Y
#define SELECT_SIZE_2_X 96		// 2P�̃A�C�e����[��ʉ��T�C�Y
#define SELECT_SIZE_2_Y 96		// 2P�̃A�C�e����[��ʏc�T�C�Y

#define PLAYER_DISTANCE_2 32	// ��x�̓��͂Ńv���C���[�Q���ړ����鋗��

void PlayerSystemInit2(void);
void PlayerGameInit2(void);
void PlayerGameDraw2(void);
void PlayerControl2(void);

void PlayerGameDraw2(void);

bool PlayerHitCheck2(XY pos, int size);	// �v���C���[�Q�̓����蔻��
void Player2ItemPoint();				// �A�C�e���F���[�����������_����