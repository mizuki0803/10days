#pragma once
#include "Sprite.h"

/// <summary>
/// ���U���g�V�[��PushA�X�v���C�g
/// </summary>
class ResultPushASprite : public Sprite
{
public: //�ÓI�����o�֐�
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns>PushA�X�v���C�g</returns>
	static ResultPushASprite* Create(UINT texNumber, const Vector2& position, const Vector2& size);
};