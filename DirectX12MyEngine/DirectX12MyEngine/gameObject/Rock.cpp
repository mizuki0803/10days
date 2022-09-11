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

	//���W���Z�b�g
	rock->scale = { 2.5f, 2.5f, 2.5f };

	return rock;
}
