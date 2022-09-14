#include "FinalSnowBallSizeUI.h"

FinalSnowBallSizeUI* FinalSnowBallSizeUI::Create(UINT numberTexNumber, UINT snowBallTexNumber, const Vector2& position, const Vector2& size, const Vector2& texSize, const float finalSnowBallSize)
{
	//最終的な雪玉の大きさを表示するUIのインスタンスを生成
	FinalSnowBallSizeUI* finalSnowBallSizeUI = new FinalSnowBallSizeUI();
	if (finalSnowBallSizeUI == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!finalSnowBallSizeUI->Initialize(numberTexNumber, snowBallTexNumber, position, size, texSize, finalSnowBallSize)) {
		delete finalSnowBallSizeUI;
		assert(0);
		return nullptr;
	}

	return finalSnowBallSizeUI;
}

bool FinalSnowBallSizeUI::Initialize(UINT numberTexNumber, UINT snowBallTexNumber, const Vector2& position, const Vector2& size, const Vector2& texSize, const float finalSnowBallSize)
{
	for (int i = 0; i < 4; i++) {
		std::unique_ptr<NumberSprite> newNumberSprite;

		Vector2 pos = position;
		pos.x -= i * size.x;
		pos.x += size.x * 3;

		newNumberSprite.reset(NumberSprite::Create(numberTexNumber, pos, size, texSize));
		numberSprites.push_back(std::move(newNumberSprite));
		numberSprites[i]->SetColor({ 1, 1, 0, 1 });
	}

	ChangeNumber(finalSnowBallSize);

	Vector2 snowBallPos = position;
	snowBallPos.x -= 65;
	snowBallPos.y += 3;
	snowBallSprite.reset(MiniMapSnowBall::Create(snowBallTexNumber, snowBallPos, { 10, 10 }));

	ChangeSnowBallSize(finalSnowBallSize);

	return true;
}

void FinalSnowBallSizeUI::Update()
{
	//スプライト更新
	for (int i = 0; i < numberSprites.size(); i++) {
		numberSprites[i]->Update();
	}
	snowBallSprite->Update();
}

void FinalSnowBallSizeUI::Draw()
{
	//スプライト描画
	for (int i = 0; i < numberSprites.size(); i++) {
		numberSprites[i]->Draw();
	}
	snowBallSprite->Draw();
}

void FinalSnowBallSizeUI::ChangeNumber(const float finalSnowBallSize)
{
	//数字をそれぞれ出力する
	const int scaleNum = (int)(finalSnowBallSize * 100.0f);
	numberSprites[0]->SetNumber(scaleNum % 10);				//000 01
	numberSprites[1]->SetNumber((scaleNum / 10) % 10);		//000 10
	numberSprites[2]->SetNumber(10);						//000.00
	numberSprites[3]->SetNumber((scaleNum / 100) % 10);		//001 00
}

void FinalSnowBallSizeUI::ChangeSnowBallSize(const float snowBallSize)
{
	Vector2 size = { snowBallSize * 20, snowBallSize * 20 };

	snowBallSprite->SetSize(size);
}
