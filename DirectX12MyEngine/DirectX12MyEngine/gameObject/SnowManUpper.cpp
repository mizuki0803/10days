#include "SnowManUpper.h"

SnowManUpper* SnowManUpper::Create(ObjModel* model, const Vector3& position, const Vector3& scale)
{
	//雪だるま(上)のインスタンスを生成
	SnowManUpper* snowManUpper = new SnowManUpper();
	if (snowManUpper == nullptr) {
		return nullptr;
	}

	//モデルをセット
	assert(model);
	snowManUpper->model = model;

	// 初期化
	if (!snowManUpper->Initialize()) {
		delete snowManUpper;
		assert(0);
		return nullptr;
	}

	//座標をセット
	snowManUpper->position = position;

	//座標をセット
	snowManUpper->scale = scale;

	return snowManUpper;
}
