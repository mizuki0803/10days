#pragma once
#include "Sprite.h"

/// <summary>
/// �~�j�}�b�v�X�v���C�g
/// </summary>
class MiniMapSprite : public Sprite
{
public:
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns>�~�j�}�b�v�X�v���C�g</returns>
	static MiniMapSprite* Create(UINT texNumber, const Vector2& position, const Vector2& size);
};