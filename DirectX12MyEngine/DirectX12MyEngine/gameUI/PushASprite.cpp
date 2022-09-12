#include "PushASprite.h"

PushASprite* PushASprite::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//PushA�X�v���C�g�̃C���X�^���X�𐶐�
	PushASprite* pushASprite = new PushASprite();
	if (pushASprite == nullptr) {
		return nullptr;
	}

	// ������
	if (!pushASprite->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete pushASprite;
		assert(0);
		return nullptr;
	}

	//���W���Z�b�g
	pushASprite->position = position;

	//�傫�����Z�b�g
	pushASprite->size = size;
	pushASprite->texSize = size;

	return pushASprite;
}

void PushASprite::Update()
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

void PushASprite::Draw()
{
	//�`���ԂłȂ���Δ�����
	if (!isDraw) { return; }

	//�X�v���C�g�`��
	Sprite::Draw();
}

void PushASprite::ChangeFlashingSpeed()
{
	//�_�ł̑�����ς���
	drawModeTime = 3;
	flashingTime = 3;
}

void PushASprite::Flashing()
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

void PushASprite::DrawMode()
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
