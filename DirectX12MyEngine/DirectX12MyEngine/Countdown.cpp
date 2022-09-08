#include "Countdown.h"

Countdown* Countdown::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//��ʂ̑傫����\������UI�̃C���X�^���X�𐶐�
	Countdown* countdown = new Countdown();
	if (countdown == nullptr) {
		return nullptr;
	}

	// ������
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
	//��ʂ̑傫���ɉ����Đ����ύX
	ChangeNumber();
	//�ړ�����
	Move();

	//�X�v���C�g�`��
	for (int i = 0; i < numberSprites.size(); i++)
	{
		numberSprites[i]->Update();
	}
}

void Countdown::Draw()
{
	//�X�v���C�g�`��
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
	//���������ꂼ��o�͂���
	numberSprites[0]->SetNumber(0);
	numberSprites[1]->SetNumber(1);
	numberSprites[2]->SetNumber(2);
	numberSprites[3]->SetNumber(3);
}

void Countdown::BeforeStart()
{
	//�t���O�Ǘ�
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


