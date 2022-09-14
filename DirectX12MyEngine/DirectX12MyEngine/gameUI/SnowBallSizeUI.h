#pragma once
#include "NumberSprite.h"
#include "MiniMapSnowBall.h"
#include <vector>
#include <memory>

/// <summary>
/// 雪玉の大きさを表示するUI
/// </summary>
class SnowBallSizeUI
{
public:
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <returns>雪玉の大きさを表示するUI</returns>
	static SnowBallSizeUI* Create(UINT numberTexNumber, UINT snowBallTexNumber, const Vector2& position, const Vector2& size, const Vector2& texSize);

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize(UINT numberTexNumber, UINT snowBallTexNumber, const Vector2& position, const Vector2& size, const Vector2& texSize);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(const float snowBallSize);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: //メンバ関数
	/// <summary>
	/// 数字スプライトの数字を変更
	/// </summary>
	void ChangeNumber(const float snowBallSize);

	/// <summary>
	/// 雪玉スプライトの大きさ変更
	/// </summary>
	void ChangeSnowBallSize(const float snowBallSize);

private: //静的メンバ変数
	static const int numberDigit = 5;

private: //メンバ変数
	//数字スプライト
	std::vector<std::unique_ptr<NumberSprite>> numberSprites;
	//雪玉スプライト
	std::unique_ptr<MiniMapSnowBall> snowBallSprite;
};