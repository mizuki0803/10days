#include "Blackout.h"
#include "Easing.h"

Blackout* Blackout::GetInstance()
{
	static Blackout instance;

	return &instance;
}

void Blackout::Initialize(UINT texNumber)
{
	//�X�v���C�g�𐶐�����(�A���J�[�|�C���g��{ 0, 0 }�ɐݒ�)
	sprite.reset(Sprite::Create(texNumber, { 0, 0 }));
	sprite->SetPosition({ 0, 0 });
	sprite->SetSize({ 1280, 720 });
	sprite->SetColor({ 0, 0, 0, 0 });
}

void Blackout::Update()
{
	//�Ó]
	if (isBlackout)
	{
		BlackoutUpdate();
	}
	//�Ó]����
	if (isReturn)
	{
		BlackoutReturn();
	}

	//�X�v���C�g�X�V
	sprite->Update();
}

void Blackout::Draw()
{
	//�X�v���C�g�`��
	sprite->Draw();
}

void Blackout::SetBlackout()
{
	//�^�C�}�[������������
	blackoutTimer = 0;

	//�Ó]��ԂɃZ�b�g
	isBlackout = true;
}

void Blackout::SetBlackoutReturn()
{
	//�^�C�}�[������������
	returnTimer = 0;

	//�Ó]������ԂɃZ�b�g
	isReturn = true;

	//�^���Âł͂Ȃ�
	isAllBlack = false;
}

void Blackout::BlackoutUpdate()
{
	//�Ó]���s������
	const int blackoutTime = 80;

	//�^�C�}�[�X�V
	blackoutTimer++;

	//�C�[�W���O�v�Z�p�̎���
	float easeTimer = (float)blackoutTimer / blackoutTime;

	//�C�[�W���O�ňÓ]
	DirectX::XMFLOAT4 color = sprite->GetColor();
	color.w = Easing::OutQuad(0, 1, easeTimer);
	sprite->SetColor(color);

	//�^�C�}�[���w�肵�����ԂɂȂ�����
	if (blackoutTimer >= blackoutTime) {
		//�Ó]�I��
		isBlackout = false;

		//�^����
		isAllBlack = true;
	}
}

void Blackout::BlackoutReturn()
{
	//�Ó]�������s������
	const int returnTime = 50;

	//�^�C�}�[�X�V
	returnTimer++;

	//�C�[�W���O�v�Z�p�̎���
	float easeTimer = (float)returnTimer / returnTime;

	//�C�[�W���O�ňÓ]����
	DirectX::XMFLOAT4 color = sprite->GetColor();
	color.w = Easing::OutQuad(1, 0, easeTimer);
	sprite->SetColor(color);

	//�^�C�}�[���w�肵�����ԂɂȂ�����
	if (returnTimer >= returnTime) {
		//�Ó]��߂���
		isReturn = false;
	}
}
