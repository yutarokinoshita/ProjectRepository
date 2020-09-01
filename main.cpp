//-----------------------------
// TestProject
//	 by Kinosita
//-----------------------------
#include <DxLib.h>		// DxLib���C�u�������g�p����
#include <stdio.h>		// �t�@�C������Ɏg�p����w�b�_�[
#include <string.h>		// �����񑀍�Ɏg�p����w�b�_�[
#include "main.h"
#include "map.h"
#include "player.h"
#include "player2.h"
#include "keycheck.h"
#include "playerAction.h"
#include "treasure.h"
#include "soil.h"
#include "effect.h"
#include "string.h"

#define INIT_VELOCITY		70.0f	// ���A�N�V��������̏����x

#define INIT_VELOCITY		70.0f	// ���A�N�V��������̏����x

// �ϐ�
SCENE_ID sceneID;
int StartTime;		// �Q�[���J�n�܂ł̎���
int GameTime;		// �Q�[���I���܂ł̎���
int EndTime;		// �Q�[���I�����̎���
int p1Point;		// �v���C���[�P�̓��_
int p2Point;		// �v���C���[�Q�̓��_
int p1Result;		// �v���C���[�P�̌���
int p2Result;		// �v���C���[�Q�̌���
int bonus;			// �{�[�i�X���_
int jumpImage1[4];	// ���U���g���̃v���C���[1�摜�i�[�p
int winImage1[2];	// ���U���g���̃v���C���[1�����摜�i�[�p
int loseImage1[2];	// ���U���g���̃v���C���[1�����摜�i�[�p
CHARACTER result1;	// ���U���g���ɌĂԃv���C���[�P�̍\��
<<<<<<< HEAD
int jumpStopTime1;	// ���U���g���Ƀv���C���[1�𒸓_�Œ�~�����鎞�Ԃ̏����p
int jumpStopTime2;	// ���U���g���Ƀv���C���[2���_�Œ�~�����鎞�Ԃ̏����p
=======
int jumpStopTime;	// ���U���g���ɒ��_�Œ�~�����鎞�Ԃ̏����p
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
int jumpImage2[4];	// ���U���g���̃v���C���[2�摜�i�[�p
int winImage2[2];	// ���U���g���̃v���C���[2�����摜�i�[�p
int loseImage2[2];	// ���U���g���̃v���C���[2�����摜�i�[�p
CHARACTER result2;	// ���U���g���ɌĂԃv���C���[�P�̍\����
<<<<<<< HEAD
int HiScore;		// �n�C�X�R�A
bool newScoreFlag;	// �n�C�X�R�A���X�V���ꂽ�ۂɎg�p
int titleImage;		// �^�C�g���摜�i�[�p
int startImage;		// �X�^�[�g�摜�i�[�p
bool stopFlag;		// �Q�[�����ꎞ��~�����邽�߂̃t���O
bool p1ResultEnd;	// �v���C���[1�̃��U���g�I���t���O
bool p2ResultEnd;	// �v���C���[2�̃��U���g�I���t���O
int namedTime;		// �̍����\�������܂ł̎���
=======
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1

// �v���g�^�C�v�錾

// WinMain�֐�
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	if (!SystemInit())
	{
		return 0;
	}

	// �n�C�X�R�A�̃��[�h
	HiScoreLoad();
	
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
	SetFontSize(32);
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
	// �n�ʏ�񏉊���
	SoilSystemInit();
	// �G�t�F�N�g��񏉊���
	EffectInit();
	// �ϐ�������
	sceneID = SCENE_ID_INIT;
	// ���U���g�p�O���̓ǂݍ���
	// �v���C���[1
	LoadDivGraph("image/moleDamage.png", 4, 4, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, jumpImage1, false);
	LoadDivGraph("image/moleWin.png", 2, 2, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, winImage1, false);
	LoadDivGraph("image/moleLose.png", 2, 2, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, loseImage1, false);
	// �v���C���[2
	LoadDivGraph("image/moleDamage.png", 4, 4, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, jumpImage2, false);
	LoadDivGraph("image/moleWin.png", 2, 2, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, winImage2, false);
	LoadDivGraph("image/moleLose.png", 2, 2, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, loseImage2, false);

	// ���U���g�p�O���̓ǂݍ���
	// �v���C���[1
	LoadDivGraph("image/moleDamage.png", 4, 4, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, jumpImage1, false);
	LoadDivGraph("image/moleWin.png", 2, 2, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, winImage1, false);
	LoadDivGraph("image/moleLose.png", 2, 2, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, loseImage1, false);
	// �v���C���[2
	LoadDivGraph("image/ratDamage.png", 4, 4, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, jumpImage2, false);
	LoadDivGraph("image/ratWin.png", 2, 2, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, winImage2, false);
	LoadDivGraph("image/ratLose.png", 2, 2, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, loseImage2, false);
	// �^�C�g���ǂݍ���
	titleImage = LoadGraph("image/titlelogo.png");
	startImage = LoadGraph("image/startbutton.png");
	// �̍�������
	StringInit();

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
<<<<<<< HEAD
	EffectGameInit();
	StringGameInit();
	FadeInit();
	StartTime = 240;
	GameTime = 720;
