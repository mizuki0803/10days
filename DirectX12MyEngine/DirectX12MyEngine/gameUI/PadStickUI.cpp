#include "PadStickUI.h"

PadStickUI* PadStickUI::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//パッドスティックUIのインスタンスを生成
	PadStickUI* padStickUI = new PadStickUI();
	if (padStickUI == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!padStickUI->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete padStickUI;
		assert(0);
		return nullptr;
	}

	//座標をセット
	padStickUI->position = position;

	//大きさをセット
	padStickUI->size = size;
	padStickUI->texSize = { 100, 100 };

	return padStickUI;
}

void PadStickUI::Update()
{
	//スティックの画像を動かす
	StickMove();

	//スプライト更新
	Sprite::Update();
}

void PadStickUI::StickMove()
{
	//タイマーを更新
	changeTimer++;
	const int changeTime = 30;

	//タイマーが指定した時間になったら
	if (changeTimer >= changeTime) {
		//タイマーを初期化
		changeTimer = 0;

		//連番画像番号を更新
		drawNum++;
		if (drawNum >= 4) { drawNum = 0; }

		//スプライトの左上切り出し座標をテクスチャサイズ * 連番画像番号で算出する
		texLeftTop.x = texSize.x * drawNum;
	}
}
