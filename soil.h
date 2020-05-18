//#pragma once

void soilSystemInit(void);
void soilDrawInit(void);


bool SoilCheckHit(XY dPos, int dSize);		// 地形攻撃判定
bool SoilIsPass(XY pPos);		// 地形通過判定