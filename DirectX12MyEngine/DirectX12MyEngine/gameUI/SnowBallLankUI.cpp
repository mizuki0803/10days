#include "SnowBallLankUI.h"

SnowBallLankUI* SnowBallLankUI::Create(UINT texNumber, const Vector2& position, const Vector2& size, const float snowBallSize)
{
	//��ʂ̑傫�������N��\������UI�̃C���X�^���X�𐶐�
	SnowBallLankUI* snowBallLankUI = new SnowBallLankUI();
	if (snowBallLankUI == nullptr) {
		return nullptr;
	}

	// ������
	if (!snowBallLankUI->Initialize(texNumber, position, size, snowBallSize)) {
		delete snowBallLankUI;
		assert(0);
		return nullptr;
	}

	return snowBallLankUI;
}

bool SnowBallLankUI::Initialize(UINT texNumber, const Vector2& position, const Vector2& size, const float snowBallSize)
{
	//�X�v���C�g����
	lankSprite.reset(LankSprite::Create(texNumber, position, size));

	//�����N���m�肳����
	SetLank(snowBallSize);

	return true;
}

void SnowBallLankUI::Update()
{
	//�X�v���C�g�X�V
	lankSprite->Update();
}

void SnowBallLankUI::Draw()
{
	//�X�v���C�g�`��
	lankSprite->Draw();
}

void SnowBallLankUI::SetLank(const float snowBallSize)
{
	//�����̑傫���Ń����N��ݒ肷��
	if (snowBallSize >= 5.0f) { lank = Lank::S; }
	else if (snowBallSize >= 4.0f) { lank = Lank::A; }
	else if (snowBallSize >= 2.0f) { lank = Lank::B; }
	else { lank = Lank::C; }

	//�����N���X�v���C�g�ɔ��f������
	lankSprite->SetLank((int)lank);
}
