#include "SnowMan.h"

SnowMan* SnowMan::Create(ObjModel* upperModel, ObjModel* underModel, const Vector3& position, const float underSize)
{
	//雪だるまのインスタンスを生成
	SnowMan* snowMan = new SnowMan();
	if (snowMan == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!snowMan->Initialize(upperModel, underModel, position, underSize)) {
		delete snowMan;
		assert(0);
		return nullptr;
	}

	return snowMan;
}

bool SnowMan::Initialize(ObjModel* upperModel, ObjModel* underModel, const Vector3& position, const float underSize)
{
	//モデルをセット
	assert(upperModel);
	assert(underModel);

	//雪だるま(下)生成
	Vector3 underPos = { position.x, underSize, position.z };
	snowManUnder.reset(SnowManUnder::Create(underModel, underPos, { underSize, underSize, underSize }));
	//雪だるま(上)生成
	Vector3 upperScale = { 1, 1, 1 };
	Vector3 upperPos = { underPos.x, underSize * 2 + upperScale.y / 2, underPos.z };
	snowManUpper.reset(SnowManUpper::Create(upperModel, upperPos, upperScale));
	snowManUpper->SetRotation({ 0, 90, 0 });

	return true;
}

void SnowMan::Update()
{
	//オブジェクト更新
	snowManUpper->Update();
	snowManUnder->Update();
}

void SnowMan::Draw()
{
	//オブジェクト描画
	snowManUpper->Draw();
	snowManUnder->Draw();
}
