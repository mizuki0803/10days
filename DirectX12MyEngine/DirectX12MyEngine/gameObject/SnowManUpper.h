#pragma once
#include "ObjObject3d.h"

/// <summary>
/// �Ⴞ���(��)
/// </summary>
class SnowManUpper : public ObjObject3d
{
public: //�ÓI�����o�֐�
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <returns>�Ⴞ���(��)</returns>
	static SnowManUpper* Create(ObjModel* model, const Vector3& position, const Vector3& scale);
};
