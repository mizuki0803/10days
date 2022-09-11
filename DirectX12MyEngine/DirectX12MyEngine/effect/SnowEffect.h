#pragma once
#include "ObjObject3d.h"

/// <summary>
/// 雪玉エフェクト
/// </summary>
class SnowEffect : public ObjObject3d
{
public:
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <returns>天球</returns>
	static SnowEffect* Create(ObjModel* model, const Vector3& position, const float scale, const Vector3& velocity);

public:
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	//getter
	const bool GetIsDead() { return isDead; }

private:
	/// <summary>
	/// 移動させる
	/// </summary>
	void Move();

private:
	//死亡フラグ
	bool isDead = false;
	//移動速度
	Vector3 velocity;
};