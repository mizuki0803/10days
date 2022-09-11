#include "MiniMap.h"

MiniMap* MiniMap::Create(UINT miniMapTexNumber, UINT snowBallTexNumber, const Vector2& position, const Vector2& size, const float goalPos)
{
	//ミニマップのインスタンスを生成
	MiniMap* miniMap = new MiniMap();
	if (miniMap == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!miniMap->Initialize(miniMapTexNumber, snowBallTexNumber, position, size)) {
		delete miniMap;
		assert(0);
		return nullptr;
	}

	miniMap->goalPos = goalPos;

	return miniMap;
}

bool MiniMap::Initialize(UINT miniMapTexNumber, UINT snowBallTexNumber, const Vector2& position, const Vector2& size)
{
	std::unique_ptr<MiniMapSprite> newMiniMapSprite;
	miniMapSprite.reset(MiniMapSprite::Create(miniMapTexNumber, position, size));

	std::unique_ptr<MiniMapSnowBall> newMiniMapSnowBall;
	Vector2 snowBallPos = position;
	snowBallPos.y += size.y;
	Vector2 snowBallSize = { 40, 40 };
	miniMapSnowBall.reset(MiniMapSnowBall::Create(snowBallTexNumber, snowBallPos, snowBallSize));

    return true;
}

void MiniMap::Update()
{
	//雪玉の座標変更
	ChangeSnowBallPos();

	//スプライト更新
	miniMapSprite->Update();
	miniMapSnowBall->Update();
}

void MiniMap::Draw()
{
	//スプライト描画
	miniMapSprite->Draw();
	miniMapSnowBall->Draw();
}

void MiniMap::ChangeSnowBallPos()
{
	//雪玉の座標を取得
	float snowBallPos = player->GetPosition().z;
	if (snowBallPos >= goalPos) {
		snowBallPos = goalPos;
	}

	//ゴール座標までの割合を計算
	const float ratio = snowBallPos / goalPos;

	//座標を更新
	Vector2 pos = miniMapSnowBall->GetPosition();
	pos.y = miniMapSprite->GetPosition().y + miniMapSprite->GetSize().y - ratio * miniMapSprite->GetSize().y;
	miniMapSnowBall->SetPosition(pos);
}
