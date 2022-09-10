#include "GameScene.h"
#include "SceneManager.h"
#include "Input.h"
#include "Audio.h"
#include "SpriteCommon.h"
#include "DebugText.h"
#include "Easing.h"
#include "FinalSnowBallSize.h"
#include <cassert>
#include <fstream>
#include <iomanip>

using namespace DirectX;


void GameScene::Initialize()
{
	//カメラ初期化
	camera.reset(new Camera());
	camera->Initialize();

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
	spriteCommon->LoadTexture(2, "Number.png");


	//objからモデルデータを読み込む
	modelSkydome.reset(ObjModel::LoadFromOBJ("skydome"));
	modelSnowBall.reset(ObjModel::LoadFromOBJ("Snowball", true));
	modelRock.reset(ObjModel::LoadFromOBJ("Rock"));
	modelSnowPlate.reset(ObjModel::LoadFromOBJ("Snowplate"));

	//雪玉生成
	player.reset(Player::Create(modelSnowBall.get()));

	//雪玉の大きさ表示生成
	snowBallSizeUI.reset(SnowBallSizeUI::Create(2, { 640, 60 }, { 32, 48 }));
	snowBallSizeUI->SetPlayer(player.get());

	//カウントダウンUI表示生成
	countdown.reset(Countdown::Create(2, { 640, 120 }, { 32, 48 }));

	//岩生成
	LoadObstacleSetData();
	ObstacleSet();

	//天球生成
	skydome.reset(Skydome::Create(modelSkydome.get()));
	skydome->SetRotation({ -30, 0, 0 });
	//雪のフィールド生成
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 35; j++) {
			std::unique_ptr<SnowPlate> newSnowPlate;

			Vector3 pos = { -50 + (float)(50 * i), 0, (float)(50 * j) };
			newSnowPlate.reset(SnowPlate::Create(modelSnowPlate.get(), pos));
			snowPlates.push_back(std::move(newSnowPlate));
		}
	}

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
	camera->Update();
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


	//とりあえず雪玉にカメラ追従させる
	camera->SetTarget(player->GetPosition());
	Vector3 eyePos = player->GetPosition();
	eyePos.y += 10;
	eyePos.z -= 15;
	camera->SetEye(eyePos);
	Vector3 targetPos = player->GetPosition();
	targetPos.z += 5;
	camera->SetTarget(targetPos);
	//カメラ更新
	camera->Update();

	countdown->Update();

	bool isStart = countdown->GetIsStart();

	//オブジェクト更新
	if (isStart)
	{
		//自機
		player->Update();
	}
	//岩
	for (const std::unique_ptr<Rock>& rock : rocks) {
		rock->Update();
	}
	//天球
	skydome->Update();
	//雪のフィールド
	for (const std::unique_ptr<SnowPlate>& snowPlate : snowPlates) {
		snowPlate->Update();
	}

	//UI更新
	snowBallSizeUI->Update();

	//衝突判定管理
	CollisionCheck3d();

	//デバックテキスト
	//X座標,Y座標,縮尺を指定して表示
	debugText->Print("GAME SCENE", 1000, 50);

	if (input->TriggerKey(DIK_RETURN)) {
		//シーン切り替え
		SceneManager::GetInstance()->ChangeScene("GAME");
	}
	if (input->TriggerKey(DIK_SPACE)) {
		FinalSnowBallSize::DetermineFinalSize(player->GetScale().x);

		//シーン切り替え
		SceneManager::GetInstance()->ChangeScene("RESULT");
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
	skydome->Draw();
	//雪のフィールド
	for (const std::unique_ptr<SnowPlate>& snowPlate : snowPlates) {
		snowPlate->Draw();
	}

	///-------Object3d描画ここまで-------///


	//スプライト共通コマンド
	SpriteCommon::GetInstance()->DrawPrev();
	///-------スプライト描画ここから-------///

	//UI描画
	snowBallSizeUI->Draw();
	countdown->Draw();

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

void GameScene::LoadObstacleSetData()
{
	//ファイルを開く
	std::ifstream file;
	file.open("Resources/obstacleSet.csv");
	assert(file.is_open());

	//ファイルの内容を文字列ストリームにコピー
	obstacleSetCommands << file.rdbuf();

	//ファイルを閉じる
	file.close();
}

void GameScene::ObstacleSet()
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
				rocks.push_back(std::move(newRock));
			}
		}
	}
}
