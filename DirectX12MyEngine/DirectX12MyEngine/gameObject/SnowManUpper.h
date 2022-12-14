#pragma once
#include "ObjObject3d.h"

/// <summary>
/// 雪だるま(上)
/// </summary>
class SnowManUpper : public ObjObject3d
{
public: //静的メンバ関数
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <returns>雪だるま(上)</returns>
	static SnowManUpper* Create(ObjModel* model, const Vector3& position, const Vector3& scale);
};
