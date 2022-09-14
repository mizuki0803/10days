#include "SnowBallSizeUI.h"

SnowBallSizeUI* SnowBallSizeUI::Create(UINT numberTexNumber, UINT snowBallTexNumber, const Vector2& position, const Vector2& size, const Vector2& texSize)
{
	//��ʂ̑傫����\������UI�̃C���X�^���X�𐶐�
	SnowBallSizeUI* snowBallSizeUI = new SnowBallSizeUI();
	if (snowBallSizeUI == nullptr) {
		return nullptr;
	}

	// ������
	if (!snowBallSizeUI->Initialize(numberTexNumber, snowBallTexNumber, position, size, texSize)) {
		delete snowBallSizeUI;
		assert(0);
		return nullptr;
	}

	return snowBallSizeUI;
}

bool SnowBallSizeUI::Initialize(UINT numberTexNumber, UINT snowBallTexNumber, const Vector2& position, const Vector2& size, const Vector2& texSize)
{
	for (int i = 0; i < 4; i++) {
		std::unique_ptr<NumberSprite> newNumberSprite;

		Vector2 pos = position;
		pos.x -= i * size.x;
		pos.x += size.x * 3;

		newNumberSprite.reset(NumberSprite::Create(numberTexNumber, pos, size, texSize));
		numberSprites.push_back(std::move(newNumberSprite));
	}

	Vector2 snowBallPos = position;
	snowBallPos.x -= 65;
	snowBallPos.y += 3;
	snowBallSprite.reset(MiniMapSnowBall::Create(snowBallTexNumber, snowBallPos, { 10, 10 }));

	return true;
}

void SnowBallSizeUI::Update(const float snowBallSize)
{
	//��ʂ̑傫���ɉ����Đ����ύX
	ChangeNumber(snowBallSize);
	//��ʃX�v���C�g�̑傫���ύX
	ChangeSnowBallSize(snowBallSize);

	//�X�v���C�g�`��
	for (int i = 0; i < numberSprites.size(); i++) {
		numberSprites[i]->Update();
	}
	snowBallSprite->Update();
}

void SnowBallSizeUI::Draw()
{
	//�X�v���C�g�`��
	for (int i = 0; i < numberSprites.size(); i++) {
		numberSprites[i]->Draw();
	}
	snowBallSprite->Draw();
}

void SnowBallSizeUI::ChangeNumber(const float snowBallSize)
{
	//���������ꂼ��o�͂���
	const int scaleNum = (int)(snowBallSize * 100.0f);
	numberSprites[0]->SetNumber(scaleNum % 10);				//000 01
	numberSprites[1]->SetNumber((scaleNum / 10) % 10);		//000 10
	numberSprites[2]->SetNumber(10);						//000.00
	numberSprites[3]->SetNumber((scaleNum / 100) % 10);		//001 00
}

void SnowBallSizeUI::ChangeSnowBallSize(const float snowBallSize)
{
	Vector2 size = { snowBallSize * 20, snowBallSize * 20 };

	snowBallSprite->SetSize(size);
}
