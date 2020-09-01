#include <DxLib.h>
#include "main.h"

// 変数
int kaisyounasiImage;	// 称号1の格納用
int rightImage;			// 称号2の格納用(仮)
int middleImage;		// 称号3の格納用
int bonusImage;			// 称号4の格納用
int resultImage;		// リザルト時に表示する称号
int stringSize;			// 称号の横サイズ記録用

// 文字画像読み込み
void StringInit()
{
	kaisyounasiImage = LoadGraph("image/kaisyounasi.png");
	middleImage = LoadGraph("image/middle.png");
	bonusImage = LoadGraph("image/bonus20.png");
}

// 文字データ初期化
void StringGameInit()
{
	resultImage = 0;
}


// リザルト時の称号決定処理
void StringResult(int point, int bonus,int point2)
{
	if (point == 0 && bonus == 0)
	{
		// カイショウナシ
		resultImage = kaisyounasiImage;
		stringSize = 278;
	}
	if (point > 0 && point <= 10)
	{
		// モグラの子分
	}
	if (point > 10 && point <= 20)
	{
		//ドゥカティ生まれ
		resultImage = middleImage;
		stringSize = 346;
	}
	if (bonus >= 20)
	{
		// もう喰っちまった
		resultImage = bonusImage;
	}
	if (bonus >= point2*2)
	{
		// 地に伏す
	}
	if (point == 0 && bonus >= 30)
	{
		// 逃亡戦士
	}
}

// 文字画像描画
void StringDraw(void)
{
	//DrawGraph(232, SCREEN_SIZE_Y / 2, resultImage, true);
	DrawGraph((SCREEN_SIZE_X - stringSize) / 2, SCREEN_SIZE_Y / 2, resultImage, true);
}