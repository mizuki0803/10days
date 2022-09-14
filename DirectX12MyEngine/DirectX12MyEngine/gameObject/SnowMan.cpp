#include "SnowMan.h"

SnowMan* SnowMan::Create(ObjModel* upperModel, ObjModel* underModel, const Vector3& position, const float underSize)
{
	//�Ⴞ��܂̃C���X�^���X�𐶐�
	SnowMan* snowMan = new SnowMan();
	if (snowMan == nullptr) {
		return nullptr;
	}

	// ������
	if (!snowMan->Initialize(upperModel, underModel, position, underSize)) {
		delete snowMan;
		assert(0);
		return nullptr;
	}

	return snowMan;
}

bool SnowMan::Initialize(ObjModel* upperModel, ObjModel* underModel, const Vector3& position, const float underSize)
{
	//���f�����Z�b�g
	assert(upperModel);
	assert(underModel);

	//�Ⴞ���(��)����
	Vector3 underPos = { position.x, underSize, position.z };
	snowManUnder.reset(SnowManUnder::Create(underModel, underPos, { underSize, underSize, underSize }));
	//�Ⴞ���(��)����
	Vector3 upperScale = { 1, 1, 1 };
	Vector3 upperPos = { underPos.x, underSize * 2 + upperScale.y / 2, underPos.z };
	snowManUpper.reset(SnowManUpper::Create(upperModel, upperPos, upperScale));
	snowManUpper->SetRotation({ 0, 90, 0 });

	return true;
}

void SnowMan::Update()
{
	//�I�u�W�F�N�g�X�V
	snowManUpper->Update();
	snowManUnder->Update();
}

void SnowMan::Draw()
{
	//�I�u�W�F�N�g�`��
	snowManUpper->Draw();
	snowManUnder->Draw();
}
