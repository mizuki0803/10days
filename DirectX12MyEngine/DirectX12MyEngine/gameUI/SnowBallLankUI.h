#pragma once
#include "LankSprite.h"
#include <memory>

/// <summary>
/// 雪玉の大きさランクを表示するUI
/// </summary>
class SnowBallLankUI
{
public:
	enum class Lank 
	{
		S,
		A,
		B,
		C,
		None,
	};

public:
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <returns>雪玉の大きさランクを表示するUI</returns>
	static SnowBallLankUI* Create(UINT texNumber, const Vector2& position, const Vector2& size, const float snowBallSize);

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize(UINT texNumber, const Vector2& position, const Vector2& size, const float snowBallSize);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: //メンバ関数
	/// <summary>
	/// ランクを確定
	/// </summary>
	void SetLank(const float snowBallSize);

private: //メンバ変数
	//ランクスプライト
	std::unique_ptr<LankSprite> lankSprite;
	//ランク
	Lank lank = Lank::None;
};