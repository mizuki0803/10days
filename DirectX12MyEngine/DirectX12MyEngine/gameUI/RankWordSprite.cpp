#include "RankWordSprite.h"

RankWordSprite* RankWordSprite::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//ランク文字スプライトのインスタンスを生成
	RankWordSprite* rankWordSprite = new RankWordSprite();
	if (rankWordSprite == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!rankWordSprite->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete rankWordSprite;
		assert(0);
		return nullptr;
	}

	//座標をセット
	rankWordSprite->position = position;

	//大きさをセット
	rankWordSprite->size = size;
	rankWordSprite->texSize = { 926, 600 };

	return rankWordSprite;
}
