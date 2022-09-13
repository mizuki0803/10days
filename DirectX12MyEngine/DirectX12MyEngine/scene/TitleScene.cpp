#include "TitleScene.h"
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
#include <fstream>
#include <iomanip>

#include "Rock.h"
#include "Tree.h"

using namespace DirectX;


void TitleScene::Initialize()
{
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
	spriteCommon->LoadTexture(1, "title.png");
	spriteCommon->LoadTexture(2, "Number.png");
	spriteCommon->LoadTexture(3, "pushAStart.png");

	//objからモデルデータを読み込む
	modelSkydome.reset(ObjModel::LoadFromOBJ("skydome"));
	modelSnowBall.reset(ObjModel::LoadFromOBJ("Snowball", true));
	modelRock.reset(ObjModel::LoadFromOBJ("Rock"));
	modelTree.reset(ObjModel::LoadFromOBJ("tree"));
	modelSnowPlate.reset(ObjModel::LoadFromOBJ("Snowplate"));

	//雪玉生成
	autoPlayer.reset(AutoPlayer::Create(modelSnowBall.get()));

	//障害物生成
	LoadObstacleSetData();
	ObstacleSet();
	Obstacle::SetPlayer(nullptr);

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
	SnowPlate::SetPlayer(nullptr);

	//とりあえず雪玉にカメラ追従させる
	camera->SetTarget(autoPlayer->GetPosition());
	Vector3 eyePos = autoPlayer->GetPosition();
	eyePos.x = 0;
	eyePos.y += 10;
	eyePos.z -= 15;
	camera->SetEye(eyePos);
	Vector3 targetPos = autoPlayer->GetPosition();
	targetPos.x = 0;
	targetPos.z += 5;
	camera->SetTarget(targetPos);
	camera->Update();
	//objオブジェクトにカメラをセット
	ObjObject3d::SetCamera(camera.get());
	//objオブジェクトにライトをセット
	ObjObject3d::SetLightGroup(lightGroup.get());

	//暗転中なら暗転解除
	if (Blackout::GetInstance()->GetColor().w != 0.0f) {
		Blackout::GetInstance()->SetBlackoutReturn();
	}

	//タイトルロゴ生成
	titleLogo.reset(TitleLogo::Create(1, { 640, 150 }, { 600, 500 }));
	//PushAスプライト生成
	pushASprite.reset(TitlePushASprite::Create(3, { 640, 550 }, { 350, 50 }));

	//タイトルシーン用BGMを再生
	Audio::GetInstance()->PlayWave("titleBGM.wav", true);
}

void TitleScene::Update()
{
	//入力のインスタンスを取得
	Input* input = Input::GetInstance();
	//デバッグテキストのインスタンスを取得
	DebugText* debugText = DebugText::GetInstance();
	//暗転用スプライトのインスタンスを取得
	Blackout* blackout = Blackout::GetInstance();


	//ライト更新
	lightGroup->Update();
	//とりあえず雪玉にカメラ追従させる
	camera->SetTarget(autoPlayer->GetPosition());
	Vector3 eyePos = autoPlayer->GetPosition();
	eyePos.y += 10;
	eyePos.z -= 15;
	camera->SetEye(eyePos);
	Vector3 targetPos = autoPlayer->GetPosition();
	targetPos.z += 5;
	camera->SetTarget(targetPos);
	//カメラ更新
	camera->Update();

	//自機
	autoPlayer->Update();
	//障害物
	for (const std::unique_ptr<Obstacle>& obstacle : obstacles) {
		obstacle->Update();
	}
	//天球
	skydome->Update();
	//雪のフィールド
	for (const std::unique_ptr<SnowPlate>& snowPlate : snowPlates) {
		snowPlate->Update();
	}

	//タイトルロゴ描画
	titleLogo->Update();
	//PushAスプライト更新
	pushASprite->Update();

	//衝突判定管理
	CollisionCheck3d();

	//デバックテキスト
	//X座標,Y座標,縮尺を指定して表示
	//debugText->Print("TITLE SCENE", 1000, 50);

	if (blackout->GetColor().w == 0.0f) {
		if (input->TriggerKey(DIK_SPACE) || input->TriggerGamePadButton(Input::PAD_A)) {
			//暗転開始
			blackout->SetBlackout();
			isStart = true;

			//PushAスプライトの点滅の速さを変える
			pushASprite->ChangeFlashingSpeed();

			//ボタン押した効果音を再生
			Audio::GetInstance()->PlayWave("select01.wav", false);
		}
	}
	//画面が真っ暗になったら
	if (blackout->GetIsAllBlack() && isStart == true) {
		//シーン切り替え
		SceneManager::GetInstance()->ChangeScene("GAME");
		//タイトルシーン用BGM再生を停止
		Audio::GetInstance()->StopWave("titleBGM.wav");
	}
}

