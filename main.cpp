//-----------------------------
// TestProject
//	 by Kinosita
//-----------------------------
#include "DxLib.h"		// DxLib���C�u�������g�p����
#include "main.h"
#include "map.h"
#include "player.h"
<<<<<<< HEAD
#include "keycheck.h"

=======
>>>>>>> e928399d299ad8e6ff2c5fbc3299ecb37a63f41d
// �ϐ�
int gameCounter;

// �v���g�^�C�v�錾
void GameMain(void);
void GameDraw(void);

<<<<<<< HEAD
=======


void GameDraw(void)
{
	DrawFormatString(0, 0,GetColor(255, 255, 255), "GameCounter = %d", gameCounter);
	StageDrawInit();
}

void GameMain(void)
{
	GameDraw();
	PlayerDrawInit();
}

>>>>>>> e928399d299ad8e6ff2c5fbc3299ecb37a63f41d
// WinMain�֐�
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//----------�V�X�e������
<<<<<<< HEAD
	SetWindowText("�̌@��");
=======
	SetWindowText("TestProject");
>>>>>>> e928399d299ad8e6ff2c5fbc3299ecb37a63f41d
	// �V�X�e������
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	// �O���t�B�b�N�̓o�^

	// �ϐ�������
	gameCounter = 0;
	PlayerSystemInit();
<<<<<<< HEAD
	keyInit();
=======
>>>>>>> e928399d299ad8e6ff2c5fbc3299ecb37a63f41d

	// �ް�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();

		// ���C������
<<<<<<< HEAD
		keyCheck();
=======
>>>>>>> e928399d299ad8e6ff2c5fbc3299ecb37a63f41d
		GameMain();
		gameCounter++;

		ScreenFlip();
	}
	DxLib_End();	// DXײ���؂̏I������
	return 0;	// ������۸��т̏I��
}

<<<<<<< HEAD
void GameDraw(void)
{
	DrawFormatString(0, 0,GetColor(255, 255, 255), "GameCounter = %d", gameCounter);


	StageDrawInit();
	PlayerDrawInit();
}
void GameMain(void)
{
	GameDraw();
	PlayerControl();
}
=======
>>>>>>> e928399d299ad8e6ff2c5fbc3299ecb37a63f41d
