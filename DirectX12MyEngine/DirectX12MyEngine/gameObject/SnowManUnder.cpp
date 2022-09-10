#include "SnowManUnder.h"

SnowManUnder* SnowManUnder::Create(ObjModel* model, const Vector3& position, const Vector3& scale)
{
	//�Ⴞ���(��)�̃C���X�^���X�𐶐�
	SnowManUnder* snowManUnder = new SnowManUnder();
	if (snowManUnder == nullptr) {
		return nullptr;
	}

	//���f�����Z�b�g
	assert(model);
	snowManUnder->model = model;

	// ������
	if (!snowManUnder->Initialize()) {
		delete snowManUnder;
		assert(0);
		return nullptr;
	}

	//���W���Z�b�g
	snowManUnder->position = position;

	//���W���Z�b�g
	snowManUnder->scale = scale;

	return snowManUnder;
}
