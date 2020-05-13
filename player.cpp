#include "DxLib.h"
#include "main.h"
#include "player.h"

CHARACTER player1;	//プレイヤー１の構造体

void PlayerSystemInit(void)
{
	player1.pos.x = 200;
	player1.pos.y = 200;

}

void PlayerDrawInit(void)
{
	// 仮置きのプレイヤー
	DrawBox(player1.pos.x, player1.pos.y, player1.pos.x + 32, player1.pos.y + 32, GetColor(255, 0, 0), true);
}