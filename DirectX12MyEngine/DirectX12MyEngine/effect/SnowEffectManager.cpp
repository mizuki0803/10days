#include "SnowEffectManager.h"
#include "DebugText.h"

ObjModel* SnowEffectManager::model = nullptr;

SnowEffectManager* SnowEffectManager::Create()
{
	//��ʃG�t�F�N�g�}�l�[�W���[�̃C���X�^���X�𐶐�
	SnowEffectManager* snowEffectManager = new SnowEffectManager();
	if (snowEffectManager == nullptr) {
		return nullptr;
	}

	return snowEffectManager;
}

void SnowEffectManager::Update()
{
	//���S������ʃG�t�F�N�g�̍폜
	snowEffects.remove_if([](std::unique_ptr<SnowEffect>& snowEffect) {
		return snowEffect->GetIsDead();
		});

	//�X�V����
	for (const std::unique_ptr<SnowEffect>& snowEffect : snowEffects) {
		snowEffect->Update();
	}

	std::string snowEffectNum = std::to_string(snowEffects.size());
	DebugText::GetInstance()->Print("snowEffectNum : " + snowEffectNum, 100, 200);
}

void SnowEffectManager::Draw()
{
	//�`��
	for (const std::unique_ptr<SnowEffect>& snowEffect : snowEffects) {
		snowEffect->Draw();
	}
}

void SnowEffectManager::AddSnowEffect(const Vector3& position)
{
	//��ʃG�t�F�N�g��ǉ�
	for (int i = 0; i < 20; i++) {
		//�����_���ŃG�t�F�N�g�̈ړ����x���Z�b�g
		const Vector3 randVel = { 10, 10, 10 };
		Vector3 velocity;
		velocity.x = (float)((rand() % (int)randVel.x) - randVel.x / 2);
		velocity.y = (float)((rand() % (int)randVel.y));
		velocity.z = (float)((rand() % (int)randVel.z) - randVel.z / 2);

		//�l���傫���̂Ŋ���Z���ď���������
		const float div = 10;
		velocity /= div;

		std::unique_ptr<SnowEffect> newSnowEffect;
		newSnowEffect.reset(SnowEffect::Create(model, position, 0.3f, velocity));
		snowEffects.push_back(std::move(newSnowEffect));
	}
}
