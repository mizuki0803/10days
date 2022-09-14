#pragma once
#include "ObjObject3d.h"
#include "Player.h"

/// <summary>
/// ��
/// </summary>
class SnowWall : public ObjObject3d
{
public:
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <returns>��</returns>
	static SnowWall* Create(ObjModel* model, const Vector3& position, const Vector3& rotation);

	//setter
	static void SetPlayer(Player* player) { SnowWall::player = player; }

public: //�����o�֐�
	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	//getter
	const bool GetIsDead() { return isDead; }

public: //�����o�֐�
	/// <summary>
	/// �`��͈͂��`�F�b�N
	/// </summary>
	void CheckIsDraw();

	/// <summary>
	/// �`��͈͂��`�F�b�N
	/// </summary>
	void CheckIsDead();

private: //�ÓI�����o�ϐ�
	//���
	static Player* player;

private: //�����o�ϐ�
	//�`��t���O
	bool isDraw = false;
	//���S�t���O
	bool isDead = false;
};