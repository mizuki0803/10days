#pragma once
#include "NumberSprite.h"
#include <vector>
#include <memory>

/// <summary>
/// �ŏI�I�Ȑ�ʂ̑傫����\������UI
/// </summary>
class FinalSnowBallSizeUI
{
public:
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns>�ŏI�I�Ȑ�ʂ̑傫����\������UI</returns>
	static FinalSnowBallSizeUI* Create(UINT texNumber, const Vector2& position, const Vector2& size, const float finalSnowBallSize);

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	bool Initialize(UINT texNumber, const Vector2& position, const Vector2& size, const float finalSnowBallSize);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private: //�����o�֐�
	/// <summary>
	/// �����X�v���C�g�̐�����ύX
	/// </summary>
	void ChangeNumber(const float finalSnowBallSize);

private: //�ÓI�����o�ϐ�
	static const int numberDigit = 5;

private: //�����o�ϐ�
	//�����X�v���C�g
	std::vector<std::unique_ptr<NumberSprite>> numberSprites;
};