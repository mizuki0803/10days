#include "RankSprite.h"

RankSprite* RankSprite::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//�����N�X�v���C�g�̃C���X�^���X�𐶐�
	RankSprite* rankSprite = new RankSprite();
	if (rankSprite == nullptr) {
		return nullptr;
	}

	// ������
	if (!rankSprite->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete rankSprite;
		assert(0);
		return nullptr;
	}

	//���W���Z�b�g
	rankSprite->position = position;

	//�傫�����Z�b�g
	rankSprite->size = size;
	rankSprite->texSize = size;

	return rankSprite;
}

void RankSprite::SetRank(const int rank)
{
	//�����N���X�V
	this->rank = rank;

	//�X�v���C�g�̍���؂�o�����W���e�N�X�`���T�C�Y * �����N(����)�ŎZ�o����
	texLeftTop.x = texSize.x * rank;
}
