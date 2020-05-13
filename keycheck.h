//#pragma once

// キー制御用
enum KEY_ID {
	KEY_ID_SPACE,
	KEY_ID_P1DOWN,
	KEY_ID_P1RIGHT,
	KEY_ID_P1UP,
	KEY_ID_P1LEFT,
	KEY_ID_PLAYER_ACSION,
	KEY_ID_MAX
};

extern bool keyOld[KEY_ID_MAX];	// 1フレーム前のキー
extern bool keyNew[KEY_ID_MAX];	// 現在のキー
extern bool keyDownTrigger[KEY_ID_MAX];	// キー押下時
extern bool keyUpTrigger[KEY_ID_MAX];	// キーを離した時

void keyInit(void);		// キー配列初期化処理
void keyCheck(void);	// キー情報取得処理