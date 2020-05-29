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
int GameTime;		// �Q�[���I���܂ł̎���
int EndTime;		// �Q�[���I�����̎���
int p1Point;		// �v���C���[�P�̓��_
int p2Point;		// �v���C���[�Q�̓��_
int bonus;			// �{�[�i�X���_

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
	StartTime = 240;
	GameTime = 600;
	EndTime = 240;
	bonus = 0;
	p1Point = 0;
	p2Point = 0;
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
	StageDrawInit();
	SoilDrawInit();
}


void GameScene(void)
{
	if (keyDownTrigger[KEY_ID_SPACE] || EndTime <= 0)
	{
		sceneID = SCENE_ID_GAMEOVER;
	}

	if (StartTime > 0)
	{
		StartTime--;
	}
	else
	{
		if (GameTime >= 0)
		{
			GameTime--;
			//GameDraw();
			PlayerControl();
			PlayerControl2();
			ItemControl();
			//effectControl();
			if (WarmHitPoint())
			{
				bonus++;
			}
			p1Point += PlayerScere();
			p2Point += PlayerScere2();
		}
		else
		{
			EndTime--;
		}
	}
		GameDraw();

}

void GameDraw(void)
{
	//DrawFormatString(0, 0,GetColor(255, 255, 255), "GameCounter = %d", gameCounter);


	StageDrawInit();
	TreasureDraw();
	SoilDrawInit();
	TreasureEffectDraw();
	ItemDrawInit();
	PlayerGameDraw();
	PlayerGameDraw2();
	DrawFormatString(500, 0, GetColor(255, 255, 255), "%d,%d", mapPos.x,mapPos.y);
	DrawFormatString(0, 300, GetColor(255, 255, 0), "bonus:%d",bonus );
	DrawFormatString(0, 316, GetColor(255, 255, 0), "p1Point:%d", p1Point);
	DrawFormatString(0, 332, GetColor(255, 255, 0), "p2Point:%d", p2Point);
	DrawFormatString(0, 348, GetColor(255, 255, 0), "start:%d", StartTime/60);
	if (GameTime <= 0)
	{
		DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, GetColor(255, 255, 255), "�^�C���A�b�v�I");
	}
}

void GameOverScene(void)
{
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		InitScene();
		sceneID = SCENE_ID_TITLE;
	}
	if (bonus >= 10)
	{
		p1Point += bonus / 10;
	}
	bonus = 0;
	GameOverDraw();
}

void GameOverDraw(void)
{
	DrawBox(100, 100, SCREEN_SIZE_X - 100, SCREEN_SIZE_Y - 100, GetColor(0, 255, 255), true);
	//SetDrawBright(100, 100, 100);
	DrawFormatString(0, 316, GetColor(255, 255, 0), "p1Point:%d", p1Point);
	DrawFormatString(0, 332, GetColor(255, 255, 0), "p2Point:%d", p2Point);
}