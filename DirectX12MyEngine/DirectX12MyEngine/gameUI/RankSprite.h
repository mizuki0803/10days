#pragma once
#include "Sprite.h"

/// <summary>
/// ランクスプライト
/// </summary>
class RankSprite : public Sprite
{
public:
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <returns>ランクスプライト</returns>
	static RankSprite* Create(UINT texNumber, const Vector2& position, const Vector2& size);

public: //メンバ関数
	/// <summary>
	/// 表示するランクをセット
	/// </summary>
	/// <param name="rank">表示する番号(S～C)</param>
	void SetRank(const int rank);

private: //メンバ変数
	//表示するランク
	int rank = 0;
};