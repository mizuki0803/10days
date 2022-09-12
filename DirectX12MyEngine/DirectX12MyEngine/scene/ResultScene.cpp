#include "ResultScene.h"
#include "SceneManager.h"
#include "Input.h"
#include "Audio.h"
#include "SpriteCommon.h"
#include "DebugText.h"
#include "Blackout.h"
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
	spriteCommon->LoadTexture(2, "Number.png");
	spriteCommon->LoadTexture(3, "lank.png");

	//objからモデルデータを読み込む
	modelSkydome.reset(ObjModel::LoadFromOBJ("skydome"));
	modelSnowBall.reset(ObjModel::LoadFromOBJ("Snowball", true));
	modelRock.reset(ObjModel::LoadFromOBJ("Rock"));
	modelSnowPlate.reset(ObjModel::LoadFromOBJ("Snowplate"));

	//雪だるま生成
	snowMan.reset(SnowMan::Create(modelSnowBall.get(), modelSnowBall.get(), { 0, 0, 15 }, FinalSnowBallSize::GetFinalSize()));

	//最終的な雪玉の大きさ表示生成
	finalSnowBallSizeUI.reset(FinalSnowBallSizeUI::Create(2, { 640, 60 }, { 32, 48 }, FinalSnowBallSize::GetFinalSize()));

	//天球生成
	skydome.reset(Skydome::Create(modelSkydome.get()));
	//雪のフィールド生成
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			std::unique_ptr<SnowPlate> newSnowPlate;

			Vector3 pos = { -250 + (float)(50 * i), 0, -50 + (float)(50 * j) };
			newSnowPlate.reset(SnowPlate::Create(modelSnowPlate.get(), pos));
			snowPlates.push_back(std::move(newSnowPlate));
		}
	}
	SnowPlate::SetPlayer(nullptr);

	//objオブジェクトにカメラをセット
	ObjObject3d::SetCamera(camera.get());
	//objオブジェクトにライトをセット
	ObjObject3d::SetLightGroup(lightGroup.get());

	//雪玉の大きさランクを表示するUI
	snowBallLankUI.reset(SnowBallLankUI::Create(3, { 1000, 200 }, { 50, 50 }, FinalSnowBallSize::GetFinalSize()));

	//暗転中なら暗転解除
	if (Blackout::GetInstance()->GetColor().w != 0.0f) {
		Blackout::GetInstance()->SetBlackoutReturn();
	}
}

void ResultScene::Update()
{
	//入力のインスタンスを取得
	Input* input = Input::GetInstance();
	//デバッグテキストのインスタンスを取得
	DebugText* debugText = DebugText::GetInstance();
	//暗転用スプライトのインスタンスを取得
	Blackout* blackout = Blackout::GetInstance();

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


	//UI更新
	//大きさUI更新
	finalSnowBallSizeUI->Update();
	//雪玉の大きさランクUI更新
	snowBallLankUI->Update();

	std::string scale = std::to_string(FinalSnowBallSize::GetFinalSize());
	DebugText::GetInstance()->Print("Scale : " + scale, 100, 200);

	//デバックテキスト
	//X座標,Y座標,縮尺を指定して表示
	debugText->Print("RESULT SCENE", 1000, 50);

	if (blackout->GetColor().w == 0.0f) {
		if (input->TriggerKey(DIK_SPACE) || input->TriggerGamePadButton(Input::PAD_A)) {
			//暗転開始
			blackout->SetBlackout();
		}
	}
	//画面が真っ暗になったら
	if (blackout->GetIsAllBlack()) {
		//シーン切り替え
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
}

void ResultScene::Draw()
{
	//背景スプライト共通コマンド
	SpriteCommon::GetInstance()->DrawPrev();
	///-------背景スプライト描画ここから-------///


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


	//UI更新
	//大きさUI更新
	finalSnowBallSizeUI->Draw();
	//雪玉の大きさランクUI描画
	snowBallLankUI->Draw();


	///-------スプライト描画ここまで-------///


	//パーティクル共通コマンド
	ParticleManager::DrawPrev();
	///-------パーティクル描画ここから-------///


	//パーティクル描画
	//particleMan->Draw();


	///-------パーティクル描画ここまで-------///
}

