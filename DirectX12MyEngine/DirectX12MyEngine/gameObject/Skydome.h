#pragma once
#include "ObjObject3d.h"

class Skydome : public ObjObject3d 
{
public:
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <returns>天球</returns>
	static Skydome* Create(ObjModel* model);
};