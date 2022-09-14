#pragma once
#include "ObjObject3d.h"
#include "Vector2.h"
#include <memory>

/// <summary>
/// 自機
/// </summary>
class Player : public ObjObject3d
{
public: //静的メンバ関数
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <returns>自機</returns>
	static Player* Create(ObjModel* model);

	//getter
	static const Vector2& GetRotLimit() { return rotLimit; }

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 衝突時コールバック関数(敵などダメージを喰らう)
	/// </summary>
	void OnCollisionDamage(const Vector3& subjectPos);

	//getter
	Vector3 GetWorldPos();
	const bool GetIsDamage() { return isDamage; }
	const Vector3& GetKnockbackVel() { return knockbackVel; }

	//setter
	void SetIsGameStart(const bool isGameStart) { this->isGameStart = isGameStart; }
	void SetIsGoal(const bool isGoal) { this->isGoal = isGoal; }

protected: //メンバ関数
	/// <summary>
	/// ダメージを喰らう
	/// </summary>
	void Damage();

	/// <summary>
	/// 回転
	/// </summary>
	void Rotate();

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	/// <summary>
	/// ノックバック情報をセット
	/// </summary>
	void SetKnockback(const Vector3& subjectPos);

	/// <summary>
	/// ノックバック
	/// </summary>
	void Knockback();

	/// <summary>
	/// ノックバック
	/// </summary>
	void ChangeScale();

	/// <summary>
	/// 移動量Zの計算
	/// </summary>
	float VelicityZ(float time);


protected: //静的メンバ変数
	//自機の回転限界
	static const Vector2 rotLimit;
	//スピードに掛ける値
	const float speedRate = 0.02f;
	//scaleに掛ける値
	const float scaleRate = 0.0032f;

protected: //メンバ変数
	//ゲーム開始か
	bool isGameStart = false;
	//ゴールしたか
	bool isGoal = false;
	//ダメージフラグ
	bool isDamage = false;
	//ノックバック用タイマー
	int32_t knockbackTimer = 0;
	//ノックバック方向
	Vector3 knockbackVec;
	//ノックバック速度
	Vector3 knockbackVel;
	//ノックバック時の大きさ
	float knockbackScale;
	//時間
	float time = 0.00f;
	//サイズ
	float ballScale = 1.0f;
	bool isDam = false;
};
