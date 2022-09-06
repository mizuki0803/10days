#pragma once
#include "ObjObject3d.h"
#include "Vector2.h"
#include <memory>

//ゲームシーンの前方宣言
class GameScene;

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
	const int GetHP() { return HP; }
	const bool GetIsDamage() { return isDamage; }
	const bool GetIsDead() { return isDead; }
	const Vector3& GetKnockbackVel() { return knockbackVel; }

private: //メンバ関数
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

private: //静的メンバ変数
	//自機の回転限界
	static const Vector2 rotLimit;
	//最大体力
	static const int maxHP = 100;

private: //メンバ変数
	//体力
	int HP = maxHP;
	//ダメージフラグ
	bool isDamage = false;
	//ノックバック用タイマー
	int32_t knockbackTimer = 0;
	//ノックバック方向
	Vector3 knockbackVec;
	//ノックバック速度
	Vector3 knockbackVel;
	//死亡フラグ
	bool isDead = false;
	//z軸ゆらゆら回転が右回転か
	bool isRotZRight = true;
	//z軸ゆらゆら回転用
	float swayZ = 0.0f;
};
