//#pragma once

// 定義
#define SCREEN_SIZE_X	800	// 画面サイズ横
#define SCREEN_SIZE_Y	600	// 画面サイズ縦

// 向き管理用
enum DIR {
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
	DIR_MAX
};

// 構造体
struct XY{
	int x;
	int y;
};

// キャラクタ構造体
struct CHARACTER {
	DIR moveDir;		// キャラクタの向き
	XY pos;				// キャラクタ座標
	XY size;			// キャラクタ画像のサイズ
	XY sizeOffset;		// キャラクタの中央から左上まで
	int moveSpeed;
};