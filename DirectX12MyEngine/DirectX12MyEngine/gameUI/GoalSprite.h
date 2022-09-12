#pragma once
#include "Sprite.h"

/// <summary>
/// �S�[���X�v���C�g
/// </summary>
class GoalSprite : public Sprite
{
public:
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns>�����N�X�v���C�g</returns>
	static GoalSprite* Create(UINT texNumber, const Vector2& size);

public: //�����o�֐�
	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �ړ��J�n
	/// </summary>
	void MoveStart();

public: //�����o�֐�
	/// <summary>
	/// �ړ�
	/// </summary>
	void Move();

private: //�����o�ϐ�
	//�ړ����邩
	bool isMove = false;
	//�ړ����ԃ^�C�}�[
	int32_t moveTimer = 0;
};