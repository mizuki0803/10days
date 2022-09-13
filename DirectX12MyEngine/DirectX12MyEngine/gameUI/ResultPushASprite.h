#pragma once
#include "Sprite.h"

/// <summary>
/// リザルトシーンPushAスプライト
/// </summary>
class ResultPushASprite : public Sprite
{
public: //静的メンバ関数
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <returns>PushAスプライト</returns>
	static ResultPushASprite* Create(UINT texNumber, const Vector2& position, const Vector2& size);
};