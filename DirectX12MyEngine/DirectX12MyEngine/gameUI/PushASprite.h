#pragma once
#include "Sprite.h"

/// <summary>
/// PushAスプライト
/// </summary>
class PushASprite : public Sprite
{
public: //静的メンバ関数
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <returns>PushAスプライト</returns>
	static PushASprite* Create(UINT texNumber, const Vector2& position, const Vector2& size);

public: //メンバ関数
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 点滅の速さを変える
	/// </summary>
	void ChangeFlashingSpeed();

private: //メンバ関数
	/// <summary>
	/// 点滅
	/// </summary>
	void Flashing();

	/// <summary>
	/// 描画状態
	/// </summary>
	void DrawMode();

private: //メンバ変数
	//描画するか
	bool isDraw = true;
	//描画状態時間
	int drawModeTime = 50;
	//描画状態の時間タイマー
	int32_t drawModeTimer = 0;
	//点滅の速さ
	int flashingTime = 50;
	//点滅用タイマー
	int32_t flashingTimer = 0;
};