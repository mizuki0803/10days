#pragma once
#include "NumberSprite.h"
#include "Player.h"

/// <summary>
/// ��ʂ̑傫����\������UI
/// </summary>
class Countdown
{
public:
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns>��ʂ̑傫����\������UI</returns>
	static Countdown* Create(UINT texNumber, const Vector2& position, const Vector2& size);

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

	/// <summary>
	/// �X�^�[�g�O����
	/// </summary>
	void BeforeStart();

	//getter
	bool GetIsStart() { return isStart; }


private: //�����o�֐�
	/// <summary>
	/// �����X�v���C�g�̐�����ύX
	/// </summary>
	void ChangeNumber();

private: //�����o�ϐ�
	//���
	Player* player = nullptr;
	//�����X�v���C�g
	std::vector<std::unique_ptr<NumberSprite>> numberSprites;

	//��ʃQ�[���p�ϐ�
	//�Q�[���ɓ���t���O
	bool isStart = false;
	//�J�E���g�_�E���`��p�t���O
	bool isOne = false;
	bool isTwo = false;
	bool isThree = false;
	//�J�E���g�_�E���p�̃^�C�}�[
	int countTime = 300;
};