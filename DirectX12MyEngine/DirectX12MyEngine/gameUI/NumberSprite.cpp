#include "NumberSprite.h"

NumberSprite* NumberSprite::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//数字スプライトのインスタンスを生成
	NumberSprite* numberSprite = new NumberSprite();
	if (numberSprite == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!numberSprite->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete numberSprite;
		assert(0);
		return nullptr;
	}

	//座標をセット
	numberSprite->position = position;

	//大きさをセット
	numberSprite->size = size;
	numberSprite->texSize = size;

	return numberSprite;
}

void NumberSprite::Update()
{
	//表示する数字を更新
	UpdateNumber();

	//スプライト更新
	Sprite::Update();
}

void NumberSprite::UpdateNumber()
{
	//スプライトの左上切り出し座標をテクスチャサイズ * 数字で算出する
	texLeftTop.x = texSize.x * number;
}
