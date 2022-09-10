#include "SnowBallLankUI.h"

SnowBallLankUI* SnowBallLankUI::Create(UINT texNumber, const Vector2& position, const Vector2& size, const float snowBallSize)
{
	//雪玉の大きさランクを表示するUIのインスタンスを生成
	SnowBallLankUI* snowBallLankUI = new SnowBallLankUI();
	if (snowBallLankUI == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!snowBallLankUI->Initialize(texNumber, position, size, snowBallSize)) {
		delete snowBallLankUI;
		assert(0);
		return nullptr;
	}

	return snowBallLankUI;
}

bool SnowBallLankUI::Initialize(UINT texNumber, const Vector2& position, const Vector2& size, const float snowBallSize)
{
	//スプライト生成
	lankSprite.reset(LankSprite::Create(texNumber, position, size));

	//ランクを確定させる
	SetLank(snowBallSize);

	return true;
}

void SnowBallLankUI::Update()
{
	//スプライト更新
	lankSprite->Update();
}

void SnowBallLankUI::Draw()
{
	//スプライト描画
	lankSprite->Draw();
}

void SnowBallLankUI::SetLank(const float snowBallSize)
{
	//引数の大きさでランクを設定する
	if (snowBallSize >= 5.0f) { lank = Lank::S; }
	else if (snowBallSize >= 4.0f) { lank = Lank::A; }
	else if (snowBallSize >= 2.0f) { lank = Lank::B; }
	else { lank = Lank::C; }

	//ランクをスプライトに反映させる
	lankSprite->SetLank((int)lank);
}
