#pragma once
#include "Sprite.h"

/// <summary>
/// 数字スプライト
/// </summary>
class NumberSprite : public Sprite
{
public:
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <returns>数字スプライト</returns>
	static NumberSprite* Create(UINT texNumber, const Vector2& position, const Vector2& size);

public: //メンバ関数
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 表示する番号を更新
	/// </summary>
	void UpdateNumber();

	/// <summary>
	/// 表示する番号をセット
	/// </summary>
	/// <param name="number">表示する番号(0～9, 10は.)</param>
	void SetNumber(const int number) { this->number = number; }

private: //メンバ変数
	//表示する番号
	int number = 0;
};