#include "PadStickUI.h"

PadStickUI* PadStickUI::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//�p�b�h�X�e�B�b�NUI�̃C���X�^���X�𐶐�
	PadStickUI* padStickUI = new PadStickUI();
	if (padStickUI == nullptr) {
		return nullptr;
	}

	// ������
	if (!padStickUI->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete padStickUI;
		assert(0);
		return nullptr;
	}

	//���W���Z�b�g
	padStickUI->position = position;

	//�傫�����Z�b�g
	padStickUI->size = size;
	padStickUI->texSize = { 100, 100 };

	return padStickUI;
}

void PadStickUI::Update()
{
	//�X�e�B�b�N�̉摜�𓮂���
	StickMove();

	//�X�v���C�g�X�V
	Sprite::Update();
}

void PadStickUI::StickMove()
{
	//�^�C�}�[���X�V
	changeTimer++;
	const int changeTime = 30;

	//�^�C�}�[���w�肵�����ԂɂȂ�����
	if (changeTimer >= changeTime) {
		//�^�C�}�[��������
		changeTimer = 0;

		//�A�ԉ摜�ԍ����X�V
		drawNum++;
		if (drawNum >= 4) { drawNum = 0; }

		//�X�v���C�g�̍���؂�o�����W���e�N�X�`���T�C�Y * �A�ԉ摜�ԍ��ŎZ�o����
		texLeftTop.x = texSize.x * drawNum;
	}
}
