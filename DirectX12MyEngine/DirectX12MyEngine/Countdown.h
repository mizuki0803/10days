#pragma once
#include "NumberSprite.h"
#include <vector>
#include <memory>

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
	static Countdown* Create(UINT texNumber, const Vector2& position, const Vector2& size, const Vector2& texSize);

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	bool Initialize(UINT texNumber, const Vector2& position, const Vector2& size, const Vector2& texSize);

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

	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();


	//getter
	bool GetIsStart() { return isStart; }

public:
	const int center = 640;
	const int leftSide = -200;
	const int rightSide = 1480;

private: //�����o�֐�
	/// <summary>
	/// �����X�v���C�g�̐�����ύX
	/// </summary>
	void ChangeNumber();

private: //�����o�ϐ�
	Vector2 pos = { 0, 0 };
	//�����X�v���C�g
	std::vector<std::unique_ptr<NumberSprite>> numberSprites;

	//��ʃQ�[���p�ϐ�
	//�Q�[���ɓ���t���O
	bool isStart = false;
	//�J�E���g�_�E���`��p�t���O
	bool isOne = false;
	bool isTwo = false;
	bool isThree = false;
	//�J�E���g�_�E���p�̕ϐ�
	int countTime = 300;
	float onePos;
	float twoPos;
	float threePos;
	float easeTimer;
	float easeTimer2;
	float easeTimer3;
	float timeRate;
};