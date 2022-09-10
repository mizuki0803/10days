#pragma once
#include "Sprite.h"
#include "Player.h"

/// <summary>
/// ミニマップの雪玉
/// </summary>
class MiniMapSnowBall : public Sprite
{
public:
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <returns>ミミニマップの雪玉</returns>
	static MiniMapSnowBall* Create(UINT texNumber, const Vector2& position, const Vector2& size);
};