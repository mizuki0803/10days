#pragma once
#include "Sprite.h"

/// <summary>
/// �����N�X�v���C�g
/// </summary>
class LankSprite : public Sprite
{
public:
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns>�����N�X�v���C�g</returns>
	static LankSprite* Create(UINT texNumber, const Vector2& position, const Vector2& size);

public: //�����o�֐�
	/// <summary>
	/// �\�����郉���N���Z�b�g
	/// </summary>
	/// <param name="lank">�\������ԍ�(S�`C)</param>
	void SetLank(const int lank);

private: //�����o�ϐ�
	//�\�����郉���N
	int lank = 0;
};