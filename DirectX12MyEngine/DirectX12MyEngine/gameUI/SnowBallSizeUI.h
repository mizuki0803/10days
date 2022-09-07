#pragma once
#include "NumberSprite.h"
#include "Player.h"

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
	static SnowBallSizeUI* Create(UINT texNumber, const Vector2& position, const Vector2& size);

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	bool Initialize(UINT texNumber, const Vector2& position, const Vector2& size);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	//getter

	//setter
	void SetPlayer(Player* player) { this->player = player; }

private: //�����o�֐�
	/// <summary>
	/// �����X�v���C�g�̐�����ύX
	/// </summary>
	void ChangeNumber();

private: //�ÓI�����o�ϐ�
	static const int numberDigit = 5;

private: //�����o�ϐ�
	//���
	Player* player = nullptr;
	//�����X�v���C�g
	std::vector<std::unique_ptr<NumberSprite>> numberSprites;
};