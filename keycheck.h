//#pragma once

// �L�[����p
enum KEY_ID {
	KEY_ID_SPACE,
	KEY_ID_P1DOWN,
	KEY_ID_P1RIGHT,
	KEY_ID_P1UP,
	KEY_ID_P1LEFT,
	KEY_ID_PLAYER_ACSION,
	KEY_ID_MAX
};

extern bool keyOld[KEY_ID_MAX];	// 1�t���[���O�̃L�[
extern bool keyNew[KEY_ID_MAX];	// ���݂̃L�[
extern bool keyDownTrigger[KEY_ID_MAX];	// �L�[������
extern bool keyUpTrigger[KEY_ID_MAX];	// �L�[�𗣂�����

void keyInit(void);		// �L�[�z�񏉊�������
void keyCheck(void);	// �L�[���擾����