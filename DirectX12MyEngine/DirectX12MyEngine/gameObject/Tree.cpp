#include "Tree.h"

Tree* Tree::Create(ObjModel* model, const Vector3& position)
{
	//�؂̃C���X�^���X�𐶐�
	Tree* tree = new Tree();
	if (tree == nullptr) {
		return nullptr;
	}

	//���f�����Z�b�g
	assert(model);
	tree->model = model;

	// ������
	if (!tree->Initialize()) {
		delete tree;
		assert(0);
		return nullptr;
	}

	//���W���Z�b�g
	tree->position = position;

	//���W���Z�b�g
	tree->scale = { 2.5f, 2.5f, 2.5f };

	//��]���Z�b�g
	tree->rotation = { -30, 0, 0 };

	return tree;
}
