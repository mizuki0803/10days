#include "SnowEffect.h"

SnowEffect* SnowEffect::Create(ObjModel* model, const Vector3& position, const float scale, const Vector3& velocity)
{
	//��ʃG�t�F�N�g�̃C���X�^���X�𐶐�
	SnowEffect* snowEffect = new SnowEffect();
	if (snowEffect == nullptr) {
		return nullptr;
	}

	// ������
	if (!snowEffect->Initialize()) {
		delete snowEffect;
		assert(0);
		return nullptr;
	}

	//���f�����Z�b�g
	assert(model);
	snowEffect->model = model;

	//���W���Z�b�g
	snowEffect->position = position;

	//�傫�����Z�b�g
	snowEffect->scale = { scale, scale, scale };

	//���x���Z�b�g
	snowEffect->velocity = velocity;

	return snowEffect;
}

void SnowEffect::Update()
{
	//�ړ�
	Move();

	ObjObject3d::Update();
}

void SnowEffect::Move()
{
	velocity.y -= 0.1f;
	position += velocity;

	if (position.y <= 0.0f) {
		isDead = true;
	}
}
