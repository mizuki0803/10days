#pragma once
#include "MiniMapSprite.h"
#include "MiniMapSnowBall.h"

/// <summary>
/// �~�j�}�b�v��UI
/// </summary>
class MiniMap
{
public:
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns>�~�j�}�b�v��UI</returns>
	static MiniMap* Create(UINT miniMapTexNumber, UINT snowBallTexNumber, const Vector2& position, const Vector2& size, const float goalPos);

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	bool Initialize(UINT miniMapTexNumber, UINT snowBallTexNumber, const Vector2& position, const Vector2& size);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(const float playerPosZ);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private: //�����o�֐�
	/// <summary>
	/// ��ʂ̍��W��ύX
	/// </summary>
	void ChangeSnowBallPos(const float playerPosZ);

private: //�����o�ϐ�
	//�S�[�����W
	float goalPos = 0;
	//�}�b�v�X�v���C�g
	std::unique_ptr<MiniMapSprite> miniMapSprite;
	//�}�b�v�X�v���C�g
	std::unique_ptr<MiniMapSnowBall> miniMapSnowBall;
};
