#pragma once
#include "SnowManUpper.h"
#include "SnowManUnder.h"

/// <summary>
/// 雪だるま
/// </summary>
class SnowMan
{
public: //静的メンバ関数
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <returns>雪だるま(下)</returns>
	static SnowMan* Create(ObjModel* upperModel, ObjModel* underModel, const Vector3& position, const float underSize);

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize(ObjModel* upperModel, ObjModel* underModel, const Vector3& position, const float underSize);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: //メンバ変数
	//雪だるま(上)
	std::unique_ptr<SnowManUpper> snowManUpper;
	//雪だるま(下)
	std::unique_ptr<SnowManUnder> snowManUnder;
};
