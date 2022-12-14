#pragma once
#include "Obstacle.h"

/// <summary>
/// 木
/// </summary>
class Tree : public Obstacle
{
public: //静的メンバ関数
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <returns>木</returns>
	static Tree* Create(ObjModel* model, const Vector3& position);
};
