#pragma once
#include "RankSprite.h"
#include "RankWordSprite.h"
#include <memory>

/// <summary>
/// 雪玉の大きさランクを表示するUI
/// </summary>
class SnowBallRankUI
{
public:
	enum class Rank
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
	static SnowBallRankUI* Create(UINT rankTexNumber, UINT wordTexNumber, const Vector2& position, const float snowBallSize);

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize(UINT rankTexNumber, UINT wordTexNumber, const Vector2& position, const float snowBallSize);

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
	void SetRank(const float snowBallSize);

private: //メンバ変数
	//ランクスプライト
	std::unique_ptr<RankSprite> rankSprite;
	//文字の「ランク」スプライト
	std::unique_ptr<RankWordSprite> rankWordSprite;
	//ランク
	Rank rank = Rank::None;
};