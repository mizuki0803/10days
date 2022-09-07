#pragma once
#include "Sprite.h"

/// <summary>
/// �����X�v���C�g
/// </summary>
class NumberSprite : public Sprite
{
public:
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns>�����X�v���C�g</returns>
	static NumberSprite* Create(UINT texNumber, const Vector2& position, const Vector2& size);

public: //�����o�֐�
	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �\������ԍ����X�V
	/// </summary>
	void UpdateNumber();

	/// <summary>
	/// �\������ԍ����Z�b�g
	/// </summary>
	/// <param name="number">�\������ԍ�(0�`9, 10��.)</param>
	void SetNumber(const int number) { this->number = number; }

private: //�����o�ϐ�
	//�\������ԍ�
	int number = 0;
};