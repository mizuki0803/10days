#pragma once
#include "SnowEffect.h"

/// <summary>
/// ��ʃG�t�F�N�g�}�l�[�W���[
/// </summary>
class SnowEffectManager
{
public: //�ÓI�����o�֐�
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <returns>�V��</returns>
	static SnowEffectManager* Create();

	//setter
	static void SetModel(ObjModel* model) { SnowEffectManager::model = model; }

public: //�����o�֐�
	/// <summary>
	/// �X�V
	/// </summary>
	/// <returns></returns>
	void Update();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <returns></returns>
	void Draw();

	/// <summary>
	/// �G�t�F�N�g�ǉ�
	/// </summary>
	void AddSnowEffect(const Vector3& position);

private: //�ÓI�����o�ϐ�
	static ObjModel* model;

private: //�����o�ϐ�
	//��ʃ��X�g
	std::list<std::unique_ptr<SnowEffect>> snowEffects;
};