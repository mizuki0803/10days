#include "PushASprite.h"

PushASprite* PushASprite::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//PushAスプライトのインスタンスを生成
	PushASprite* pushASprite = new PushASprite();
	if (pushASprite == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!pushASprite->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete pushASprite;
		assert(0);
		return nullptr;
	}

	//座標をセット
	pushASprite->position = position;

	//大きさをセット
	pushASprite->size = size;
	pushASprite->texSize = size;

	return pushASprite;
}

void PushASprite::Update()
{
	//点滅
	if (isDraw) {
		DrawMode();
	}
	else {
		Flashing();
	}


	//描画状態でなければ抜ける
	if (!isDraw) { return; }

	//スプライト更新
	Sprite::Update();
}

void PushASprite::Draw()
{
	//描画状態でなければ抜ける
	if (!isDraw) { return; }

	//スプライト描画
	Sprite::Draw();
}

void PushASprite::ChangeFlashingSpeed()
{
	//点滅の速さを変える
	drawModeTime = 3;
	flashingTime = 3;
}

void PushASprite::Flashing()
{
	//タイマーを更新
	flashingTimer++;

	//タイマーが指定した時間になったら
	if (flashingTimer >= flashingTime) {
		//描画状態にする
		isDraw = true;
		//タイマーを初期化
		flashingTimer = 0;
	}
}

void PushASprite::DrawMode()
{
	//タイマーを更新
	drawModeTimer++;

	//タイマーが指定した時間になったら
	if (drawModeTimer >= drawModeTime) {
		//描画状態を解除
		isDraw = false;
		//タイマーを初期化
		drawModeTimer = 0;
	}
}
