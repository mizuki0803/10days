#include "SnowBallSizeUI.h"

SnowBallSizeUI* SnowBallSizeUI::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//雪玉の大きさを表示するUIのインスタンスを生成
	SnowBallSizeUI* snowBallSizeUI = new SnowBallSizeUI();
	if (snowBallSizeUI == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!snowBallSizeUI->Initialize(texNumber, position, size)) {
		delete snowBallSizeUI;
		assert(0);
		return nullptr;
	}

	return snowBallSizeUI;
}

bool SnowBallSizeUI::Initialize(UINT texNumber, const Vector2& position, const Vector2& size)
{
	for (int i = 0; i < 6; i++) {
		std::unique_ptr<NumberSprite> newNumberSprite;

		Vector2 pos = position;
		pos.x -= i * size.x;
		pos.x += size.x * 3;

		newNumberSprite.reset(NumberSprite::Create(texNumber, pos, size));
		numberSprites.push_back(std::move(newNumberSprite));
	}

    return true;
}

void SnowBallSizeUI::Update()
{
	//雪玉の大きさに応じて数字変更
	ChangeNumber();

	//スプライト描画
	for (int i = 0; i < numberSprites.size(); i++) {
		numberSprites[i]->Update();
	}
}

void SnowBallSizeUI::Draw()
{
	//スプライト描画
	for (int i = 0; i < numberSprites.size(); i++) {
		numberSprites[i]->Draw();
	}
}

void SnowBallSizeUI::ChangeNumber()
{
	//数字をそれぞれ出力する
	const int scaleNum = (int)(player->GetScale().x * 100.0f);
	numberSprites[0]->SetNumber(scaleNum % 10);				//000 01
	numberSprites[1]->SetNumber((scaleNum / 10) % 10);		//000 10
	numberSprites[2]->SetNumber(10);						//000.00
	numberSprites[3]->SetNumber((scaleNum / 100) % 10);		//001 00
	numberSprites[4]->SetNumber((scaleNum / 1000) % 10);	//010 00
	numberSprites[5]->SetNumber((scaleNum / 10000) % 10);	//100 00
}
