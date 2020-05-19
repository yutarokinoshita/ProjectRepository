#include "DxLib.h"
#include "main.h"
#include "keycheck.h"

// キー制御
bool keyOld[KEY_ID_MAX];	// 1フレーム前のキー
bool keyNew[KEY_ID_MAX];	// 現在のキー
bool keyDownTrigger[KEY_ID_MAX];	// キー押下時のトリガー
bool keyUpTrigger[KEY_ID_MAX];		// キーを離した際のトリガー

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
	// 1フレーム前のキー情報をコピー
	for (int keyID = 0;keyID < KEY_ID_MAX;keyID++)
	{
		keyOld[keyID] = keyNew[keyID];
	}

	// 現在のキー情報を取得する
	keyNew[KEY_ID_SPACE] = CheckHitKey(KEY_INPUT_SPACE);
	keyNew[KEY_ID_P1DOWN] = CheckHitKey(KEY_INPUT_S);
	keyNew[KEY_ID_P1RIGHT] = CheckHitKey(KEY_INPUT_D);
	keyNew[KEY_ID_P1UP] = CheckHitKey(KEY_INPUT_W);
	keyNew[KEY_ID_P1LEFT] = CheckHitKey(KEY_INPUT_A);
	keyNew[KEY_ID_PLAYER_ACTION] = CheckHitKey(KEY_INPUT_Z);
	keyNew[KEY_ID_PLAYER_ITEM] = CheckHitKey(KEY_INPUT_LCONTROL);
	
	// トリガー情報の取得
	for (int keyID = 0;keyID < KEY_ID_MAX;keyID++)
	{
		// トリガー情報の初期化
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