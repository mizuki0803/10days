#pragma once
#include "ObjObject3d.h"
#include "Player.h"

/// <summary>
/// 障害物
/// </summary>
class Obstacle : public ObjObject3d
{
public: //静的メンバ関数

	//setter
	static void SetPlayer(Player* player) { Obstacle::player = player; }

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
	Vector3 GetWorldPos();
	const bool GetIsDraw() { return isDraw; }
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