#include "SnowEffect.h"

SnowEffect* SnowEffect::Create(ObjModel* model, const Vector3& position, const float scale, const Vector3& velocity)
{
	//雪玉エフェクトのインスタンスを生成
	SnowEffect* snowEffect = new SnowEffect();
	if (snowEffect == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!snowEffect->Initialize()) {
		delete snowEffect;
		assert(0);
		return nullptr;
	}

	//モデルをセット
	assert(model);
	snowEffect->model = model;

	//座標をセット
	snowEffect->position = position;

	//大きさをセット
	snowEffect->scale = { scale, scale, scale };

	//速度をセット
	snowEffect->velocity = velocity;

	return snowEffect;
}

void SnowEffect::Update()
{
	//移動
	Move();

	ObjObject3d::Update();
}

void SnowEffect::Move()
{
	velocity.y -= 0.1f;
	position += velocity;

	if (position.y <= 0.0f) {
		isDead = true;
	}
}
