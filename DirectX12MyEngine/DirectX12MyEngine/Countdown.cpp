#include "Countdown.h"

Countdown* Countdown::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//雪玉の大きさを表示するUIのインスタンスを生成
	Countdown* countdown = new Countdown();
	if (countdown == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!countdown->Initialize(texNumber, position, size)) {
		delete countdown;
		assert(0);
		return nullptr;
	}

	return countdown;
}

bool Countdown::Initialize(UINT texNumber, const Vector2& position, const Vector2& size)
{
	for (int i = 0; i < 4; i++) {
		std::unique_ptr<NumberSprite> newNumberSprite;

		Vector2 pos = position;
		pos.x -= i * size.x;
		pos.x += size.x * 3;

		newNumberSprite.reset(NumberSprite::Create(texNumber, pos, size));
		numberSprites.push_back(std::move(newNumberSprite));
	}

	return true;
}

void Countdown::Update()
{
	BeforeStart();
	//雪玉の大きさに応じて数字変更
	ChangeNumber();

	//スプライト描画
	for (int i = 0; i < numberSprites.size(); i++)
	{
		numberSprites[i]->Update();
	}
}

void Countdown::Draw()
{
	//スプライト描画
	for (int i = 0; i < numberSprites.size(); i++)
	{
		numberSprites[i]->Draw();
	}
}

void Countdown::ChangeNumber()
{
	//数字をそれぞれ出力する
	numberSprites[0]->SetNumber(0);
	numberSprites[1]->SetNumber(1);
	numberSprites[2]->SetNumber(2);
	numberSprites[3]->SetNumber(3);
}

void Countdown::BeforeStart()
{
	//フラグ管理
	if (!isStart)
	{
		countTime--;
		if (countTime == 180)
		{
			isOne = true;
		}
		if (countTime == 120)
		{
			isTwo = true;
		}
		if (countTime == 60)
		{
			isThree = true;
		}
	}
	if (countTime < 1)
	{
		isStart = true;
		isOne = false;
		isTwo = false;
		isThree = false;
	}
}

