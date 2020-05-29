//#pragma once

#define TREASURE_SIZE_X 32
#define TREASURE_SIZE_Y 32
#define TREASURE_MAX	100	// アイテム配置最大数

void TreasureSystemInit(void);
void TreasureGameInit(void);
void TreasureDraw(void);
bool TreasureGet(XY pPos, int slot);
void OllTreasure(int slot);
void TreasureSearch(XY pPos,int Time);	// レーダー用の処理
int TreasureDistance(XY pPos);	// プレイヤー周辺の探索処理
bool TreasureYsearch(XY Pos);	// CPU用得点アイテムの縦位置を探る処理
int TreasureXsearch(XY Pos);	// 得点アイテムの横位置を探り移動する