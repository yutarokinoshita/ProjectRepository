//#pragma once

#define ITEM_SIZE_X 32
#define ITEM_SIZE_Y 32
#define DRILL_MOVE	256	// ドリルの飛距離
#define DRILL_LIFE	6	// ドリルの耐久値
#define BOMB_COUNT	90	// 爆弾の起爆までの時間
#define WARM_MAX	6	// ワームの総数

void ItemSystemInit(void);
void ItemGameInit(void);
void ItemDrawInit(void);
void ItemControl(void);
bool WarmControl(XY Pos,int Size);					// ワームの追尾及び奪取処理
void CliateDig(XY Pos,DIR Dir,TYPE Type,int Life);	// 採掘アクション発生
void CliateDrill(XY Pos, DIR Dir);					// ドリル発生
void CliateBomb(XY Pos, DIR Dir);					// 爆弾発生
void CliateWarm(XY Pos);							// ワーム生成

bool CheckItemStock(ITEM Item);						// アイテム使用確認

bool WarmHitCheck(void);							// ワーム当たり判定