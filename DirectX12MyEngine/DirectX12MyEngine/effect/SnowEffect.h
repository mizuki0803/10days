#pragma once
#include "ObjObject3d.h"

/// <summary>
/// ��ʃG�t�F�N�g
/// </summary>
class SnowEffect : public ObjObject3d
{
public:
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <returns>�V��</returns>
	static SnowEffect* Create(ObjModel* model, const Vector3& position, const float scale, const Vector3& velocity);

public:
	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	//getter
	const bool GetIsDead() { return isDead; }

private:
	/// <summary>
	/// �ړ�������
	/// </summary>
	void Move();

private:
	//���S�t���O
	bool isDead = false;
	//�ړ����x
	Vector3 velocity;
};