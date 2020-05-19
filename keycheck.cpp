#include "DxLib.h"
#include "main.h"
#include "keycheck.h"

// �L�[����
bool keyOld[KEY_ID_MAX];	// 1�t���[���O�̃L�[
bool keyNew[KEY_ID_MAX];	// ���݂̃L�[
bool keyDownTrigger[KEY_ID_MAX];	// �L�[�������̃g���K�[
bool keyUpTrigger[KEY_ID_MAX];		// �L�[�𗣂����ۂ̃g���K�[

void keyInit(void)
{
	for (int keyID = 0;keyID < KEY_ID_MAX;keyID++)
	{
		keyOld[keyID] = false;
		keyNew[keyID] = false;	
		keyDownTrigger[keyID] = false;
		keyUpTrigger[keyID] = false;
	}
}

void keyCheck(void)
{
	// 1�t���[���O�̃L�[�����R�s�[
	for (int keyID = 0;keyID < KEY_ID_MAX;keyID++)
	{
		keyOld[keyID] = keyNew[keyID];
	}

	// ���݂̃L�[�����擾����
	keyNew[KEY_ID_SPACE] = CheckHitKey(KEY_INPUT_SPACE);
	keyNew[KEY_ID_P1DOWN] = CheckHitKey(KEY_INPUT_S);
	keyNew[KEY_ID_P1RIGHT] = CheckHitKey(KEY_INPUT_D);
	keyNew[KEY_ID_P1UP] = CheckHitKey(KEY_INPUT_W);
	keyNew[KEY_ID_P1LEFT] = CheckHitKey(KEY_INPUT_A);
	keyNew[KEY_ID_PLAYER_ACTION] = CheckHitKey(KEY_INPUT_Z);
	keyNew[KEY_ID_PLAYER_ITEM] = CheckHitKey(KEY_INPUT_LCONTROL);
	
	// �g���K�[���̎擾
	for (int keyID = 0;keyID < KEY_ID_MAX;keyID++)
	{
		// �g���K�[���̏�����
		keyDownTrigger[keyID] = false;
		keyUpTrigger[keyID] = false;

		if (!keyOld[keyID] && keyNew[keyID])
		{
			keyDownTrigger[keyID] = true;
		}

		if (keyOld[keyID] && !keyNew[keyID])
		{
			keyUpTrigger[keyID] = true;
		}
	}
}