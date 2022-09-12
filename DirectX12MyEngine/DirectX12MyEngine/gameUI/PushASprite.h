#pragma once
#include "Sprite.h"

/// <summary>
/// PushA�X�v���C�g
/// </summary>
class PushASprite : public Sprite
{
public: //�ÓI�����o�֐�
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns>PushA�X�v���C�g</returns>
	static PushASprite* Create(UINT texNumber, const Vector2& position, const Vector2& size);

public: //�����o�֐�
	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �_�ł̑�����ς���
	/// </summary>
	void ChangeFlashingSpeed();

private: //�����o�֐�
	/// <summary>
	/// �_��
	/// </summary>
	void Flashing();

	/// <summary>
	/// �`����
	/// </summary>
	void DrawMode();

private: //�����o�ϐ�
	//�`�悷�邩
	bool isDraw = true;
	//�`���Ԏ���
	int drawModeTime = 50;
	//�`���Ԃ̎��ԃ^�C�}�[
	int32_t drawModeTimer = 0;
	//�_�ł̑���
	int flashingTime = 50;
	//�_�ŗp�^�C�}�[
	int32_t flashingTimer = 0;
};