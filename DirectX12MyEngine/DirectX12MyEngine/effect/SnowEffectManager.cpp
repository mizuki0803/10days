#include "SnowEffectManager.h"
#include "DebugText.h"

ObjModel* SnowEffectManager::model = nullptr;

SnowEffectManager* SnowEffectManager::Create()
{
	//雪玉エフェクトマネージャーのインスタンスを生成
	SnowEffectManager* snowEffectManager = new SnowEffectManager();
	if (snowEffectManager == nullptr) {
		return nullptr;
	}

	return snowEffectManager;
}

void SnowEffectManager::Update()
{
	//死亡した雪玉エフェクトの削除
	snowEffects.remove_if([](std::unique_ptr<SnowEffect>& snowEffect) {
		return snowEffect->GetIsDead();
		});

	//更新処理
	for (const std::unique_ptr<SnowEffect>& snowEffect : snowEffects) {
		snowEffect->Update();
	}

	std::string snowEffectNum = std::to_string(snowEffects.size());
	DebugText::GetInstance()->Print("snowEffectNum : " + snowEffectNum, 100, 200);
}

void SnowEffectManager::Draw()
{
	//描画
	for (const std::unique_ptr<SnowEffect>& snowEffect : snowEffects) {
		snowEffect->Draw();
	}
}

void SnowEffectManager::AddSnowEffect(const Vector3& position)
{
	//雪玉エフェクトを追加
	for (int i = 0; i < 20; i++) {
		//ランダムでエフェクトの移動速度をセット
		const Vector3 randVel = { 10, 10, 10 };
		Vector3 velocity;
		velocity.x = (float)((rand() % (int)randVel.x) - randVel.x / 2);
		velocity.y = (float)((rand() % (int)randVel.y));
		velocity.z = (float)((rand() % (int)randVel.z) - randVel.z / 2);

		//値が大きいので割り算して小さくする
		const float div = 10;
		velocity /= div;

		std::unique_ptr<SnowEffect> newSnowEffect;
		newSnowEffect.reset(SnowEffect::Create(model, position, 0.3f, velocity));
		snowEffects.push_back(std::move(newSnowEffect));
	}
}
