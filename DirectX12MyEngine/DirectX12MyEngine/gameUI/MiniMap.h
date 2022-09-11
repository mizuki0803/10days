#pragma once
#include "MiniMapSprite.h"
#include "MiniMapSnowBall.h"

/// <summary>
/// ミニマップのUI
/// </summary>
class MiniMap
{
public:
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <returns>ミニマップのUI</returns>
	static MiniMap* Create(UINT miniMapTexNumber, UINT snowBallTexNumber, const Vector2& position, const Vector2& size, const float goalPos);

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize(UINT miniMapTexNumber, UINT snowBallTexNumber, const Vector2& position, const Vector2& size);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//getter

	//setter
	void SetPlayer(Player* player) { this->player = player; }

private: //メンバ関数
	/// <summary>
	/// 雪玉の座標を変更
	/// </summary>
	void ChangeSnowBallPos();

private: //メンバ変数
	//雪玉
	Player* player = nullptr;
	//ゴール座標
	float goalPos = 0;
	//マップスプライト
	std::unique_ptr<MiniMapSprite> miniMapSprite;
	//マップスプライト
	std::unique_ptr<MiniMapSnowBall> miniMapSnowBall;
};
