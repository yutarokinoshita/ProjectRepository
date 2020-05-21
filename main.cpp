//-----------------------------
// TestProject
//	 by Kinosita
//-----------------------------
#include "DxLib.h"		// DxLib���C�u�������g�p����
#include "main.h"
#include "map.h"
#include "player.h"
#include "keycheck.h"
#include "playerAction.h"
#include "treasure.h"
#include "soil.h"
//#include "effect.h"

// �ϐ�
int gameCounter;

// �v���g�^�C�v�錾
void GameMain(void);
void GameDraw(void);

// WinMain�֐�
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//----------�V�X�e������
	SetWindowText("�̌@��");
	// �V�X�e������
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	// �O���t�B�b�N�̓o�^

	// �ϐ�������
	gameCounter = 0;
	StageInit();
	PlayerSystemInit();
	keyInit();
	ItemSystemInit();
	TreasureInit();
	soilSystemInit();
	//TreasureEffectInit();

	// �ް�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();

		// ���C������
		keyCheck();
		GameMain();
		gameCounter++;

		ScreenFlip();
	}
	DxLib_End();	// DXײ���؂̏I������
	return 0;	// ������۸��т̏I��
}

void InitScene(void)
{

}

void GameDraw(void)
{
	DrawFormatString(0, 0,GetColor(255, 255, 255), "GameCounter = %d", gameCounter);


	StageDrawInit();
	soilDrawInit();
	TreasureDraw();
	//TreasureEffectDraw();
	ItemDrawInit();
	PlayerGameDraw();
	DrawFormatString(500, 0, GetColor(255, 255, 255), "%d,%d", mapPos.x,mapPos.y);
}
void GameMain(void)
{
	GameDraw();
	PlayerControl();
	ItemControl();
	//effectControl();

	// �f�o�b�O�p�@��ŏ����Ă悵
	if (CheckHitKey(KEY_INPUT_UP))
	{
		mapPos.y++;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		mapPos.y--;
	}
}
