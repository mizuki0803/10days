#pragma once
#include "Sprite.h"

/// <summary>
/// パッドスティックUI
/// </summary>
class PadStickUI : public Sprite
{
public:
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <returns>パッドスティックUI</returns>
	static PadStickUI* Create(UINT texNumber, const Vector2& position, const Vector2& size);

public: //メンバ関数
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

private:
	/// <summary>
	/// スティックを動かす
	/// </summary>
	void StickMove();

private:
	//描画する連番画像の番号
	int drawNum = 0;
	//スプライトの描画変更タイマー
	int32_t changeTimer = 0;
};