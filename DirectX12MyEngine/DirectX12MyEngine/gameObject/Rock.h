#pragma once
#include "ObjObject3d.h"

/// <summary>
/// 岩
/// </summary>
class Rock : public ObjObject3d
{
public: //静的メンバ関数
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <returns>岩</returns>
	static Rock* Create(ObjModel* model, const Vector3& position);

public: //メンバ関数
	//getter
	Vector3 GetWorldPos();
	bool GetIsDead() const { return isDead; }

private: //メンバ変数
	//死亡フラグ
	bool isDead = false;
};
