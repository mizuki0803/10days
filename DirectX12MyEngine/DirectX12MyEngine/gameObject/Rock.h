#pragma once
#include "ObjObject3d.h"

/// <summary>
/// ��
/// </summary>
class Rock : public ObjObject3d
{
public: //�ÓI�����o�֐�
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <returns>��</returns>
	static Rock* Create(ObjModel* model, const Vector3& position);

public: //�����o�֐�
	//getter
	Vector3 GetWorldPos();
	bool GetIsDead() const { return isDead; }

private: //�����o�ϐ�
	//���S�t���O
	bool isDead = false;
};
