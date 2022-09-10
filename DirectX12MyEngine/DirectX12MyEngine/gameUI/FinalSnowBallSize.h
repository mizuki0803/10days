#pragma once

/// <summary>
/// 最終的な雪玉の大きさを記録する
/// </summary>
class FinalSnowBallSize
{
public: //静的メンバ関数
	/// <summary>
	/// 最終的な雪玉の大きさを記録
	/// </summary>
	static void DetermineFinalSize(float finalSize);

	//getter
	static const float GetFinalSize() { return FinalSnowBallSize::finalSize; }

private: //静的メンバ変数
	//終了時の大きさ
	static float finalSize;
};