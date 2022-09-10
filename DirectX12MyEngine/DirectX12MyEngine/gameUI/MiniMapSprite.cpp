#include "MiniMapSprite.h"

MiniMapSprite* MiniMapSprite::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//ミニマップスプライトのインスタンスを生成
	MiniMapSprite* miniMapSprite = new MiniMapSprite();
	if (miniMapSprite == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!miniMapSprite->Initialize(texNumber, { 0.5f, 0 }, false, false)) {
		delete miniMapSprite;
		assert(0);
		return nullptr;
	}

	//座標をセット
	miniMapSprite->position = position;

	//大きさをセット
	miniMapSprite->size = size;
	miniMapSprite->texSize = size;

	return miniMapSprite;
}
