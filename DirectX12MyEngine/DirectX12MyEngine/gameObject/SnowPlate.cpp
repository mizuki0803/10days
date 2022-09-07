#include "SnowPlate.h"

SnowPlate* SnowPlate::Create(ObjModel* model, const Vector3& position)
{
	//雪のフィールドのインスタンスを生成
	SnowPlate* snowPlate = new SnowPlate();
	if (snowPlate == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!snowPlate->Initialize()) {
		delete snowPlate;
		assert(0);
		return nullptr;
	}

	//モデルをセット
	assert(model);
	snowPlate->model = model;

	//座標をセット
	snowPlate->position = position;

	//大きさをセット
	snowPlate->scale = { 5, 5, 5 };

	//色をセット
	snowPlate->color = { 0.6f, 0.6f, 0.6f, 1 };

	return snowPlate;
}