void TitleScene::Draw()
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
	//自機
	autoPlayer->Draw();
	//障害物
	for (const std::unique_ptr<Obstacle>& obstacle : obstacles) {
		obstacle->Draw();
	}
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


	//タイトルロゴ描画
	titleLogo->Draw();
	//PushAスプライト描画
	pushASprite->Draw();


	///-------スプライト描画ここまで-------///


	//パーティクル共通コマンド
	ParticleManager::DrawPrev();
	///-------パーティクル描画ここから-------///


	//パーティクル描画
	//particleMan->Draw();


	///-------パーティクル描画ここまで-------///
}

void TitleScene::CollisionCheck3d()
{
	//判定対象の座標
	Vector3 posA, posB;
	float radiusA, radiusB;

#pragma region 自機と敵の衝突判定
	//自機座標
	posA = autoPlayer->GetWorldPos();
	//自機半径
	radiusA = autoPlayer->GetScale().x;

	//自機と全ての障害物の衝突判定
	for (const std::unique_ptr<Obstacle>& obstacle : obstacles) {
		//障害物が描画されていなければ飛ばす
		if (!obstacle->GetIsDraw()) { continue; }

		//障害物座標
		posB = obstacle->GetWorldPos();
		//障害物半径
		radiusB = obstacle->GetScale().x;

		//球と球の衝突判定を行う
		bool isCollision = Collision::CheckSphereToSphere(posA, posB, radiusA, radiusB);

		//衝突していたら
		if (isCollision) {
			//自機のダメージ用コールバック関数を呼び出す
			autoPlayer->OnCollisionDamage(posB);

			//カメラシェイクを開始
			camera->ShakeStart(30, 100);
		}
	}
#pragma endregion
}

void TitleScene::LoadObstacleSetData()
{
	//ファイルを開く
	std::ifstream file;
	file.open("Resources/demoPlay.csv");
	assert(file.is_open());

	//ファイルの内容を文字列ストリームにコピー
	obstacleSetCommands << file.rdbuf();

	//ファイルを閉じる
	file.close();
}

void TitleScene::ObstacleSet()
{
	//1行分の文字列を入れる変数
	std::string line;
	//csvファイルの数字を入れておく2重vector
	std::vector<std::vector<int>> mapData;
	//行数
	int lineNum = 0;

	//全ての行を読み取る
	while (getline(obstacleSetCommands, line)) {
		//1行分の文字列をストリーム変換して解析しやすく
		std::istringstream line_stream(line);
		//1文字を入れる変数
		std::string word;

		//行数を増やす
		lineNum++;
		mapData.resize(lineNum);

		//行の全ての文字を読み取る
		while (std::getline(line_stream, word, ',')) {
			//要素番号は0からなので、行番号 - 1
			const int elementNumber = lineNum - 1;
			//文字を記録
			mapData[elementNumber].push_back(std::atoi(word.c_str()));
		}
	}

	//読み込んだデータを元に障害物を設置する
	for (int i = 0; i < mapData.size(); i++) {
		for (int j = 0; j < mapData[i].size(); j++) {
			//1のときは岩をセット
			if (mapData[i][j] == 1) {
				std::unique_ptr<Rock> newRock;
				newRock.reset(Rock::Create(modelRock.get(), { (float)j * 5 - 17.5f, 0, (float)i * 50 + 30 }));
				obstacles.push_back(std::move(newRock));
			}
			//2のときは木をセット
			else if (mapData[i][j] == 2) {
				std::unique_ptr<Tree> newTree;
				newTree.reset(Tree::Create(modelTree.get(), { (float)j * 5 - 17.5f, 0, (float)i * 50 + 30 }));
				obstacles.push_back(std::move(newTree));
			}
		}
	}
}
