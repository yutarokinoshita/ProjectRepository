//#pragma once

#define TREASURE_SIZE_X 32
#define TREASURE_SIZE_Y 32

void TreasureInit(void);
void TreasureDraw(void);
bool TreasureGet(XY pPos, int slot);