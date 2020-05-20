//#pragma once

#define ITEM_SIZE_X 32
#define ITEM_SIZE_Y 32
#define DRILL_MOVE	196	// ƒhƒŠƒ‹‚Ì”ò‹——£
#define DRILL_LIFE	6	// ƒhƒŠƒ‹‚Ì‘Ï‹v’l

void ItemSystemInit(void);
void ItemDrawInit(void);
void ItemControl(void);
void CliateDig(XY Pos,DIR Dir);
void CliateDrill(XY Pos, DIR Dir);