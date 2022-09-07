#include "Rock.h"

Rock* Rock::Create(ObjModel* model, const Vector3& position)
{
	//��̃C���X�^���X�𐶐�
	Rock* rock = new Rock();
	if (rock == nullptr) {
		return nullptr;
	}

	//���f�����Z�b�g
	assert(model);
	rock->model = model;

	// ������
	if (!rock->Initialize()) {
		delete rock;
		assert(0);
		return nullptr;
	}

	//���W���Z�b�g
	rock->position = position;

	return rock;
}

Vector3 Rock::GetWorldPos()
{
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���s�ړ��������擾
	worldPos.x = matWorld.r[3].m128_f32[0];
	worldPos.y = matWorld.r[3].m128_f32[1];
	worldPos.z = matWorld.r[3].m128_f32[2];

	return worldPos;
}
