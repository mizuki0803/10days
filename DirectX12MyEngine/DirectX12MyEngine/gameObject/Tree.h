#pragma once
#include "Obstacle.h"

/// <summary>
/// ��
/// </summary>
class Tree : public Obstacle
{
public: //�ÓI�����o�֐�
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <returns>��</returns>
	static Tree* Create(ObjModel* model, const Vector3& position);
};
