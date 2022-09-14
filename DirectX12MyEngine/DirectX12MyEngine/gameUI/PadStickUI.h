#pragma once
#include "Sprite.h"

/// <summary>
/// �p�b�h�X�e�B�b�NUI
/// </summary>
class PadStickUI : public Sprite
{
public:
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns>�p�b�h�X�e�B�b�NUI</returns>
	static PadStickUI* Create(UINT texNumber, const Vector2& position, const Vector2& size);

public: //�����o�֐�
	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

private:
	/// <summary>
	/// �X�e�B�b�N�𓮂���
	/// </summary>
	void StickMove();

private:
	//�`�悷��A�ԉ摜�̔ԍ�
	int drawNum = 0;
	//�X�v���C�g�̕`��ύX�^�C�}�[
	int32_t changeTimer = 0;
};