#pragma once
#include "Sprite.h"

/// <summary>
/// �����N�����X�v���C�g
/// </summary>
class RankWordSprite : public Sprite
{
public:
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns>�����N�����X�v���C�g</returns>
	static RankWordSprite* Create(UINT texNumber, const Vector2& position, const Vector2& size);
};