#include "Countdown.h"
#include "Audio.h"
#include "Easing.h"

Countdown* Countdown::Create(UINT texNumber, const Vector2& position, const Vector2& size, const Vector2& texSize)
{
	//雪玉の大きさを表示するUIのインスタンスを生成
	Countdown* countdown = new Countdown();
	if (countdown == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!countdown->Initialize(texNumber, position, size, texSize)) {
		delete countdown;
		assert(0);
		return nullptr;
	}

	return countdown;
}

bool Countdown::Initialize(UINT texNumber, const Vector2& position, const Vector2& size, const Vector2& texSize)
{
	for (int i = 0; i < 4; i++) {
		std::unique_ptr<NumberSprite> newNumberSprite;

		pos = position;
		pos.x = leftSide - 400;
		pos.x += size.x * 3;

		newNumberSprite.reset(NumberSprite::Create(texNumber, pos, size, texSize));
		numberSprites.push_back(std::move(newNumberSprite));
	}


	//スプライト数字変更
	ChangeNumber();

	return true;
}

void Countdown::Update()
{
	BeforeStart();
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
	numberSprites[1]->Draw();
	numberSprites[2]->Draw();
	numberSprites[3]->Draw();
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
		int returnCount = 40;
		timeRate = easeTimer / returnCount;
		threePos = Easing::InQuad(leftSide, center, timeRate);
		if (easeTimer / returnCount < 1)
		{
			easeTimer++;

			if (easeTimer == returnCount)
			{
				//ピッ効果音を再生
				Audio::GetInstance()->PlayWave("countdown.wav", false);
			}
		}
		numberSprites[3]->SetPosition({ threePos, pos.y });
	}
	if (isTwo)
	{
		int returnCount = 40;
		timeRate = easeTimer2 / returnCount;
		twoPos = Easing::InQuad(leftSide, center, timeRate);
		threePos = Easing::InQuad(center, rightSide, timeRate);
		if (easeTimer2 / returnCount < 1)
		{
			easeTimer2++;

			if (easeTimer2 == returnCount)
			{
				//ピッ効果音を再生
				Audio::GetInstance()->PlayWave("countdown.wav", false);
			}
		}
		numberSprites[3]->SetPosition({ threePos, pos.y });
		numberSprites[2]->SetPosition({ twoPos, pos.y });
	}
	if (isThree)
	{
		int returnCount = 40;
		timeRate = easeTimer3 / returnCount;
		onePos = Easing::InQuad(leftSide, center, timeRate);
		twoPos = Easing::InQuad(center, rightSide, timeRate);
		if (easeTimer3 / returnCount < 1)
		{
			easeTimer3++;

			if (easeTimer3 == returnCount)
			{
				//ピッ効果音を再生
				Audio::GetInstance()->PlayWave("countdown.wav", false);
			}
		}
		numberSprites[2]->SetPosition({ twoPos, pos.y });
		numberSprites[1]->SetPosition({ onePos, pos.y });
	}
}


