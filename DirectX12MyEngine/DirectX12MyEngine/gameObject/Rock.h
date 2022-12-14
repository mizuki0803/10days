#pragma once
#include "Obstacle.h"

/// <summary>
/// 岩
/// </summary>
class Rock : public Obstacle
{
public: //静的メンバ関数
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <returns>岩</returns>
	static Rock* Create(ObjModel* model, const Vector3& position);
};
