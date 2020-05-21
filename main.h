//#pragma once

// 定義
#define SCREEN_SIZE_X	800	// 画面サイズ横
#define SCREEN_SIZE_Y	608	// 画面サイズ縦

// 向き管理用
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

// 構造体
struct XY{
	int x;
	int y;
};

// キャラクタ構造体
struct CHARACTER {
	DIR moveDir;		// キャラクタの向き
	DIR oldmoveDir;		// キャラクタの1フレーム前の向き
	XY pos;				// キャラクタ座標
	XY size;			// キャラクタ画像のサイズ
	XY sizeOffset;		// キャラクタの中央から外側まで
	int moveSpeed;		// キャラクタの移動速度
	bool Flag;			// キャラクタの状態の確認
	int life;			// キャラクタのライフ
	int distance;		// キャラクタが移動できる距離
	int AnimCnt;		// キャラクタのアニメーション
	int slot;			// キャラクタの得点アイテム保持数
	int score;			// キャラクタのスコア
	XY effectMoveSpeed;	// キャラクタの特殊な移動
	ITEM item;			// キャラクタの所持アイテム
	int itemStock;		// キャラクタのアイテム所持数
};