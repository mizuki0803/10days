#pragma once
#include "Sprite.h"

/// <summary>
/// ゴールスプライト
/// </summary>
class GoalSprite : public Sprite
{
public:
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <returns>ランクスプライト</returns>
	static GoalSprite* Create(UINT texNumber, const Vector2& size);

public: //メンバ関数
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 移動開始
	/// </summary>
	void MoveStart();

public: //メンバ関数
	/// <summary>
	/// 移動
	/// </summary>
	void Move();

private: //メンバ変数
	//移動するか
	bool isMove = false;
	//移動時間タイマー
	int32_t moveTimer = 0;
};