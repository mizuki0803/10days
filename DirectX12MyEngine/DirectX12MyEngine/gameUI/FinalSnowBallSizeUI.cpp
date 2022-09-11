#include "FinalSnowBallSizeUI.h"

FinalSnowBallSizeUI* FinalSnowBallSizeUI::Create(UINT texNumber, const Vector2& position, const Vector2& size, const float finalSnowBallSize)
{
	//�ŏI�I�Ȑ�ʂ̑傫����\������UI�̃C���X�^���X�𐶐�
	FinalSnowBallSizeUI* finalSnowBallSizeUI = new FinalSnowBallSizeUI();
	if (finalSnowBallSizeUI == nullptr) {
		return nullptr;
	}

	// ������
	if (!finalSnowBallSizeUI->Initialize(texNumber, position, size, finalSnowBallSize)) {
		delete finalSnowBallSizeUI;
		assert(0);
		return nullptr;
	}

	return finalSnowBallSizeUI;
}

bool FinalSnowBallSizeUI::Initialize(UINT texNumber, const Vector2& position, const Vector2& size, const float finalSnowBallSize)
{
	for (int i = 0; i < 6; i++) {
		std::unique_ptr<NumberSprite> newNumberSprite;

		Vector2 pos = position;
		pos.x -= i * size.x;
		pos.x += size.x * 3;

		newNumberSprite.reset(NumberSprite::Create(texNumber, pos, size));
		numberSprites.push_back(std::move(newNumberSprite));
	}

	ChangeNumber(finalSnowBallSize);

	return true;
}

void FinalSnowBallSizeUI::Update()
{
	//�X�v���C�g�X�V
	for (int i = 0; i < numberSprites.size(); i++) {
		numberSprites[i]->Update();
	}
}

void FinalSnowBallSizeUI::Draw()
{
	//�X�v���C�g�`��
	for (int i = 0; i < numberSprites.size(); i++) {
		numberSprites[i]->Draw();
	}
}

void FinalSnowBallSizeUI::ChangeNumber(const float finalSnowBallSize)
{
	//���������ꂼ��o�͂���
	const int scaleNum = (int)(finalSnowBallSize * 100.0f);
	numberSprites[0]->SetNumber(scaleNum % 10);				//000 01
	numberSprites[1]->SetNumber((scaleNum / 10) % 10);		//000 10
	numberSprites[2]->SetNumber(10);						//000.00
	numberSprites[3]->SetNumber((scaleNum / 100) % 10);		//001 00
	numberSprites[4]->SetNumber((scaleNum / 1000) % 10);	//010 00
	numberSprites[5]->SetNumber((scaleNum / 10000) % 10);	//100 00
}
