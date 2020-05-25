//#pragma once

#define TREASURE_SIZE_X 32
#define TREASURE_SIZE_Y 32
#define TREASURE_MAX	30	// アイテム配置最大数

void TreasureInit(void);
void TreasureDraw(void);
bool TreasureGet(XY pPos, int slot);
void OllTreasure(int slot);
void TreasureSearch(XY pPos,int Time);	// レーダー用の処理
int TreasureDistance(XY pPos);	// プレイヤー周辺の探索処理