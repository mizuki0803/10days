#include "ResultScene.h"
#include "SceneManager.h"
#include "Input.h"
#include "Audio.h"
#include "SpriteCommon.h"
#include "DebugText.h"
#include "Easing.h"
#include "FbxLoader.h"
#include <cassert>
#include <sstream>
#include <iomanip>

#include "FinalSnowBallSize.h"

using namespace DirectX;


void ResultScene::Initialize()
{
	//カメラ初期化
	camera.reset(new Camera());
	camera->Initialize();
	camera->SetEye({ 0, 7, -4 });
	camera->SetTarget({ 0, 5, 5 });

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
	spriteCommon->LoadTexture(1, "finish.png");

	//スプライト生成
	sprite.reset(Sprite::Create(1, { 0, 0 }));
	sprite->SetSize({ 1280, 720 });

	//objからモデルデータを読み込む
	modelSkydome.reset(ObjModel::LoadFromOBJ("skydome"));
	modelSnowBall.reset(ObjModel::LoadFromOBJ("Snowball", true));
	modelRock.reset(ObjModel::LoadFromOBJ("Rock"));
	modelSnowPlate.reset(ObjModel::LoadFromOBJ("Snowplate"));

	//雪だるま生成
	snowMan.reset(SnowMan::Create(modelSnowBall.get(), modelSnowBall.get(), { 0, 0, 15 }, FinalSnowBallSize::GetFinalSize()));

	//天球生成
	skydome.reset(Skydome::Create(modelSkydome.get()));
	//雪のフィールド生成
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 35; j++) {
			std::unique_ptr<SnowPlate> newSnowPlate;

			Vector3 pos = { -50 + (float)(50 * i), 0, (float)(50 * j) };
			newSnowPlate.reset(SnowPlate::Create(modelSnowPlate.get(), pos));
			snowPlates.push_back(std::move(newSnowPlate));
		}
	}

	//objオブジェクトにカメラをセット
	ObjObject3d::SetCamera(camera.get());
	//objオブジェクトにライトをセット
	ObjObject3d::SetLightGroup(lightGroup.get());
}

void ResultScene::Update()
{
	//入力のインスタンスを取得
	Input* input = Input::GetInstance();
	//デバッグテキストのインスタンスを取得
	DebugText* debugText = DebugText::GetInstance();


	//カメラ更新
	camera->Update();

	//雪玉更新
	snowMan->Update();
	//天球
	skydome->Update();
	//雪のフィールド
	for (const std::unique_ptr<SnowPlate>& snowPlate : snowPlates) {
		snowPlate->Update();
	}


	//スプライト更新
	sprite->Update();

	std::string scale = std::to_string(FinalSnowBallSize::GetFinalSize());
	DebugText::GetInstance()->Print("Scale : " + scale, 100, 200);

	//デバックテキスト
	//X座標,Y座標,縮尺を指定して表示
	debugText->Print("RESULT SCENE", 1000, 50);

	if (input->TriggerKey(DIK_SPACE)) {
		//シーン切り替え
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
}

void ResultScene::Draw()
{
	//背景スプライト共通コマンド
	SpriteCommon::GetInstance()->DrawPrev();
	///-------背景スプライト描画ここから-------///


	//sprite->Draw();

	//dxbase->ClearDepthBuffer();

	///-------背景スプライト描画ここまで-------///


	//Object3d共通コマンド
	ObjObject3d::DrawPrev();
	///-------Object3d描画ここから-------///

	//雪玉描画
	snowMan->Draw();
	//天球
	skydome->Draw();
	//雪のフィールド
	for (const std::unique_ptr<SnowPlate>& snowPlate : snowPlates) {
		snowPlate->Draw();
	}


	///-------Object3d描画ここまで-------///


	//スプライト共通コマンド
	SpriteCommon::GetInstance()->DrawPrev();
	///-------スプライト描画ここから-------///


	//sprite->Draw();


	///-------スプライト描画ここまで-------///


	//パーティクル共通コマンド
	ParticleManager::DrawPrev();
	///-------パーティクル描画ここから-------///


	//パーティクル描画
	//particleMan->Draw();


	///-------パーティクル描画ここまで-------///
}

