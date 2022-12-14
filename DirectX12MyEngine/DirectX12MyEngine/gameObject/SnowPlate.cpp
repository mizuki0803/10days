#include "SnowPlate.h"

Player* SnowPlate::player = nullptr;

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

void SnowPlate::Update()
{
	//描画するかチェック
	CheckIsDraw();

	//描画しなければ抜ける
	if (!isDraw) { return; }

	//死亡するかチェック
	CheckIsDead();

	//オブジェクト更新
	ObjObject3d::Update();
}

void SnowPlate::Draw()
{
	//描画しなければ抜ける
	if (!isDraw) { return; }

	//オブジェクト更新
	ObjObject3d::Draw();
}

void SnowPlate::CheckIsDraw()
{
	//既に描画されていたら抜ける
	if (isDraw) { return; }

	//プレイヤーが設定されていなければ一斉に描画状態にする
	if (player == nullptr) { isDraw = true; return; }

	//描画範囲にいるか
	bool isDrawDistance = position.z <= player->GetPosition().z + 600;

	//描画範囲にいなければ抜ける
	if (!isDrawDistance) { return; }

	isDraw = true;
}

void SnowPlate::CheckIsDead()
{
	//プレイヤーが設定されていなければ抜ける
	if (player == nullptr) { return; }

	//プレイヤーより後ろにいるか
	bool isBack = position.z <= player->GetPosition().z - 100;

	//プレイヤーより後ろにいなければ抜ける
	if (!isBack) { return; }

	isDead = true;
}
