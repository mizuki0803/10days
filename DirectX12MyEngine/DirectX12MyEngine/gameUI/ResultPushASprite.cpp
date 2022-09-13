#include "ResultPushASprite.h"

ResultPushASprite* ResultPushASprite::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//PushA�X�v���C�g�̃C���X�^���X�𐶐�
	ResultPushASprite* resultPushASprite = new ResultPushASprite();
	if (resultPushASprite == nullptr) {
		return nullptr;
	}

	// ������
	if (!resultPushASprite->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete resultPushASprite;
		assert(0);
		return nullptr;
	}

	//���W���Z�b�g
	resultPushASprite->position = position;

	//�傫�����Z�b�g
	resultPushASprite->size = size;
	resultPushASprite->texSize = size;

	return resultPushASprite;
}
