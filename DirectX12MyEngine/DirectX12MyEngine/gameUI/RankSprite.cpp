#include "RankSprite.h"

RankSprite* RankSprite::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//ランクスプライトのインスタンスを生成
	RankSprite* rankSprite = new RankSprite();
	if (rankSprite == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!rankSprite->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete rankSprite;
		assert(0);
		return nullptr;
	}

	//座標をセット
	rankSprite->position = position;

	//大きさをセット
	rankSprite->size = size;
	rankSprite->texSize = size;

	return rankSprite;
}

void RankSprite::SetRank(const int rank)
{
	//ランクを更新
	this->rank = rank;

	//スプライトの左上切り出し座標をテクスチャサイズ * ランク(数字)で算出する
	texLeftTop.x = texSize.x * rank;
}
