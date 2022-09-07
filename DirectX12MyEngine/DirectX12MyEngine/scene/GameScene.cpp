#include "GameScene.h"
#include "SceneManager.h"
#include "Input.h"
#include "Audio.h"
#include "SpriteCommon.h"
#include "DebugText.h"
#include "Easing.h"
#include <cassert>

using namespace DirectX;


void GameScene::Initialize()
{
	//カメラ初期化
	camera.reset(new Camera());
	camera->Initialize();
	//カメラ更新
	camera->SetAngle({30, 0, 0});

	//ライト生成
	lightGroup.reset(LightGroup::Create());

	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightActive(2, true);
	pointLightPos[0] = 0.5f;
	pointLightPos[1] = 1.0f;
	pointLightPos[2] = 0.0f;
	lightGroup->SetPointLightActive(0, false);
	lightGroup->SetPointLightActive(1, false);
	lightGroup->SetPointLightActive(2, false);
	//lightGroup->SetSpotLightActive(0, true);
	lightGroup->SetCircleShadowActive(0, true);

	//スプライト共通部分のインスタンスを取得
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	//スプライト用テクスチャ読み込み
	spriteCommon->LoadTexture(1, "white1x1.png");


	//objからモデルデータを読み込む
	modelSkydome.reset(ObjModel::LoadFromOBJ("skydome"));
	modelSphere.reset(ObjModel::LoadFromOBJ("sphere", true));
	modelSnowBall.reset(ObjModel::LoadFromOBJ("Snowball"));
	modelRock.reset(ObjModel::LoadFromOBJ("Rock"));

	//雪玉生成
	player.reset(Player::Create(modelSnowBall.get()));

	//岩生成
	for (int i = 0; i < 5; i++) {
		std::unique_ptr<Rock> newRock;
		newRock.reset(Rock::Create(modelRock.get(), { (float)i * 6 - 15, 0, 10 }));
		rocks.push_back(std::move(newRock));
	}

	//天球生成
	objSkydome.reset(Skydome::Create(modelSkydome.get()));

	//objオブジェクトにカメラをセット
	ObjObject3d::SetCamera(camera.get());
	//objオブジェクトにライトをセット
	ObjObject3d::SetLightGroup(lightGroup.get());
}

void GameScene::Update()
{
	//入力のインスタンスを取得
	Input* input = Input::GetInstance();
	//デバッグテキストのインスタンスを取得
	DebugText* debugText = DebugText::GetInstance();

	//カメラ更新
	camera->Update();

	//オブジェクト更新
	//自機
	player->Update();
	//岩
	for (const std::unique_ptr<Rock>& rock : rocks) {
		rock->Update();
	}
	//天球
	objSkydome->Update();

	//衝突判定管理
	CollisionCheck3d();

	//とりあえず雪玉にカメラ追従させる
	camera->SetTarget(player->GetPosition());
	Vector3 eyePos = player->GetPosition();
	eyePos.x = 0;
	eyePos.y += 10;
	eyePos.z -= 15;
	camera->SetEye(eyePos);
	Vector3 targetPos = player->GetPosition();
	targetPos.x = 0;
	targetPos.z += 5;
	camera->SetTarget(targetPos);
	if (input->TriggerKey(DIK_SPACE)) {
		camera->ShakeStart(30, 100);
	}

	//デバックテキスト
	//X座標,Y座標,縮尺を指定して表示
	debugText->Print("GAME SCENE", 1000, 50);

	if (input->TriggerKey(DIK_RETURN)) {
		//シーン切り替え
		SceneManager::GetInstance()->ChangeScene("GAME");
	}
}

void GameScene::Draw()
{
	//Object3d共通コマンド
	ObjObject3d::DrawPrev();
	///-------Object3d描画ここから-------///

	//自機
	player->Draw();
	//岩
	for (const std::unique_ptr<Rock>& rock : rocks) {
		rock->Draw();
	}
	//天球
	objSkydome->Draw();

	///-------Object3d描画ここまで-------///


	//スプライト共通コマンド
	SpriteCommon::GetInstance()->DrawPrev();
	///-------スプライト描画ここから-------///




	///-------スプライト描画ここまで-------///


	//パーティクル共通コマンド
	//ParticleManager::DrawPrev();
	///-------パーティクル描画ここから-------///


	//パーティクル描画
	//particleMan->Draw();


	///-------パーティクル描画ここまで-------///
}

void GameScene::CollisionCheck3d()
{
	//判定対象の座標
	Vector3 posA, posB;
	float radiusA, radiusB;

#pragma region 自機と敵の衝突判定
	//自機座標
	posA = player->GetWorldPos();
	//自機半径
	radiusA = player->GetScale().x;

	//自機と全ての岩の衝突判定
	for (const std::unique_ptr<Rock>& rock : rocks) {
		//敵座標
		posB = rock->GetWorldPos();
		//敵半径
		radiusB = rock->GetScale().x;

		//球と球の衝突判定を行う
		bool isCollision = Collision::CheckSphereToSphere(posA, posB, radiusA, radiusB);

		//衝突していたら
		if (isCollision) {
			//自機のダメージ用コールバック関数を呼び出す
			player->OnCollisionDamage(posB);

			//カメラシェイクを開始
			camera->ShakeStart(30, 100);
		}
	}
#pragma endregion
}
