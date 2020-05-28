//#pragma once

#define PLAYER_SIZE_X 32		// プレイヤー横サイズ
#define PLAYER_SIZE_Y 32		// プレイヤー縦サイズ
#define SELECT_SIZE_X 96		// アイテム補充画面横サイズ
#define SELECT_SIZE_Y 96		// アイテム補充画面縦サイズ

#define PLAYER_DISTANCE 32		// 一度の入力で移動する距離

void PlayerSystemInit(void);
void PlayerGameInit(void);
void PlayerGameDraw(void);
void PlayerControl(void);

void PlayerGameDraw(void);

bool PlayerHitCheck(XY pos, int size);	// プレイヤーの当たり判定