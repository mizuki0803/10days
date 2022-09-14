#include "GoalPole.h"

GoalPole* GoalPole::Create(ObjModel* model, const Vector3& position)
{
	//�S�[���|�[���̃C���X�^���X�𐶐�
	GoalPole* goalPole = new GoalPole();
	if (goalPole == nullptr) {
		return nullptr;
	}

	//���f�����Z�b�g
	assert(model);
	goalPole->model = model;

	// ������
	if (!goalPole->Initialize()) {
		delete goalPole;
		assert(0);
		return nullptr;
	}

	//���W���Z�b�g
	goalPole->position = position;

	//���W���Z�b�g
	goalPole->scale = { 5, 5, 5 };

	return goalPole;
}
