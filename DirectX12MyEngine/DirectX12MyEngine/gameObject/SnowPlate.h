#pragma once
#include "ObjObject3d.h"

/// <summary>
/// 雪のフィールド
/// </summary>
class SnowPlate : public ObjObject3d
{
public:
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <returns>雪のフィールド</returns>
	static SnowPlate* Create(ObjModel* model, const Vector3& position);
};