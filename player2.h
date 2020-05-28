//#pragma once

#define PLAYER_SIZE_2_X 32		// プレイヤー２横サイズ
#define PLAYER_SIZE_2_Y 32		// プレイヤー２縦サイズ
#define SELECT_SIZE_2_X 96		// 2Pのアイテム補充画面横サイズ
#define SELECT_SIZE_2_Y 96		// 2Pのアイテム補充画面縦サイズ

#define PLAYER_DISTANCE_2 32	// 一度の入力でプレイヤー２が移動する距離

void PlayerSystemInit2(void);
void PlayerGameInit2(void);
void PlayerGameDraw2(void);
void PlayerControl2(void);

void PlayerGameDraw2(void);

bool PlayerHitCheck2(XY pos, int size);	// プレイヤー２の当たり判定
void Player2ItemPoint();				// アイテム：ワーム命中時得点入手