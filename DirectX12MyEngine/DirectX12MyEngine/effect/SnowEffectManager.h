#pragma once
#include "SnowEffect.h"

/// <summary>
/// 雪玉エフェクトマネージャー
/// </summary>
class SnowEffectManager
{
public: //静的メンバ関数
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <returns>天球</returns>
	static SnowEffectManager* Create();

	//setter
	static void SetModel(ObjModel* model) { SnowEffectManager::model = model; }

public: //メンバ関数
	/// <summary>
	/// 更新
	/// </summary>
	/// <returns></returns>
	void Update();

	/// <summary>
	/// 更新
	/// </summary>
	/// <returns></returns>
	void Draw();

	/// <summary>
	/// エフェクト追加
	/// </summary>
	void AddSnowEffect(const Vector3& position);

private: //静的メンバ変数
	static ObjModel* model;

private: //メンバ変数
	//雪玉リスト
	std::list<std::unique_ptr<SnowEffect>> snowEffects;
};