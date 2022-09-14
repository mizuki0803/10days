#include "SnowWall.h"

Player* SnowWall::player = nullptr;

SnowWall* SnowWall::Create(ObjModel* model, const Vector3& position, const Vector3& rotation)
{
	//壁のインスタンスを生成
	SnowWall* snowWall = new SnowWall();
	if (snowWall == nullptr) {
		return nullptr;
	}

	//モデルをセット
	assert(model);
	snowWall->model = model;

	// 初期化
	if (!snowWall->Initialize()) {
		delete snowWall;
		assert(0);
		return nullptr;
	}

	//座標をセット
	snowWall->position = position;

	//大きさをセット
	snowWall->scale = { 12.5f, 6, 12.5f };

	//角度をセット
	snowWall->rotation = rotation;

	//色をセット
	snowWall->color = { 0.6f, 0.6f, 0.6f, 1 };

	return snowWall;
}

void SnowWall::Update()
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

void SnowWall::Draw()
{
	//描画しなければ抜ける
	if (!isDraw) { return; }

	//オブジェクト更新
	ObjObject3d::Draw();
}

void SnowWall::CheckIsDraw()
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

void SnowWall::CheckIsDead()
{
	//プレイヤーが設定されていなければ抜ける
	if (player == nullptr) { return; }

	//プレイヤーより後ろにいるか
	bool isBack = position.z <= player->GetPosition().z - 100;

	//プレイヤーより後ろにいなければ抜ける
	if (!isBack) { return; }

	isDead = true;
}
