#pragma once
#include "Obstacle.h"

/// <summary>
/// �S�[���|�[��
/// </summary>
class GoalPole : public Obstacle
{
public: //�ÓI�����o�֐�
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <returns>�S�[���|�[��</returns>
	static GoalPole* Create(ObjModel* model, const Vector3& position);
};
