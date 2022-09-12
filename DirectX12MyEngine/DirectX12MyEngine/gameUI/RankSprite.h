#pragma once
#include "Sprite.h"

/// <summary>
/// �����N�X�v���C�g
/// </summary>
class RankSprite : public Sprite
{
public:
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns>�����N�X�v���C�g</returns>
	static RankSprite* Create(UINT texNumber, const Vector2& position, const Vector2& size);

public: //�����o�֐�
	/// <summary>
	/// �\�����郉���N���Z�b�g
	/// </summary>
	/// <param name="rank">�\������ԍ�(S�`C)</param>
	void SetRank(const int rank);

private: //�����o�ϐ�
	//�\�����郉���N
	int rank = 0;
};