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

		pos = position;
		pos.x += (i * 400) - 1300;
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
	//移動処理
	Move();

	//スプライト描画
	for (int i = 0; i < numberSprites.size(); i++)
	{
		numberSprites[i]->Update();
	}
}

void Countdown::Draw()
{
	//スプライト描画
	if (isThree)
	{
		numberSprites[1]->Draw();
	}
	if (isTwo)
	{
		numberSprites[2]->Draw();
	}
	if (isOne)
	{
		numberSprites[3]->Draw();
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
			isOne = false;
			isTwo = true;
		}
		if (countTime == 60)
		{
			isTwo = false;
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

void Countdown::Move()
{
	if (isOne)
	{
		numberSprites[3]->SetPosition({ 1040,120 });
		numberSprites[2]->SetPosition({ 640,120 });
		numberSprites[1]->SetPosition({ 240,120 });
	}
	if (isTwo)
	{
		numberSprites[3]->SetPosition({ 1440,120 });
		numberSprites[2]->SetPosition({ 1040,120 });
		numberSprites[1]->SetPosition({ 640,120 });
	}
	if (isThree)
	{
		numberSprites[3]->SetPosition({ 1840,120 });
		numberSprites[2]->SetPosition({ 1440,120 });
		numberSprites[1]->SetPosition({ 1040,120 });
	}
}


