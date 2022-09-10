#include "Rock.h"

Rock* Rock::Create(ObjModel* model, const Vector3& position)
{
	//岩のインスタンスを生成
	Rock* rock = new Rock();
	if (rock == nullptr) {
		return nullptr;
	}

	//モデルをセット
	assert(model);
	rock->model = model;

	// 初期化
	if (!rock->Initialize()) {
		delete rock;
		assert(0);
		return nullptr;
	}

	//座標をセット
	rock->position = position;

	//座標をセット
	rock->scale = { 2.5f, 2.5f, 2.5f };

	return rock;
}
