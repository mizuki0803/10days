#pragma once
#include "ObjObject3d.h"
#include "Player.h"

/// <summary>
/// 壁
/// </summary>
class SnowWall : public ObjObject3d
{
public:
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <returns>壁</returns>
	static SnowWall* Create(ObjModel* model, const Vector3& position, const Vector3& rotation);

	//setter
	static void SetPlayer(Player* player) { SnowWall::player = player; }

public: //メンバ関数
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	//getter
	const bool GetIsDead() { return isDead; }

public: //メンバ関数
	/// <summary>
	/// 描画範囲かチェック
	/// </summary>
	void CheckIsDraw();

	/// <summary>
	/// 描画範囲かチェック
	/// </summary>
	void CheckIsDead();

private: //静的メンバ変数
	//雪玉
	static Player* player;

private: //メンバ変数
	//描画フラグ
	bool isDraw = false;
	//死亡フラグ
	bool isDead = false;
};