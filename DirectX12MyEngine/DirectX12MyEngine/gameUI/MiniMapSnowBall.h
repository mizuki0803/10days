#pragma once
#include "Sprite.h"
#include "Player.h"

/// <summary>
/// �~�j�}�b�v�̐��
/// </summary>
class MiniMapSnowBall : public Sprite
{
public:
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns>�~�~�j�}�b�v�̐��</returns>
	static MiniMapSnowBall* Create(UINT texNumber, const Vector2& position, const Vector2& size);
};