#pragma once
#include "NumberSprite.h"
#include <vector>
#include <memory>

/// <summary>
/// 最終的な雪玉の大きさを表示するUI
/// </summary>
class FinalSnowBallSizeUI
{
public:
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <returns>最終的な雪玉の大きさを表示するUI</returns>
	static FinalSnowBallSizeUI* Create(UINT texNumber, const Vector2& position, const Vector2& size, const float finalSnowBallSize);

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize(UINT texNumber, const Vector2& position, const Vector2& size, const float finalSnowBallSize);

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
	/// 数字スプライトの数字を変更
	/// </summary>
	void ChangeNumber(const float finalSnowBallSize);

private: //静的メンバ変数
	static const int numberDigit = 5;

private: //メンバ変数
	//数字スプライト
	std::vector<std::unique_ptr<NumberSprite>> numberSprites;
};