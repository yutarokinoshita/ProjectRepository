//-----------------------------
// TestProject
//	 by Kinosita
//-----------------------------
#include "DxLib.h"		// DxLib���C�u�������g�p����
#include "main.h"
#include "map.h"
#include "player.h"
#include "player2.h"
#include "keycheck.h"
#include "playerAction.h"
#include "treasure.h"
#include "soil.h"
#include "effect.h"

// �ϐ�
SCENE_ID sceneID;
int StartTime;		// �Q�[���J�n�܂ł̎���

// �v���g�^�C�v�錾

// WinMain�֐�
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	if (!SystemInit())
	{
		return 0;
	}

	// �ް�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		keyCheck();
		ClsDrawScreen();
		// ���C������
		switch (sceneID)
		{
		case SCENE_ID_INIT:
			InitScene();
			sceneID = SCENE_ID_TITLE;
			break;
		case SCENE_ID_TITLE:
			TitleScene();
			break;
		case SCENE_ID_GAME:
			GameScene();
			break;
		case SCENE_ID_GAMEOVER:
			GameOverScene();
			break;
		case SCENE_ID_MAX:
			break;
		default:
			break;
		}



		ScreenFlip();
	}
	DxLib_End();	// DXײ���؂̏I������
	return 0;	// ������۸��т̏I��
}

bool SystemInit(void)
{
	//----------�V�X�e������
	SetWindowText("�̌@��");
	// �V�X�e������
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	// �L�[�̒ǉ�
	keyInit();
	// �O���t�B�b�N�̓o�^
	// �X�e�[�W��񏉊���
	StageSystemInit();
	// �v���C���[��񏉊���
	PlayerSystemInit();
	PlayerSystemInit2();
	// �A�C�e����񏉊���
	ItemSystemInit();
	// ���_�A�C�e����񏉊���
	TreasureSystemInit();
	// �n�ʏ��@������
	SoilSystemInit();
	// �G�t�F�N�g��񏉊���
	TreasureEffectInit();
	// �ϐ�������
	sceneID = SCENE_ID_INIT;

	return true;
}

void InitScene(void)
{
	StageGameInit();
	PlayerGameInit();
	PlayerGameInit2();
	ItemGameInit();
	TreasureGameInit();
	SoilGameInit();
	TreasureEffectGameInit();
	StartTime = 2400;
}

void TitleScene(void)
{
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		sceneID = SCENE_ID_GAME;
	}
	TitleDraw();
}

void TitleDraw(void)
{
	DrawBox(100, 100, SCREEN_SIZE_X - 100, SCREEN_SIZE_Y - 100, GetColor(255, 255, 255), true);
}


void GameScene(void)
{
	if (keyDownTrigger[KEY_ID_SPACE] || StartTime <= 0)
	{
		sceneID = SCENE_ID_GAMEOVER;
	}
	StartTime--;
	//GameDraw();
	PlayerControl();
	PlayerControl2();
	ItemControl();
	//effectControl();
	GameDraw();
}

void GameDraw(void)
{
	//DrawFormatString(0, 0,GetColor(255, 255, 255), "GameCounter = %d", gameCounter);


	StageDrawInit();
	SoilDrawInit();
	TreasureDraw();
	TreasureEffectDraw();
	ItemDrawInit();
	PlayerGameDraw();
	PlayerGameDraw2();
	DrawFormatString(500, 0, GetColor(255, 255, 255), "%d,%d", mapPos.x,mapPos.y);
}

void GameOverScene(void)
{
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		InitScene();
		sceneID = SCENE_ID_TITLE;
	}
	GameOverDraw();
}

void GameOverDraw(void)
{
	DrawBox(100, 100, SCREEN_SIZE_X - 100, SCREEN_SIZE_Y - 100, GetColor(0, 255, 255), true);
}