#pragma once
#include "RankSprite.h"
#include "RankWordSprite.h"
#include <memory>

/// <summary>
/// ��ʂ̑傫�������N��\������UI
/// </summary>
class SnowBallRankUI
{
public:
	enum class Rank
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
	static SnowBallRankUI* Create(UINT rankTexNumber, UINT wordTexNumber, const Vector2& position, const float snowBallSize);

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	bool Initialize(UINT rankTexNumber, UINT wordTexNumber, const Vector2& position, const float snowBallSize);

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
	void SetRank(const float snowBallSize);

private: //�����o�ϐ�
	//�����N�X�v���C�g
	std::unique_ptr<RankSprite> rankSprite;
	//�����́u�����N�v�X�v���C�g
	std::unique_ptr<RankWordSprite> rankWordSprite;
	//�����N
	Rank rank = Rank::None;
};