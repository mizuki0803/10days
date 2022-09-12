#include "GoalSprite.h"
#include "Easing.h"

GoalSprite* GoalSprite::Create(UINT texNumber, const Vector2& size)
{
	//ゴールスプライトのインスタンスを生成
	GoalSprite* goalSprite = new GoalSprite();
	if (goalSprite == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!goalSprite->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete goalSprite;
		assert(0);
		return nullptr;
	}

	//座標をセット
	goalSprite->position = { -1200, 300 };

	//大きさをセット
	goalSprite->size = size;
	goalSprite->texSize = size;

	return goalSprite;
}

void GoalSprite::Update()
{
	//移動させる
	if (isMove) {
		Move();
	}

	//スプライト更新
	Sprite::Update();
}

void GoalSprite::MoveStart()
{
	//移動する
	isMove = true;
}

void GoalSprite::Move()
{
	//移動させる時間
	const float moveTime = 90;
	//タイマーを更新
	moveTimer++;
	//イージングで動かす
	const float time = moveTimer / moveTime;
	const float startPos = -500;
	const float stayPos = 640;
	position.x = Easing::OutBack(startPos, stayPos, time);

	//タイマーが指定した時間になったら
	if (moveTimer >= moveTime) {
		//移動終了
		isMove = false;
	}
}
