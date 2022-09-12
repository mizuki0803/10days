#include "SnowBallRankUI.h"

SnowBallRankUI* SnowBallRankUI::Create(UINT rankTexNumber, UINT wordTexNumber, const Vector2& position, const float snowBallSize)
{
	//��ʂ̑傫�������N��\������UI�̃C���X�^���X�𐶐�
	SnowBallRankUI* snowBallRankUI = new SnowBallRankUI();
	if (snowBallRankUI == nullptr) {
		return nullptr;
	}

	// ������
	if (!snowBallRankUI->Initialize(rankTexNumber, wordTexNumber, position, snowBallSize)) {
		delete snowBallRankUI;
		assert(0);
		return nullptr;
	}

	return snowBallRankUI;
}

bool SnowBallRankUI::Initialize(UINT rankTexNumber, UINT wordTexNumber, const Vector2& position, const float snowBallSize)
{
	//�X�v���C�g����
	Vector2 rankSize = { 50, 50 };
	rankSprite.reset(RankSprite::Create(rankTexNumber, position, rankSize));
	Vector2 wordPos = position;
	wordPos.y -= 50;
	Vector2 wordSize = { 160, 40 };
	rankWordSprite.reset(RankWordSprite::Create(wordTexNumber, wordPos, wordSize));

	//�����N���m�肳����
	SetRank(snowBallSize);

	return true;
}

void SnowBallRankUI::Update()
{
	//�X�v���C�g�X�V
	rankSprite->Update();
	rankWordSprite->Update();
}

void SnowBallRankUI::Draw()
{
	//�X�v���C�g�`��
	rankSprite->Draw();
	rankWordSprite->Draw();
}

void SnowBallRankUI::SetRank(const float snowBallSize)
{
	//�����̑傫���Ń����N��ݒ肷��
	if (snowBallSize >= 5.0f) { rank = Rank::S; }
	else if (snowBallSize >= 4.0f) { rank = Rank::A; }
	else if (snowBallSize >= 2.0f) { rank = Rank::B; }
	else { rank = Rank::C; }

	//�����N���X�v���C�g�ɔ��f������
	rankSprite->SetRank((int)rank);
}
