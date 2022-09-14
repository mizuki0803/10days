#pragma once
#include "NumberSprite.h"
#include <vector>
#include <memory>

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
	static Countdown* Create(UINT texNumber, const Vector2& position, const Vector2& size, const Vector2& texSize);

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize(UINT texNumber, const Vector2& position, const Vector2& size, const Vector2& texSize);

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

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();


	//getter
	bool GetIsStart() { return isStart; }

public:
	const int center = 640;
	const int leftSide = -200;
	const int rightSide = 1480;

private: //メンバ関数
	/// <summary>
	/// 数字スプライトの数字を変更
	/// </summary>
	void ChangeNumber();

private: //メンバ変数
	Vector2 pos = { 0, 0 };
	//数字スプライト
	std::vector<std::unique_ptr<NumberSprite>> numberSprites;

	//雪玉ゲーム用変数
	//ゲームに入るフラグ
	bool isStart = false;
	//カウントダウン描画用フラグ
	bool isOne = false;
	bool isTwo = false;
	bool isThree = false;
	//カウントダウン用の変数
	int countTime = 300;
	float onePos;
	float twoPos;
	float threePos;
	float easeTimer;
	float easeTimer2;
	float easeTimer3;
	float timeRate;
};