#pragma once
#include "SnowManUpper.h"
#include "SnowManUnder.h"

/// <summary>
/// �Ⴞ���
/// </summary>
class SnowMan
{
public: //�ÓI�����o�֐�
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <returns>�Ⴞ���(��)</returns>
	static SnowMan* Create(ObjModel* upperModel, ObjModel* underModel, const Vector3& position, const float underSize);

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	bool Initialize(ObjModel* upperModel, ObjModel* underModel, const Vector3& position, const float underSize);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private: //�����o�ϐ�
	//�Ⴞ���(��)
	std::unique_ptr<SnowManUpper> snowManUpper;
	//�Ⴞ���(��)
	std::unique_ptr<SnowManUnder> snowManUnder;
};
