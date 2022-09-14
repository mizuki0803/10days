#pragma once
#include "Obstacle.h"

/// <summary>
/// ゴールポール
/// </summary>
class GoalPole : public Obstacle
{
public: //静的メンバ関数
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <returns>ゴールポール</returns>
	static GoalPole* Create(ObjModel* model, const Vector3& position);
};
