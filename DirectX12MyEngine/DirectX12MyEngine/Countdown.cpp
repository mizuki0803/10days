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
	//��ʂ̑傫���ɉ����Đ����ύX
	ChangeNumber();

	//�X�v���C�g�`��
	for (int i = 0; i < numberSprites.size(); i++)
	{
		numberSprites[i]->Update();
	}
}

void Countdown::Draw()
{
	//�X�v���C�g�`��
	for (int i = 0; i < numberSprites.size(); i++)
	{
		numberSprites[i]->Draw();
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

