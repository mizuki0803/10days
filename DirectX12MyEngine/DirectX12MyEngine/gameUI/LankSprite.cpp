#include "LankSprite.h"

LankSprite* LankSprite::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//�����N�X�v���C�g�̃C���X�^���X�𐶐�
	LankSprite* lankSprite = new LankSprite();
	if (lankSprite == nullptr) {
		return nullptr;
	}

	// ������
	if (!lankSprite->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete lankSprite;
		assert(0);
		return nullptr;
	}

	//���W���Z�b�g
	lankSprite->position = position;

	//�傫�����Z�b�g
	lankSprite->size = size;
	lankSprite->texSize = size;

	return lankSprite;
}

void LankSprite::SetLank(const int lank)
{
	//�����N���X�V
	this->lank = lank;

	//�X�v���C�g�̍���؂�o�����W���e�N�X�`���T�C�Y * �����N(����)�ŎZ�o����
	texLeftTop.x = texSize.x * lank;
}
