#include "DxLib.h"
#include "main.h"
#include "player.h"

CHARACTER player1;	//�v���C���[�P�̍\����

void PlayerSystemInit(void)
{
	player1.pos.x = 200;
	player1.pos.y = 200;

}

void PlayerDrawInit(void)
{
	// ���u���̃v���C���[
	DrawBox(player1.pos.x, player1.pos.y, player1.pos.x + 32, player1.pos.y + 32, GetColor(255, 0, 0), true);
}