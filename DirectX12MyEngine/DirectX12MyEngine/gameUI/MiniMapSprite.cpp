#include "MiniMapSprite.h"

MiniMapSprite* MiniMapSprite::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//�~�j�}�b�v�X�v���C�g�̃C���X�^���X�𐶐�
	MiniMapSprite* miniMapSprite = new MiniMapSprite();
	if (miniMapSprite == nullptr) {
		return nullptr;
	}

	// ������
	if (!miniMapSprite->Initialize(texNumber, { 0.5f, 0 }, false, false)) {
		delete miniMapSprite;
		assert(0);
		return nullptr;
	}

	//���W���Z�b�g
	miniMapSprite->position = position;

	//�傫�����Z�b�g
	miniMapSprite->size = size;
	miniMapSprite->texSize = size;

	return miniMapSprite;
}
