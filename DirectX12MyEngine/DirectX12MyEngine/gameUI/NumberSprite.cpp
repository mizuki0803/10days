#include "NumberSprite.h"

NumberSprite* NumberSprite::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//�����X�v���C�g�̃C���X�^���X�𐶐�
	NumberSprite* numberSprite = new NumberSprite();
	if (numberSprite == nullptr) {
		return nullptr;
	}

	// ������
	if (!numberSprite->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete numberSprite;
		assert(0);
		return nullptr;
	}

	//���W���Z�b�g
	numberSprite->position = position;

	//�傫�����Z�b�g
	numberSprite->size = size;
	numberSprite->texSize = size;

	return numberSprite;
}

void NumberSprite::Update()
{
	//�\�����鐔�����X�V
	UpdateNumber();

	//�X�v���C�g�X�V
	Sprite::Update();
}

void NumberSprite::UpdateNumber()
{
	//�X�v���C�g�̍���؂�o�����W���e�N�X�`���T�C�Y * �����ŎZ�o����
	texLeftTop.x = texSize.x * number;
}
