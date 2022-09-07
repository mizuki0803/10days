#include "SnowPlate.h"

SnowPlate* SnowPlate::Create(ObjModel* model, const Vector3& position)
{
	//��̃t�B�[���h�̃C���X�^���X�𐶐�
	SnowPlate* snowPlate = new SnowPlate();
	if (snowPlate == nullptr) {
		return nullptr;
	}

	// ������
	if (!snowPlate->Initialize()) {
		delete snowPlate;
		assert(0);
		return nullptr;
	}

	//���f�����Z�b�g
	assert(model);
	snowPlate->model = model;

	//���W���Z�b�g
	snowPlate->position = position;

	//�傫�����Z�b�g
	snowPlate->scale = { 5, 5, 5 };

	//�F���Z�b�g
	snowPlate->color = { 0.6f, 0.6f, 0.6f, 1 };

	return snowPlate;
}
