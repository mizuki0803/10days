#include "SnowManUnder.h"

SnowManUnder* SnowManUnder::Create(ObjModel* model, const Vector3& position, const Vector3& scale)
{
	//雪だるま(下)のインスタンスを生成
	SnowManUnder* snowManUnder = new SnowManUnder();
	if (snowManUnder == nullptr) {
		return nullptr;
	}

	//モデルをセット
	assert(model);
	snowManUnder->model = model;

	// 初期化
	if (!snowManUnder->Initialize()) {
		delete snowManUnder;
		assert(0);
		return nullptr;
	}

	//座標をセット
	snowManUnder->position = position;

	//座標をセット
	snowManUnder->scale = scale;

	return snowManUnder;
}
