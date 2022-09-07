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

	return rock;
}

Vector3 Rock::GetWorldPos()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//平行移動成分を取得
	worldPos.x = matWorld.r[3].m128_f32[0];
	worldPos.y = matWorld.r[3].m128_f32[1];
	worldPos.z = matWorld.r[3].m128_f32[2];

	return worldPos;
}
