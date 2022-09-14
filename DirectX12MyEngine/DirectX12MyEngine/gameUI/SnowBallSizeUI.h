#pragma once
#include "NumberSprite.h"
#include "MiniMapSnowBall.h"
#include <vector>
#include <memory>

/// <summary>
/// ��ʂ̑傫����\������UI
/// </summary>
class SnowBallSizeUI
{
public:
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns>��ʂ̑傫����\������UI</returns>
	static SnowBallSizeUI* Create(UINT numberTexNumber, UINT snowBallTexNumber, const Vector2& position, const Vector2& size, const Vector2& texSize);

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	bool Initialize(UINT numberTexNumber, UINT snowBallTexNumber, const Vector2& position, const Vector2& size, const Vector2& texSize);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(const float snowBallSize);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private: //�����o�֐�
	/// <summary>
	/// �����X�v���C�g�̐�����ύX
	/// </summary>
	void ChangeNumber(const float snowBallSize);

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