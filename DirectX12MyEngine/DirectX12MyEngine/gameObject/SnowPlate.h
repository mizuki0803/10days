#pragma once
#include "ObjObject3d.h"

/// <summary>
/// ��̃t�B�[���h
/// </summary>
class SnowPlate : public ObjObject3d
{
public:
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <returns>��̃t�B�[���h</returns>
	static SnowPlate* Create(ObjModel* model, const Vector3& position);
};