#include "ResultPushASprite.h"

ResultPushASprite* ResultPushASprite::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//PushAスプライトのインスタンスを生成
	ResultPushASprite* resultPushASprite = new ResultPushASprite();
	if (resultPushASprite == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!resultPushASprite->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete resultPushASprite;
		assert(0);
		return nullptr;
	}

	//座標をセット
	resultPushASprite->position = position;

	//大きさをセット
	resultPushASprite->size = size;
	resultPushASprite->texSize = size;

	return resultPushASprite;
}
