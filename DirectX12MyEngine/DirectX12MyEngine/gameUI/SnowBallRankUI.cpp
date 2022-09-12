#include "SnowBallRankUI.h"

SnowBallRankUI* SnowBallRankUI::Create(UINT rankTexNumber, UINT wordTexNumber, const Vector2& position, const float snowBallSize)
{
	//雪玉の大きさランクを表示するUIのインスタンスを生成
	SnowBallRankUI* snowBallRankUI = new SnowBallRankUI();
	if (snowBallRankUI == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!snowBallRankUI->Initialize(rankTexNumber, wordTexNumber, position, snowBallSize)) {
		delete snowBallRankUI;
		assert(0);
		return nullptr;
	}

	return snowBallRankUI;
}

bool SnowBallRankUI::Initialize(UINT rankTexNumber, UINT wordTexNumber, const Vector2& position, const float snowBallSize)
{
	//スプライト生成
	Vector2 rankSize = { 50, 50 };
	rankSprite.reset(RankSprite::Create(rankTexNumber, position, rankSize));
	Vector2 wordPos = position;
	wordPos.y -= 50;
	Vector2 wordSize = { 160, 40 };
	rankWordSprite.reset(RankWordSprite::Create(wordTexNumber, wordPos, wordSize));

	//ランクを確定させる
	SetRank(snowBallSize);

	return true;
}

void SnowBallRankUI::Update()
{
	//スプライト更新
	rankSprite->Update();
	rankWordSprite->Update();
}

void SnowBallRankUI::Draw()
{
	//スプライト描画
	rankSprite->Draw();
	rankWordSprite->Draw();
}

void SnowBallRankUI::SetRank(const float snowBallSize)
{
	//引数の大きさでランクを設定する
	if (snowBallSize >= 5.0f) { rank = Rank::S; }
	else if (snowBallSize >= 4.0f) { rank = Rank::A; }
	else if (snowBallSize >= 2.0f) { rank = Rank::B; }
	else { rank = Rank::C; }

	//ランクをスプライトに反映させる
	rankSprite->SetRank((int)rank);
}
