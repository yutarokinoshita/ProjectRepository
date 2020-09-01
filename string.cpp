#include <DxLib.h>
#include "main.h"

// �ϐ�
int kaisyounasiImage;	// �̍�1�̊i�[�p
int rightImage;			// �̍�2�̊i�[�p(��)
int middleImage;		// �̍�3�̊i�[�p
int bonusImage;			// �̍�4�̊i�[�p
int resultImage;		// ���U���g���ɕ\������̍�
int stringSize;			// �̍��̉��T�C�Y�L�^�p

// �����摜�ǂݍ���
void StringInit()
{
	kaisyounasiImage = LoadGraph("image/kaisyounasi.png");
	middleImage = LoadGraph("image/middle.png");
	bonusImage = LoadGraph("image/bonus20.png");
}

// �����f�[�^������
void StringGameInit()
{
	resultImage = 0;
}


// ���U���g���̏̍����菈��
void StringResult(int point, int bonus,int point2)
{
	if (point == 0 && bonus == 0)
	{
		// �J�C�V���E�i�V
		resultImage = kaisyounasiImage;
		stringSize = 278;
	}
	if (point > 0 && point <= 10)
	{
		// ���O���̎q��
	}
	if (point > 10 && point <= 20)
	{
		//�h�D�J�e�B���܂�
		resultImage = middleImage;
		stringSize = 346;
	}
	if (bonus >= 20)
	{
		// ����������܂���
		resultImage = bonusImage;
	}
	if (bonus >= point2*2)
	{
		// �n�ɕ���
	}
	if (point == 0 && bonus >= 30)
	{
		// ���S��m
	}
}

// �����摜�`��
void StringDraw(void)
{
	//DrawGraph(232, SCREEN_SIZE_Y / 2, resultImage, true);
	DrawGraph((SCREEN_SIZE_X - stringSize) / 2, SCREEN_SIZE_Y / 2, resultImage, true);
}