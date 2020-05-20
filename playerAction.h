//#pragma once

#define ITEM_SIZE_X 32
#define ITEM_SIZE_Y 32
#define DRILL_MOVE	196	// ドリルの飛距離
#define DRILL_LIFE	6	// ドリルの耐久値
#define BOMB_COUNT	90	// 爆弾の起爆までの時間

void ItemSystemInit(void);
void ItemDrawInit(void);
void ItemControl(void);
void CliateDig(XY Pos,DIR Dir);
void CliateDrill(XY Pos, DIR Dir);
void CliateBomb(XY Pos, DIR Dir);