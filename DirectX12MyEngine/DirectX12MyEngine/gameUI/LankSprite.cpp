#include "LankSprite.h"

LankSprite* LankSprite::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//ランクスプライトのインスタンスを生成
	LankSprite* lankSprite = new LankSprite();
	if (lankSprite == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!lankSprite->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete lankSprite;
		assert(0);
		return nullptr;
	}

	//座標をセット
	lankSprite->position = position;

	//大きさをセット
	lankSprite->size = size;
	lankSprite->texSize = size;

	return lankSprite;
}

void LankSprite::SetLank(const int lank)
{
	//ランクを更新
	this->lank = lank;

	//スプライトの左上切り出し座標をテクスチャサイズ * ランク(数字)で算出する
	texLeftTop.x = texSize.x * lank;
}
