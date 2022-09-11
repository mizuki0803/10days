#pragma once
#include "Sprite.h"

/// <summary>
/// ランクスプライト
/// </summary>
class LankSprite : public Sprite
{
public:
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <returns>ランクスプライト</returns>
	static LankSprite* Create(UINT texNumber, const Vector2& position, const Vector2& size);

public: //メンバ関数
	/// <summary>
	/// 表示するランクをセット
	/// </summary>
	/// <param name="lank">表示する番号(S～C)</param>
	void SetLank(const int lank);

private: //メンバ変数
	//表示するランク
	int lank = 0;
};