#include "Obstacle.h"
#include "Obstacle.h"

Player* Obstacle::player = nullptr;

void Obstacle::Update()
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

void Obstacle::Draw()
{
	//�`�悵�Ȃ���Δ�����
	if (!isDraw) { return; }

	//�I�u�W�F�N�g�X�V
	ObjObject3d::Draw();
}

Vector3 Obstacle::GetWorldPos()
{
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���s�ړ��������擾
	worldPos.x = matWorld.r[3].m128_f32[0];
	worldPos.y = matWorld.r[3].m128_f32[1];
	worldPos.z = matWorld.r[3].m128_f32[2];

	return worldPos;
}

void Obstacle::CheckIsDraw()
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

void Obstacle::CheckIsDead()
{
	//�v���C���[���ݒ肳��Ă��Ȃ���Δ�����
	if (player == nullptr) { return; }

	//�v���C���[�����ɂ��邩
	bool isBack = position.z <= player->GetPosition().z - 100;

	//�v���C���[�����ɂ��Ȃ���Δ�����
	if (!isBack) { return; }

	isDead = true;
}
