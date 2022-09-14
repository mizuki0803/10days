#pragma once
#include "ObjObject3d.h"
#include "Vector2.h"
#include <memory>

/// <summary>
/// ���@
/// </summary>
class Player : public ObjObject3d
{
public: //�ÓI�����o�֐�
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <returns>���@</returns>
	static Player* Create(ObjModel* model);

	//getter
	static const Vector2& GetRotLimit() { return rotLimit; }

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	bool Initialize() override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�(�G�Ȃǃ_���[�W����炤)
	/// </summary>
	void OnCollisionDamage(const Vector3& subjectPos);

	//getter
	Vector3 GetWorldPos();
	const bool GetIsDamage() { return isDamage; }
	const Vector3& GetKnockbackVel() { return knockbackVel; }

	//setter
	void SetIsGameStart(const bool isGameStart) { this->isGameStart = isGameStart; }
	void SetIsGoal(const bool isGoal) { this->isGoal = isGoal; }

protected: //�����o�֐�
	/// <summary>
	/// �_���[�W����炤
	/// </summary>
	void Damage();

	/// <summary>
	/// ��]
	/// </summary>
	void Rotate();

	/// <summary>
	/// �ړ�
	/// </summary>
	void Move();

	/// <summary>
	/// �m�b�N�o�b�N�����Z�b�g
	/// </summary>
	void SetKnockback(const Vector3& subjectPos);

	/// <summary>
	/// �m�b�N�o�b�N
	/// </summary>
	void Knockback();

	/// <summary>
	/// �m�b�N�o�b�N
	/// </summary>
	void ChangeScale();

	/// <summary>
	/// �ړ���Z�̌v�Z
	/// </summary>
	float VelicityZ(float time);


protected: //�ÓI�����o�ϐ�
	//���@�̉�]���E
	static const Vector2 rotLimit;
	//�X�s�[�h�Ɋ|����l
	const float speedRate = 0.02f;
	//scale�Ɋ|����l
	const float scaleRate = 0.0032f;

protected: //�����o�ϐ�
	//�Q�[���J�n��
	bool isGameStart = false;
	//�S�[��������
	bool isGoal = false;
	//�_���[�W�t���O
	bool isDamage = false;
	//�m�b�N�o�b�N�p�^�C�}�[
	int32_t knockbackTimer = 0;
	//�m�b�N�o�b�N����
	Vector3 knockbackVec;
	//�m�b�N�o�b�N���x
	Vector3 knockbackVel;
	//�m�b�N�o�b�N���̑傫��
	float knockbackScale;
	//����
	float time = 0.00f;
	//�T�C�Y
	float ballScale = 1.0f;
	bool isDam = false;
};
