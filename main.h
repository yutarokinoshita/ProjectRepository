//#pragma once

// 定義
#define SCREEN_SIZE_X	800	// 画面サイズ横
#define SCREEN_SIZE_Y	608	// 画面サイズ縦
#define ACC_G			10	// 重力加速度	
#define FRAME_TIME		0.2f	// 1フレームの時間

// シーン管理用
enum SCENE_ID
{
	SCENE_ID_INIT,
	SCENE_ID_TITLE,
	SCENE_ID_GAME,
	SCENE_ID_GAMEOVER,
	SCENE_ID_MAX
};
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
	ITEM_RADAR,
	ITEM_WARM,
	ITEM_MAX
};

// 構造体
struct XY{
	int x;
	int y;
};

// 構造体(float)
struct XY_F {
	float x;
	float y;
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
	ITEM item;			// キャラクタの所持アイテム
	int itemStock;		// キャラクタのアイテム所持数

	XY_F velocity;		// キャラクタの速度
};

extern XY mapPos;			// マップ座標

bool SystemInit(void);		// 初期化処理
// 初期化シーン
void InitScene(void);
// タイトルシーン
void TitleScene(void);
void TitleDraw(void);
// ゲームシーン
void GameScene(void);
void GameDraw(void);
// ゲームオーバーシーン
void GameOverScene(void);
void GameOverDraw(void);