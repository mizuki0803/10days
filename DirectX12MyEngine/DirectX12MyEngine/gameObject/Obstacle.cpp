#include "Obstacle.h"
#include "Obstacle.h"

Player* Obstacle::player = nullptr;

void Obstacle::Update()
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

void Obstacle::Draw()
{
	//描画しなければ抜ける
	if (!isDraw) { return; }

	//オブジェクト更新
	ObjObject3d::Draw();
}

Vector3 Obstacle::GetWorldPos()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//平行移動成分を取得
	worldPos.x = matWorld.r[3].m128_f32[0];
	worldPos.y = matWorld.r[3].m128_f32[1];
	worldPos.z = matWorld.r[3].m128_f32[2];

	return worldPos;
}

void Obstacle::CheckIsDraw()
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

void Obstacle::CheckIsDead()
{
	//プレイヤーが設定されていなければ抜ける
	if (player == nullptr) { return; }

	//プレイヤーより後ろにいるか
	bool isBack = position.z <= player->GetPosition().z - 100;

	//プレイヤーより後ろにいなければ抜ける
	if (!isBack) { return; }

	isDead = true;
}