=======
	TreasureEffectGameInit();
	FadeInit();
	StartTime = 240;
	GameTime = 300;
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
	EndTime = 60;
	bonus = 0;
	p1Point = 0;
	p2Point = 0;
	sceneID = SCENE_ID_TITLE;

	result1.pos = { 200, SCREEN_SIZE_Y /2 };
	result1.velocity = { 0,0 };
	result2.pos = { SCREEN_SIZE_X - 232, SCREEN_SIZE_Y /2 }; //SCREEN_SIZE_Y - 132 };
	result2.velocity = { 0,0 };
<<<<<<< HEAD
	jumpStopTime1 = 0;
	jumpStopTime2 = 0;
	p1Result = 0;
	p2Result = 0;
	p1ResultEnd = false;
	p2ResultEnd = false;

	newScoreFlag = false;
	stopFlag = false;
	namedTime = 0;
=======
	jumpStopTime = 30;
	p1Result = 0;
	p2Result = 0;
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
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

	DrawGraph((SCREEN_SIZE_X - 464) / 2, SCREEN_SIZE_Y  / 2- 148, titleImage, true);
	DrawGraph((SCREEN_SIZE_X - 456) / 2, (SCREEN_SIZE_Y + 128) / 2, startImage, true);
	DrawFormatString(SCREEN_SIZE_X / 2-128, 448, GetColor(255, 255, 255), "�n�C�X�R�A %d", HiScore);
}


