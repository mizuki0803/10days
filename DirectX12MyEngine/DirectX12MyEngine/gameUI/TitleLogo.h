#pragma once
#include "Sprite.h"

/// <summary>
/// �^�C�g�����S
/// </summary>
class TitleLogo : public Sprite
{
public: //�ÓI�����o�֐�
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns>�^�C�g�����S</returns>
	static TitleLogo* Create(UINT texNumber, const Vector2& position, const Vector2& size);
};