#include "TitlePushASprite.h"

TitlePushASprite* TitlePushASprite::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//PushA�X�v���C�g�̃C���X�^���X�𐶐�
	TitlePushASprite* titlePushASprite = new TitlePushASprite();
	if (titlePushASprite == nullptr) {
		return nullptr;
	}

	// ������
	if (!titlePushASprite->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete titlePushASprite;
		assert(0);
		return nullptr;
	}

	//���W���Z�b�g
	titlePushASprite->position = position;

	//�傫�����Z�b�g
	titlePushASprite->size = size;
	titlePushASprite->texSize = size;

	return titlePushASprite;
}

void TitlePushASprite::Update()
{
	//�_��
	if (isDraw) {
		DrawMode();
	}
	else {
		Flashing();
	}


	//�`���ԂłȂ���Δ�����
	if (!isDraw) { return; }

	//�X�v���C�g�X�V
	Sprite::Update();
}

void TitlePushASprite::Draw()
{
	//�`���ԂłȂ���Δ�����
	if (!isDraw) { return; }

	//�X�v���C�g�`��
	Sprite::Draw();
}

void TitlePushASprite::ChangeFlashingSpeed()
{
	//�_�ł̑�����ς���
	drawModeTime = 3;
	flashingTime = 3;
}

void TitlePushASprite::Flashing()
{
	//�^�C�}�[���X�V
	flashingTimer++;

	//�^�C�}�[���w�肵�����ԂɂȂ�����
	if (flashingTimer >= flashingTime) {
		//�`���Ԃɂ���
		isDraw = true;
		//�^�C�}�[��������
		flashingTimer = 0;
	}
}

void TitlePushASprite::DrawMode()
{
	//�^�C�}�[���X�V
	drawModeTimer++;

	//�^�C�}�[���w�肵�����ԂɂȂ�����
	if (drawModeTimer >= drawModeTime) {
		//�`���Ԃ�����
		isDraw = false;
		//�^�C�}�[��������
		drawModeTimer = 0;
	}
}