void GameScene(void)
{
<<<<<<< HEAD
	stopFlag = false;
	if (keyNew[KEY_ID_SPACE] || EndTime <= 0)
	{
		// �f�o�b�O�p�X�R�A
		p1Point = 15;
		p2Point = 10;
		//bonus = 20;

		if (FadeOutScreen(5) >= 255)
		{
			// ���U���g�ŕ\������̍���I������
			StringResult(p1Point, bonus, p2Point);
			// �Q�[���I���m�莞�ɓG�������{�[�i�X�����Z
			if (bonus >= 10)
			{
				p1Point += bonus / 5;
=======
	if (keyNew[KEY_ID_SPACE] || EndTime <= 0)
	{
		p1Point = 15;
		p2Point = 10;
		bonus = 20;

		if (FadeOutScreen(5) >= 255)
		{
			// �Q�[���I���m�莞�ɓG�������{�[�i�X�����Z
			if (bonus >= 10)
			{
				p1Point += bonus / 10;
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
			}
			// �I�����ɃW�����v�̏����x��ǉ�
			result1.velocity.y = INIT_VELOCITY;
			result2.velocity.y = INIT_VELOCITY;
<<<<<<< HEAD
			// ���_�ɉ�������~���Ԃ�^����
			jumpStopTime1 = p1Point * 3;
			jumpStopTime2 = p2Point * 3;

			mapPos = { 0,0 };
			// �n�C�X�R�A���o���ꍇ�X�V����
			if (HiScore < p1Point)
			{
				HiScore = p1Point;

				HiScoreSave();

				newScoreFlag = true;
			}
=======
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1

			FadeInit();
			sceneID = SCENE_ID_GAMEOVER;
		}
	}

	if (StartTime > 0)
	{
		StartTime--;
	}
	else
	{
		if (GameTime >= 0)
		{
			PlayerControl();
			// ��~�������s��ꂽ�ۃv���C���[�ȊO���~�߂�
			if (!stopFlag)
			{
				GameTime--;
				//GameDraw();
				PlayerControl2();
				ItemControl();
				//effectControl();
				if (WarmHitPoint())
				{
					bonus++;
				}
				p1Point += PlayerScere();
				p2Point += PlayerScere2();
				EffectControl();
			}
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
	ItemDrawInit();
	if (!stopFlag)
	{
		PlayerGameDraw();
	}
	PlayerGameDraw2();
<<<<<<< HEAD
	EffectDraw();
	if (stopFlag)
	{
		PlayerGameDraw();
	}

	if ((GameTime+60)/60 <= 10)
	{
		DrawFormatString(SCREEN_SIZE_X / 2 - 32, 32, GetColor(255, 0, 0), "%d", (GameTime+60) / 60);
	}
	else
	{
		DrawFormatString(SCREEN_SIZE_X / 2 - 32, 32, GetColor(255, 128, 128), "%d", (GameTime+60) / 60);
=======
	//DrawFormatString(500, 0, GetColor(255, 255, 255), "%d,%d", mapPos.x,mapPos.y);
	//DrawFormatString(0, 300, GetColor(255, 255, 0), "bonus:%d",bonus );
	//DrawFormatString(0, 316, GetColor(255, 255, 0), "p1Point:%d", p1Point);
	//DrawFormatString(0, 332, GetColor(255, 255, 0), "p2Point:%d", p2Point);
	//DrawFormatString(0, 348, GetColor(255, 255, 0), "start:%d", StartTime/60);
	if (GameTime/60 <= 10)
	{
		DrawFormatString(SCREEN_SIZE_X / 2 - 32, 32, GetColor(255, 0, 0), "%d", GameTime / 60);
	}
	else
	{
		DrawFormatString(SCREEN_SIZE_X / 2 - 32, 32, GetColor(0, 0, 0), "%d", GameTime / 60);
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
	}

	if (GameTime <= 0)
	{
		DrawFormatString(SCREEN_SIZE_X / 2- 96, SCREEN_SIZE_Y / 2 , GetColor(255, 255, 255), "�^�C���A�b�v�I");
	}
	if (StartTime > 0)
	{
		if (StartTime >= 60)
		{
			DrawFormatString(SCREEN_SIZE_X / 2-32, SCREEN_SIZE_Y / 2, GetColor(255, 255, 255), "%d", StartTime / 60);
		}
		else
		{
			DrawFormatString(SCREEN_SIZE_X / 2 - 32, SCREEN_SIZE_Y / 2, GetColor(255, 255, 255), "GO!");
		}
	}

	// �ȉ��f�o�b�O�p�\��
	DrawFormatString(500, 0, GetColor(255, 255, 255), "%d,%d", mapPos.x,mapPos.y);
	DrawFormatString(0, 300, GetColor(0, 255, 0), "bonus:%d",bonus );
	DrawFormatString(0, 332, GetColor(0,255, 0), "p1Point:%d", p1Point);
	DrawFormatString(0, 364, GetColor(0,255, 0), "p2Point:%d", p2Point);
	DrawFormatString(0, 396, GetColor(0, 255, 0), "start:%d", StartTime/60);
}

void GameOverScene(void)
{
<<<<<<< HEAD
	//XY jumpPosCopy = {0,0};
	if (FadeInScreen(5) >= 0)
	{
		if (p1ResultEnd && p2ResultEnd)
		{
			if (keyDownTrigger[KEY_ID_SPACE] && FadeInScreen(5) >= 255)
			{
				InitScene();
				sceneID = SCENE_ID_TITLE;
			}
=======
	XY jumpPosCopy = {0,0};
	if (FadeInScreen(5) >= 0)
	{
		if (keyDownTrigger[KEY_ID_SPACE] && FadeInScreen(5) >= 255)
		{
			InitScene();
			sceneID = SCENE_ID_TITLE;
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
		}
		//bonus = 0;

	// ���_�Q�[�W�̑�������
		if (p1Point > 0)
		{
<<<<<<< HEAD
			if (result1.AnimCnt % 3 == 0 && result1.velocity.y == 0)
			{
				p1Point--;
				p1Result += 10;
			}
		}
		if (p2Point > 0)
		{
			if (result2.AnimCnt % 3 == 0 && result2.velocity.y == 0)
			{
				p2Point--;
				p2Result += 10;
			}
=======
			p1Point--;
			p1Result += 10;
		}
		if (p2Point > 0)
		{
			p2Point--;
			p2Result += 10;
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
		}
		//if (result1.pos.y+10 > SCREEN_SIZE_Y - 100 - p1Result)

		// ���U���g�̃v���C���[�A�j���[�V��������
		// �v���C���[1�̏���
<<<<<<< HEAD
		if (result1.velocity.y != 0 || jumpStopTime1 < 0)
		{
			// ���x�̕ύX
			result1.velocity.y -= ACC_G * FRAME_TIME;
			//if (p1Point > 0)
			//{
			//	if (result1.velocity.y == 0)
			//	{
			//		result1.velocity.y = 0;
			//	}
			//}
=======
		if (result1.velocity.y != 0 || jumpStopTime < 0)
		{
			// ���x�̕ύX
			result1.velocity.y -= ACC_G * FRAME_TIME;
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
			// �ړ������̒ǉ�
			result1.pos.y -= result1.velocity.y * FRAME_TIME;
		}
		else
		{
<<<<<<< HEAD
			jumpStopTime1--;
		}
		// �W�����v���~�߃Q�[�W�ɏ悹�鏈��
		if (result1.pos.y >= SCREEN_SIZE_Y - 132 - p1Result - 32)
		{
			//jumpStopFlag = true;
			result1.pos.y = SCREEN_SIZE_Y - 132 - p1Result - 32;
			p1ResultEnd = true;
		}
		// �v���C���[2�̏���
		if (result2.velocity.y != 0 || jumpStopTime2 < 0)
		{
			// ���x�̕ύX
			result2.velocity.y -= ACC_G * FRAME_TIME;
			// �ړ������̒ǉ�
			result2.pos.y -= result2.velocity.y * FRAME_TIME;
			//}
		}
		else
		{
			jumpStopTime2--;
		}
		// �W�����v���~�߃Q�[�W�ɏ悹�鏈��
		if (result2.pos.y >= SCREEN_SIZE_Y - 132 - p2Result - 32)
		{
			result2.pos.y = SCREEN_SIZE_Y - 132 - p2Result - 32;
			p2ResultEnd = true;
		}
		GameOverDraw();
		if (p1ResultEnd && p2ResultEnd)
		{
			StringDraw();
		}
=======
			jumpStopTime--;
		}
		// �W�����v���~�߃Q�[�W�ɏ悹�鏈��
		if (result1.pos.y >= SCREEN_SIZE_Y - 100 - p1Result - 32)
		{
			//jumpStopFlag = true;
			result1.pos.y = SCREEN_SIZE_Y - 100 - p1Result - 32;
		}
		// �v���C���[2�̏���
		if (result2.velocity.y != 0 || jumpStopTime < 0)
		{
				// ���x�̕ύX
				result2.velocity.y -= ACC_G * FRAME_TIME;
				// �ړ������̒ǉ�
				result2.pos.y -= result2.velocity.y * FRAME_TIME;
			//}
		}
		// �W�����v���~�߃Q�[�W�ɏ悹�鏈��
		if (result2.pos.y >= SCREEN_SIZE_Y - 100 - p2Result - 32)
		{
			result2.pos.y = SCREEN_SIZE_Y - 100 - p2Result - 32;
		}
		GameOverDraw();
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
	}
}

void GameOverDraw(void)
{
	result1.AnimCnt++;
	result2.AnimCnt++;

	StageDrawInit();
	SoilDrawInit();

<<<<<<< HEAD
	DrawBox(100, 100, SCREEN_SIZE_X - 100, SCREEN_SIZE_Y - 100, GetColor(255, 255, 255), true);
=======
	DrawBox(100, 100, SCREEN_SIZE_X - 100, SCREEN_SIZE_Y - 100, GetColor(0, 255, 255), true);
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
	//SetDrawBright(100, 100, 100);
	DrawFormatString(0, 316, GetColor(255, 255, 0), "p1Point:%d", p1Point);
	DrawFormatString(0, 348, GetColor(255, 255, 0), "p2Point:%d", p2Point);
	DrawFormatString(0, 380, GetColor(255, 255, 0), "bonus:%d", bonus);
	DrawFormatString(0, 422, GetColor(255, 255, 0), "total:%d", p1Point + bonus / 10);
<<<<<<< HEAD
	// ���_�̕`��
	DrawFormatString(200, SCREEN_SIZE_Y - 132, GetColor(0, 0, 0), "%2d", p1Result / 10);
	DrawFormatString(SCREEN_SIZE_X - 232, SCREEN_SIZE_Y - 132, GetColor(0, 0, 0), "%2d", p2Result / 10);
	DrawFormatString(SCREEN_SIZE_X/2, 200, GetColor(0, 0, 0), "YOU WIN");

	// ���n���ɉ摜��ύX����
	// �v���C���[1�̉摜
	if (result1.pos.y <= SCREEN_SIZE_Y - 132 - p1Result)
	{
		if (result1.pos.y >= SCREEN_SIZE_Y - 132 - p1Result - 32)
=======

	// ���n���ɉ摜��ύX����
	// �v���C���[1�̉摜
	if (result1.pos.y <= SCREEN_SIZE_Y - 100 - p1Result)
	{
		if (result1.pos.y >= SCREEN_SIZE_Y - 100 - p1Result - 32)
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
		{
			if (p1Result > p2Result)
			{
				DrawGraph(result1.pos.x, result1.pos.y, winImage1[(result1.AnimCnt / 15) % 2], true);
			}
			else
			{
				DrawGraph(result1.pos.x, result1.pos.y, loseImage1[(result1.AnimCnt / 15) % 2], true);
			}
		}
		else
		{
			DrawGraph(result1.pos.x, result1.pos.y, jumpImage1[(result1.AnimCnt / 5) % 4], true);
		}
	}
	// �v���C���[2�̉摜
<<<<<<< HEAD
	if (result2.pos.y <= SCREEN_SIZE_Y - 132 - p2Result)
	{
		if (result2.pos.y >= SCREEN_SIZE_Y - 132 - p2Result - 32)
=======
	if (result2.pos.y <= SCREEN_SIZE_Y - 100 - p2Result)
	{
		if (result2.pos.y >= SCREEN_SIZE_Y - 100 - p2Result - 32)
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
		{
			if (p2Result > p1Result)
			{
				DrawGraph(result2.pos.x, result2.pos.y, winImage2[(result2.AnimCnt / 15) % 2], true);
			}
			else
			{
				DrawGraph(result2.pos.x, result2.pos.y, loseImage2[(result2.AnimCnt / 15) % 2], true);
			}
		}
		else
		{
			DrawGraph(result2.pos.x, result2.pos.y, jumpImage2[(result2.AnimCnt / 5) % 4], true);
		}
	}

	// ���_�̃Q�[�W�̕\��
	// �v���C���[1�̃Q�[�W
<<<<<<< HEAD
	DrawBox(200, SCREEN_SIZE_Y - 132, 200+32, SCREEN_SIZE_Y - 132 - p1Result, GetColor(0, 128, 0), true);
	// �v���C���[2�̃Q�[�W
	DrawBox(SCREEN_SIZE_X - 200 - 32, SCREEN_SIZE_Y - 132, SCREEN_SIZE_X - 200, SCREEN_SIZE_Y - 132 - p2Result, GetColor(0, 0, 128), true);
	//DrawBox(182 + 32, SCREEN_SIZE_Y - 100,182+ 64, SCREEN_SIZE_Y - 100 - p2Point, GetColor(255, 255, 255), true);
}

void HiScoreSave()
{
	FILE *fp;

	// �n�C�X�R�A�p�t�@�C�����J��
	fp = fopen("HiScore.dat", "wb");

	// �J���Ȃ��ꍇ�����ŏI��
	if (fp == NULL) return;

	// �n�C�X�R�A�̏����o��
	fwrite(&HiScore, sizeof(HiScore), 1, fp);

	// �t�@�C�������
	fclose(fp);
}

void HiScoreLoad()
{

	FILE* fp;

	// �n�C�X�R�A�p�t�@�C�����J��
	fp = fopen("HiScore.dat", "rb");

	// �J���Ȃ��ꍇ���̐��l���Z�b�g
	if (fp == NULL)
	{
		HiScore = 15;
	}
	else
	{
		// �t�@�C���ǂݍ���
		fread(&HiScore, sizeof(HiScore), 1, fp);

		// �t�@�C�������
		fclose(fp);
	}
}

// �Ăяo�����̓Q�[�����ꎞ��~������
void GameStop()
{
	stopFlag = true;
=======
	DrawBox(200, SCREEN_SIZE_Y - 132, 200+32, SCREEN_SIZE_Y - 100 - p1Result, GetColor(0, 255, 0), true);
	// �v���C���[2�̃Q�[�W
	DrawBox(SCREEN_SIZE_X - 200, SCREEN_SIZE_Y - 132, SCREEN_SIZE_X - 200 - 32, SCREEN_SIZE_Y - 100 - p2Result, GetColor(0, 255, 0), true);
	//DrawBox(182 + 32, SCREEN_SIZE_Y - 100,182+ 64, SCREEN_SIZE_Y - 100 - p2Point, GetColor(255, 255, 255), true);
>>>>>>> e686ce240afe81a29fe3b035459777d97375fbd1
}