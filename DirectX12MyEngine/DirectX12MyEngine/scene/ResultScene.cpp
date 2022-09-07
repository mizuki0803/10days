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

using namespace DirectX;


void ResultScene::Initialize()
{
	//オーディオのインスタンスを取得
	Audio* audio = Audio::GetInstance();

	//音全体のボリューム変更
	audio->ChangeVolume(0.1f);
	//audio->PlayWave("BGM.wav", true);

	//カメラ初期化
	camera.reset(new Camera());
	camera->Initialize();
	camera->SetTarget({ 0, 2.5f, 0 });
	camera->SetDistance(8.0f);

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
}

void ResultScene::Update()
{
	//入力のインスタンスを取得
	Input* input = Input::GetInstance();
	//デバッグテキストのインスタンスを取得
	DebugText* debugText = DebugText::GetInstance();


	//ライト更新
	lightGroup->Update();

	//カメラ更新
	camera->Update();

	//スプライト更新
	sprite->Update();

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


	///-------Object3d描画ここまで-------///


	//スプライト共通コマンド
	SpriteCommon::GetInstance()->DrawPrev();
	///-------スプライト描画ここから-------///


	sprite->Draw();


	///-------スプライト描画ここまで-------///


	//パーティクル共通コマンド
	ParticleManager::DrawPrev();
	///-------パーティクル描画ここから-------///


	//パーティクル描画
	//particleMan->Draw();


	///-------パーティクル描画ここまで-------///
}

