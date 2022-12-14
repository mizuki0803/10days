#pragma once
#include <DirectXMath.h>
#include "Vector3.h"

using namespace DirectX;

/// <summary>
/// カメラ
/// </summary>
class Camera
{
protected: // エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	/// <summary>
	/// カメラ初期化
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// カメラアングルを更新
	/// </summary>
	void UpdateAngle();

	/// <summary>
	/// ビュー行列を更新
	/// </summary>
	void UpdateMatView();

	/// <summary>
	/// 射影行列を更新
	/// </summary>
	void UpdateMatProjection();

	/// <summary>
	/// ベクトルによる移動
	/// </summary>
	/// <param name="move">移動量</param>
	void MoveVector(const Vector3& move);

	/// <summary>
	/// ベクトルによる視点移動
	/// </summary>
	/// <param name="move">移動量</param>
	void MoveEyeVector(const Vector3& move);

	/// <summary>
	/// ベクトルによる注視点移動
	/// </summary>
	/// <param name="move">移動量</param>
	void MoveTargetVector(const Vector3& move);

	/// <summary>
	/// シェイク開始
	/// </summary>
	/// <param name="shakeTime">シェイク時間</param>
	/// <param name="shakePower">シェイクの強さ</param>
	void ShakeStart(float shakeTime, float shakePower);

	//getter
	const Vector3& GetEye() { return eye; }
	const Vector3& GetTarget() { return target; }
	const XMMATRIX& GetMatView() { return matView; }
	const XMMATRIX& GetMatProjection() { return matProjection; }
	const XMMATRIX& GetMatBillboard() { return matBillboard; }
	const XMMATRIX& GetMatBillboardY() { return matBillboardY; }
	const Vector3& GetAngle() { return angle; }
	const float GetDistance() { return distance; }
	const DirectX::XMMATRIX& GetMatWorld() { return matWorld; }

	//setter
	void SetEye(const Vector3& eye) { this->eye = eye; dirtyView = true; }
	void SetTarget(const Vector3& target) { this->target = target; dirtyView = true; }
	void SetAngle(const Vector3& angle) { this->angle = angle; dirtyAngle = true; }
	void SetDistance(const float distance) { this->distance = distance; dirtyAngle = true; }

protected:
	/// <summary>
	/// シェイク
	/// </summary>
	void Shake();

protected:
	//ワールド変換行列
	DirectX::XMMATRIX matWorld = {};
	// ビュー行列
	XMMATRIX matView = XMMatrixIdentity();
	// 射影行列
	XMMATRIX matProjection = XMMatrixIdentity();
	//ビルボード行列
	XMMATRIX matBillboard = XMMatrixIdentity();
	//Y軸回りのビルボード行列
	XMMATRIX matBillboardY = XMMatrixIdentity();
	// 視点座標
	Vector3 eye = { 0, 1, -10.0f };
	// 注視点座標
	Vector3 target = { 0, 0, 0 };
	// 上方向ベクトル
	Vector3 up = { 0, 1, 0 };
	//カメラの回転角
	Vector3 angle = { 0.0f, 0.0f, 0.0f };
	//targetからカメラまでの距離
	float distance = 10.0f;
	//シェイクするか
	bool isShake = false;
	//カメラシェイク用タイマー
	int32_t shakeTimer = 0;
	//カメラシェイクする時間
	float shakeTime = 0;
	//シェイクする強さ
	float shakePower = 0;
	//ダーティフラグ
	bool dirtyAngle = false;
	bool dirtyView = false;
	bool dirtyProjection = false;
};