#include "SnowWall.h"

Player* SnowWall::player = nullptr;

SnowWall* SnowWall::Create(ObjModel* model, const Vector3& position, const Vector3& rotation)
{
	//�ǂ̃C���X�^���X�𐶐�
	SnowWall* snowWall = new SnowWall();
	if (snowWall == nullptr) {
		return nullptr;
	}

	//���f�����Z�b�g
	assert(model);
	snowWall->model = model;

	// ������
	if (!snowWall->Initialize()) {
		delete snowWall;
		assert(0);
		return nullptr;
	}

	//���W���Z�b�g
	snowWall->position = position;

	//�傫�����Z�b�g
	snowWall->scale = { 12.5f, 6, 12.5f };

	//�p�x���Z�b�g
	snowWall->rotation = rotation;

	//�F���Z�b�g
	snowWall->color = { 0.6f, 0.6f, 0.6f, 1 };

	return snowWall;
}

void SnowWall::Update()
{
	//�`�悷�邩�`�F�b�N
	CheckIsDraw();

	//�`�悵�Ȃ���Δ�����
	if (!isDraw) { return; }

	//���S���邩�`�F�b�N
	CheckIsDead();

	//�I�u�W�F�N�g�X�V
	ObjObject3d::Update();
}

void SnowWall::Draw()
{
	//�`�悵�Ȃ���Δ�����
	if (!isDraw) { return; }

	//�I�u�W�F�N�g�X�V
	ObjObject3d::Draw();
}

void SnowWall::CheckIsDraw()
{
	//���ɕ`�悳��Ă����甲����
	if (isDraw) { return; }

	//�v���C���[���ݒ肳��Ă��Ȃ���Έ�Ăɕ`���Ԃɂ���
	if (player == nullptr) { isDraw = true; return; }

	//�`��͈͂ɂ��邩
	bool isDrawDistance = position.z <= player->GetPosition().z + 600;

	//�`��͈͂ɂ��Ȃ���Δ�����
	if (!isDrawDistance) { return; }

	isDraw = true;
}

void SnowWall::CheckIsDead()
{
	//�v���C���[���ݒ肳��Ă��Ȃ���Δ�����
	if (player == nullptr) { return; }

	//�v���C���[�����ɂ��邩
	bool isBack = position.z <= player->GetPosition().z - 100;

	//�v���C���[�����ɂ��Ȃ���Δ�����
	if (!isBack) { return; }

	isDead = true;
}
