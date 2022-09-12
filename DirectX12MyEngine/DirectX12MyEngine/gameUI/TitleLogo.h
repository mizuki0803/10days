#pragma once
#include "Sprite.h"

/// <summary>
/// タイトルロゴ
/// </summary>
class TitleLogo : public Sprite
{
public: //静的メンバ関数
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <returns>タイトルロゴ</returns>
	static TitleLogo* Create(UINT texNumber, const Vector2& position, const Vector2& size);
};