#pragma once
#include "Sprite.h"
#include <memory>

/// <summary>
/// 暗転スプライト
/// </summary>
class Blackout final
{
private: //シングルトン化
	//コンストラクタを隠蔽
	Blackout() = default;
public:
	//コピーコンストラクタを無効化
	Blackout(const Blackout& blackout) = delete;
	//代入演算子を無効化
	void operator = (const Blackout& blackout) = delete;

public:
	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>暗転</returns>
	static Blackout* GetInstance();

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="texNumber">テクスチャ番号</param>
	/// <returns>成否</returns>
	void Initialize(UINT texNumber);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 暗転状態にセット
	/// </summary>
	void SetBlackout();

	/// <summary>
	/// 暗転解除状態にセット
	/// </summary>
	void SetBlackoutReturn();

	//getter
	const DirectX::XMFLOAT4& GetColor() { return sprite->GetColor(); }
	bool GetIsAllBlack() { return isAllBlack; }
	bool GetIsBlackout() { return isBlackout; }
	bool GetIsBlackReturn() { return isReturn; }

private:
	/// <summary>
	/// 暗転
	/// </summary>
	void BlackoutUpdate();

	/// <summary>
	/// 暗転を戻す
	/// </summary>
	void BlackoutReturn();

private: //静的メンバ変数
	//暗転用スプライト
	std::unique_ptr<Sprite> sprite;
	//真っ暗か
	bool isAllBlack = false;
	//暗転中か
	bool isBlackout = false;
	//暗転する時間タイマー
	int blackoutTimer = 0;
	//暗転を戻すか
	bool isReturn = false;
	//暗転解除する時間タイマー
	int returnTimer = 0;
};