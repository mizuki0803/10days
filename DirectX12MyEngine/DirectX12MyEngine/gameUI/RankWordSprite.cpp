#include "RankWordSprite.h"

RankWordSprite* RankWordSprite::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//�����N�����X�v���C�g�̃C���X�^���X�𐶐�
	RankWordSprite* rankWordSprite = new RankWordSprite();
	if (rankWordSprite == nullptr) {
		return nullptr;
	}

	// ������
	if (!rankWordSprite->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete rankWordSprite;
		assert(0);
		return nullptr;
	}

	//���W���Z�b�g
	rankWordSprite->position = position;

	//�傫�����Z�b�g
	rankWordSprite->size = size;
	rankWordSprite->texSize = { 926, 600 };

	return rankWordSprite;
}
