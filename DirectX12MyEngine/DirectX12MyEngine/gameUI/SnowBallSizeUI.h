#pragma once
#include "NumberSprite.h"
#include "Player.h"

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
	static SnowBallSizeUI* Create(UINT texNumber, const Vector2& position, const Vector2& size);

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize(UINT texNumber, const Vector2& position, const Vector2& size);

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
	/// 数字スプライトの数字を変更
	/// </summary>
	void ChangeNumber();

private: //静的メンバ変数
	static const int numberDigit = 5;

private: //メンバ変数
	//雪玉
	Player* player = nullptr;
	//数字スプライト
	std::vector<std::unique_ptr<NumberSprite>> numberSprites;
};