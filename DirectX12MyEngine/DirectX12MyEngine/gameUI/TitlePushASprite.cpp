#include "TitlePushASprite.h"

TitlePushASprite* TitlePushASprite::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//PushAスプライトのインスタンスを生成
	TitlePushASprite* titlePushASprite = new TitlePushASprite();
	if (titlePushASprite == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!titlePushASprite->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete titlePushASprite;
		assert(0);
		return nullptr;
	}

	//座標をセット
	titlePushASprite->position = position;

	//大きさをセット
	titlePushASprite->size = size;
	titlePushASprite->texSize = size;

	return titlePushASprite;
}

void TitlePushASprite::Update()
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

void TitlePushASprite::Draw()
{
	//描画状態でなければ抜ける
	if (!isDraw) { return; }

	//スプライト描画
	Sprite::Draw();
}

void TitlePushASprite::ChangeFlashingSpeed()
{
	//点滅の速さを変える
	drawModeTime = 3;
	flashingTime = 3;
}

void TitlePushASprite::Flashing()
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

void TitlePushASprite::DrawMode()
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
