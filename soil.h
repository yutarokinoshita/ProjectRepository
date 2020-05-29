//#pragma once

#define STRATA_1	17	// １層まで
#define STRATA_2	25	// ２層まで

void SoilSystemInit(void);
void SoilGameInit(void);
void SoilDrawInit(void);


bool SoilCheckHit(XY dPos,int size,bool Bomb);		// 地形攻撃判定
bool SoilIsPass(XY pPos);		// 地形通過判定
bool SoilIsPass2(XY pPos);		// プレイヤー２地形通過判定