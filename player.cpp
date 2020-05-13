#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "keycheck.h"

CHARACTER player1;	//�v���C���[�P�̍\����

void PlayerSystemInit(void)
{
	player1.pos.x = 200;
	player1.pos.y = 200;
	player1.moveDir = DIR_DOWN;
}

void PlayerDrawInit(void)
{
	// ���u���̃v���C���[
	if (player1.moveDir == DIR_DOWN)
	{
		DrawBox(player1.pos.x, player1.pos.y, player1.pos.x + 32, player1.pos.y + 32, GetColor(255, 0, 0), true);
	}
	if (player1.moveDir == DIR_RIGHT)
	{
		DrawBox(player1.pos.x, player1.pos.y, player1.pos.x + 32, player1.pos.y + 32, GetColor(0, 255, 255), true);
	}
	if (player1.moveDir == DIR_UP)
	{
		DrawBox(player1.pos.x, player1.pos.y, player1.pos.x + 32, player1.pos.y + 32, GetColor(0, 0, 255), true);
	}
	if (player1.moveDir == DIR_LEFT)
	{
		DrawBox(player1.pos.x, player1.pos.y, player1.pos.x + 32, player1.pos.y + 32, GetColor(255, 255, 255), true);
	}
	DrawFormatString(0, 16, GetColor(255, 0, 0), "%d,%d", player1.pos.x, player1.pos.y);
}

void PlayerControl(void)
{
	if (keyNew[KEY_ID_P1DOWN])
	{
		player1.moveDir = DIR_DOWN;
		player1.pos.y = player1.pos.y +2;
	}
	if (keyNew[KEY_ID_P1RIGHT])
	{
		player1.moveDir = DIR_RIGHT;
		player1.pos.x = player1.pos.x +2;
	}
	if (keyNew[KEY_ID_P1UP])
	{
		player1.moveDir = DIR_UP;
		player1.pos.y = player1.pos.y -2;
	}
	if (keyNew[KEY_ID_P1LEFT])
	{
		player1.moveDir = DIR_LEFT;
		player1.pos.x = player1.pos.x -2;
	}
}