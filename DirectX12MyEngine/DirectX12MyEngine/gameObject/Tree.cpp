#include "Tree.h"

Tree* Tree::Create(ObjModel* model, const Vector3& position)
{
	//木のインスタンスを生成
	Tree* tree = new Tree();
	if (tree == nullptr) {
		return nullptr;
	}

	//モデルをセット
	assert(model);
	tree->model = model;

	// 初期化
	if (!tree->Initialize()) {
		delete tree;
		assert(0);
		return nullptr;
	}

	//座標をセット
	tree->position = position;

	//座標をセット
	tree->scale = { 2.5f, 2.5f, 2.5f };

	return tree;
}
