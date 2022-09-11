#pragma once
#include "LankSprite.h"
#include <memory>

/// <summary>
/// ��ʂ̑傫�������N��\������UI
/// </summary>
class SnowBallLankUI
{
public:
	enum class Lank 
	{
		S,
		A,
		B,
		C,
		None,
	};

public:
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns>��ʂ̑傫�������N��\������UI</returns>
	static SnowBallLankUI* Create(UINT texNumber, const Vector2& position, const Vector2& size, const float snowBallSize);

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	bool Initialize(UINT texNumber, const Vector2& position, const Vector2& size, const float snowBallSize);

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
	/// �����N���m��
	/// </summary>
	void SetLank(const float snowBallSize);

private: //�����o�ϐ�
	//�����N�X�v���C�g
	std::unique_ptr<LankSprite> lankSprite;
	//�����N
	Lank lank = Lank::None;
};