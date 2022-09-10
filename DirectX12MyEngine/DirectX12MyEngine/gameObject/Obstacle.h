#pragma once
#include "ObjObject3d.h"
#include "Player.h"

/// <summary>
/// ��Q��
/// </summary>
class Obstacle : public ObjObject3d
{
public: //�ÓI�����o�֐�

	//setter
	static void SetPlayer(Player* player) { Obstacle::player = player; }

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
	Vector3 GetWorldPos();
	const bool GetIsDraw() { return isDraw; }
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