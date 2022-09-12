#include "TitleLogo.h"

TitleLogo* TitleLogo::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//�^�C�g�����S�̃C���X�^���X�𐶐�
	TitleLogo* titleLogo = new TitleLogo();
	if (titleLogo == nullptr) {
		return nullptr;
	}

	// ������
	if (!titleLogo->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete titleLogo;
		assert(0);
		return nullptr;
	}

	//���W���Z�b�g
	titleLogo->position = position;

	//�傫�����Z�b�g
	titleLogo->size = size;
	titleLogo->texSize = size;

	return titleLogo;
}
