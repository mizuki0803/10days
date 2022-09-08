#pragma once
#include "NumberSprite.h"
#include "Player.h"

/// <summary>
/// 雪玉の大きさを表示するUI
/// </summary>
class Countdown
{
public:
	/// <summary>
	/// 生成処理
	/// </summary>
	/// <returns>雪玉の大きさを表示するUI</returns>
	static Countdown* Create(UINT texNumber, const Vector2& position, const Vector2& size);

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

	/// <summary>
	/// スタート前処理
	/// </summary>
	void BeforeStart();

	//getter
	bool GetIsStart() { return isStart; }


private: //メンバ関数
	/// <summary>
	/// 数字スプライトの数字を変更
	/// </summary>
	void ChangeNumber();

private: //メンバ変数
	//雪玉
	Player* player = nullptr;
	//数字スプライト
	std::vector<std::unique_ptr<NumberSprite>> numberSprites;

	//雪玉ゲーム用変数
	//ゲームに入るフラグ
	bool isStart = false;
	//カウントダウン描画用フラグ
	bool isOne = false;
	bool isTwo = false;
	bool isThree = false;
	//カウントダウン用のタイマー
	int countTime = 300;
};