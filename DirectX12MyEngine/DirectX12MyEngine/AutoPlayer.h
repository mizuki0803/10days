#pragma once
#pragma once
#include "ObjObject3d.h"
#include "Vector2.h"
#include <memory>

//�Q�[���V�[���̑O���錾
class GameScene;

/// <summary>
/// ���@
/// </summary>
class AutoPlayer : public ObjObject3d
{
public: //�ÓI�����o�֐�
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <returns>���@</returns>
	static AutoPlayer* Create(ObjModel* model);

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
	const int GetHP() { return HP; }
	const bool GetIsDamage() { return isDamage; }
	const bool GetIsDead() { return isDead; }
	const Vector3& GetKnockbackVel() { return knockbackVel; }

private: //�����o�֐�
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


private: //�ÓI�����o�ϐ�
	//���@�̉�]���E
	static const Vector2 rotLimit;
	//�ő�̗�
	static const int maxHP = 100;
	//�X�s�[�h�Ɋ|����l
	const float speedRate = 0.02f;
	//scale�Ɋ|����l
	const float scaleRate = 0.005f;

private: //�����o�ϐ�
	//�̗�
	int HP = maxHP;
	//�_���[�W�t���O
	bool isDamage = false;
	//�m�b�N�o�b�N�p�^�C�}�[
	int32_t knockbackTimer = 0;
	//�m�b�N�o�b�N����
	Vector3 knockbackVec;
	//�m�b�N�o�b�N���x
	Vector3 knockbackVel;
	//���S�t���O
	bool isDead = false;
	//z��������]���E��]��
	bool isRotZRight = true;
	//z��������]�p
	float swayZ = 0.0f;
	//����
	float time = 0.00f;
	//�S�[���̈ʒu
	float goalPosition = 1500.0f;
	//�T�C�Y
	float ballScale = 1.0f;
	//�^�C�}�[
	int timer = 0;
};
