#include "SnowBall.h"

SnowBall* SnowBall::Create(ObjModel* model)
{
	//���@�̃C���X�^���X�𐶐�
	SnowBall* snowBall = new SnowBall();
	if (snowBall == nullptr) {
		return nullptr;
	}

	//���f�����Z�b�g
	assert(model);
	snowBall->model = model;

	// ������
	if (!snowBall->Initialize()) {
		delete snowBall;
		assert(0);
		return nullptr;
	}

	return snowBall;
}

bool SnowBall::Initialize()
{
	position = { 0 ,1 ,10 };
	scale = { 1.5f, 1.5f, 1.5f };

	//3D�I�u�W�F�N�g�̏�����
	if (!ObjObject3d::Initialize()) {
		return false;
	}

	return true;
}

void SnowBall::Update()
{
}
