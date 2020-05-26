//#pragma once

void soilSystemInit(void);
void soilDrawInit(void);


bool SoilCheckHit(XY dPos,int size,bool Bomb);		// 地形攻撃判定
bool SoilIsPass(XY pPos);		// 地形通過判定
bool SoilIsPass2(XY pPos);		// プレイヤー２地形通過判定