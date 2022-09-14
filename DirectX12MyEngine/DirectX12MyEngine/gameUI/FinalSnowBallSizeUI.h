#pragma once
#include "NumberSprite.h"
#include "MiniMapSnowBall.h"
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
	static FinalSnowBallSizeUI* Create(UINT numberTexNumber, UINT snowBallTexNumber, const Vector2& position, const Vector2& size, const Vector2& texSize, const float finalSnowBallSize);

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	bool Initialize(UINT numberTexNumber, UINT snowBallTexNumber, const Vector2& position, const Vector2& size, const Vector2& texSize, const float finalSnowBallSize);

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
	/// <summary>
	/// ��ʃX�v���C�g�̑傫���ύX
	/// </summary>
	void ChangeSnowBallSize(const float snowBallSize);

private: //�ÓI�����o�ϐ�
	static const int numberDigit = 5;

private: //�����o�ϐ�
	//�����X�v���C�g
	std::vector<std::unique_ptr<NumberSprite>> numberSprites;
	//��ʃX�v���C�g
	std::unique_ptr<MiniMapSnowBall> snowBallSprite;
};