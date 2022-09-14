#include "MiniMapSnowBall.h"

MiniMapSnowBall* MiniMapSnowBall::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//ミニマップの雪玉のインスタンスを生成
	MiniMapSnowBall* miniMapSnowBall = new MiniMapSnowBall();
	if (miniMapSnowBall == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!miniMapSnowBall->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete miniMapSnowBall;
		assert(0);
		return nullptr;
	}

	//座標をセット
	miniMapSnowBall->position = position;

	//大きさをセット
	miniMapSnowBall->size = size;
	miniMapSnowBall->texSize = { 768, 768 };

	return miniMapSnowBall;
}
