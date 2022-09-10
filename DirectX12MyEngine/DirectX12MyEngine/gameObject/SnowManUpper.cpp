#include "SnowManUpper.h"

SnowManUpper* SnowManUpper::Create(ObjModel* model, const Vector3& position, const Vector3& scale)
{
	//�Ⴞ���(��)�̃C���X�^���X�𐶐�
	SnowManUpper* snowManUpper = new SnowManUpper();
	if (snowManUpper == nullptr) {
		return nullptr;
	}

	//���f�����Z�b�g
	assert(model);
	snowManUpper->model = model;

	// ������
	if (!snowManUpper->Initialize()) {
		delete snowManUpper;
		assert(0);
		return nullptr;
	}

	//���W���Z�b�g
	snowManUpper->position = position;

	//���W���Z�b�g
	snowManUpper->scale = scale;

	return snowManUpper;
}
