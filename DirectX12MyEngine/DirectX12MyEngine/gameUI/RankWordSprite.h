#pragma once
#include "Sprite.h"

/// <summary>
/// ランク文字スプライト
/// </summary>
class RankWordSprite : public Sprite
{
public:
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <returns>ランク文字スプライト</returns>
	static RankWordSprite* Create(UINT texNumber, const Vector2& position, const Vector2& size);
};