#pragma once
#include "BaseScene.h"
#include "Sprite.h"
#include "ObjObject3d.h"
#include "FbxObject3d.h"
#include "ParticleManager.h"
#include "LightGroup.h"
#include "Camera.h"
#include "CollisionShape.h"
#include "Collision.h"
#include "SnowMan.h"
#include "FinalSnowBallSizeUI.h"
#include "Skydome.h"
#include "SnowPlate.h"
#include "SnowBallRankUI.h"
#include "ResultPushASprite.h"

/// <summary>
/// リザルトシーン
/// </summary>
class ResultScene :public BaseScene
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private: //メンバ変数
	//カメラ
	std::unique_ptr<Camera> camera;

	//ライト
	std::unique_ptr<LightGroup> lightGroup;
	float ambientColor0[3] = { 1,1,1 };
	// 光線方向初期値
	float lightDir0[3] = { 0,0,1 };
	float lightColor0[3] = { 1,0,0 };

	float lightDir1[3] = { 0,1,0 };
	float lightColor1[3] = { 0,1,0 };

	float lightDir2[3] = { 1,0,0 };
	float lightColor2[3] = { 0,0,1 };

	float pointLightPos[3] = { 0,0,0 };
	float pointLightColor[3] = { 1,1,1 };
	float pointLightAtten[3] = { 0.3f, 0.1f, 0.1f };

	float spotLightDir[3] = { 0, -1, 0 };
	float spotLightPos[3] = { 0, 5, 0 };
	float spotLightColor[3] = { 1, 1, 1 };
	float spotLightAtten[3] = { 0.0f, 0.0f, 0.0f };
	float spotLightfactorAngleCos[2] = { 20.0f, 30.0f };

	float circleShadowDir[3] = { 0, -1, 0 };
	float circleShadowAtten[3] = { 0.5f, 0.6f, 0.0f };
	float circleShadowFactorAngle[2] = { 0.0f, 0.5f };

	//objモデルデータ
	std::unique_ptr<ObjModel> modelSkydome;
	std::unique_ptr<ObjModel> modelRock;
	std::unique_ptr<ObjModel> modelSnowBall;
	std::unique_ptr<ObjModel> modelSnowHead;
	std::unique_ptr<ObjModel> modelSnowPlate;

	//雪だるま
	std::unique_ptr<SnowMan> snowMan;
	//最終的な雪玉の大きさ表示
	std::unique_ptr<FinalSnowBallSizeUI> finalSnowBallSizeUI;
	//天球
	std::unique_ptr<Skydome> skydome;
	//雪のフィールド
	std::list < std::unique_ptr<SnowPlate>> snowPlates;
	//雪玉の大きさランクを表示するUI
	std::unique_ptr<SnowBallRankUI> snowBallRankUI;
	//PushAスプライト
	std::unique_ptr<ResultPushASprite> pushASprite;
};