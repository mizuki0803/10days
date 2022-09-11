#pragma once
#include "Sprite.h"

/// <summary>
/// ミニマップスプライト
/// </summary>
class MiniMapSprite : public Sprite
{
public:
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <returns>ミニマップスプライト</returns>
	static MiniMapSprite* Create(UINT texNumber, const Vector2& position, const Vector2& size);
};