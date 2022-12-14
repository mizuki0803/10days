#include "GameScene.h"
#include "SceneManager.h"
#include "Input.h"
#include "Audio.h"
#include "SpriteCommon.h"
#include "DebugText.h"
#include "Blackout.h"
#include "Easing.h"
#include "FinalSnowBallSize.h"
#include <cassert>
#include <fstream>
#include <iomanip>

#include "Rock.h"
#include "Tree.h"

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
	spriteCommon->LoadTexture(1, "CountNumber.png");
	spriteCommon->LoadTexture(2, "Number.png");
	spriteCommon->LoadTexture(3, "miniMap.png");
	spriteCommon->LoadTexture(4, "miniSnowBall.png");
	spriteCommon->LoadTexture(5, "goal.png");
	spriteCommon->LoadTexture(6, "stick.png");


	//objからモデルデータを読み込む
	modelSkydome.reset(ObjModel::LoadFromOBJ("skydome"));
	modelSnowBall.reset(ObjModel::LoadFromOBJ("Snowball", true));
	modelRock.reset(ObjModel::LoadFromOBJ("Rock"));
	modelTree.reset(ObjModel::LoadFromOBJ("tree"));
	modelSnowPlate.reset(ObjModel::LoadFromOBJ("Snowplate"));
	modelSnowWall.reset(ObjModel::LoadFromOBJ("Snowwall", true));
	modelGoalPole.reset(ObjModel::LoadFromOBJ("Goalpole"));

	//雪玉生成
	player.reset(Player::Create(modelSnowBall.get()));

	//雪玉の大きさ表示生成
	snowBallSizeUI.reset(SnowBallSizeUI::Create(2, 4, { 640, 60 }, { 32, 48 }, { 32, 48 }));

	//パッドスティックUI生成
	padStickUI.reset(PadStickUI::Create(6, { 1050, 550 }, { 100, 100 }));

	//カウントダウンUI表示生成
	countdown.reset(Countdown::Create(1, { 640, 200 }, { 100, 100 }, { 1000, 1000 }));

	//ミニマップ生成
	miniMap.reset(MiniMap::Create(3, 4, { 50, 150 }, { 20, 400 }, goalPosition));

	//ゴールスプライト生成
	goalSprite.reset(GoalSprite::Create(5, { 616, 400 }));

	//障害物生成
	LoadObstacleSetData();
	ObstacleSet();
	Obstacle::SetPlayer(player.get());

	//天球生成
	skydome.reset(Skydome::Create(modelSkydome.get()));
	skydome->SetRotation({ -10, 0, 0 });
	//雪のフィールド生成
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 40; j++) {
			std::unique_ptr<SnowPlate> newSnowPlate;

			Vector3 pos = { -50 + (float)(50 * i), 0, (float)(50 * j) };
			newSnowPlate.reset(SnowPlate::Create(modelSnowPlate.get(), pos));
			snowPlates.push_back(std::move(newSnowPlate));
		}
	}
	SnowPlate::SetPlayer(player.get());

	//壁生成
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 40; j++) {
			std::unique_ptr<SnowWall> newSnowWall;

			Vector3 pos = { -20 + (float)(50 * i), 0, (float)(50 * j) };
			if (i == 1) { pos.x -= 11.8f; }
			Vector3 rota = { 0, 90 + 180 * (float)i, 0 };
			newSnowWall.reset(SnowWall::Create(modelSnowWall.get(), pos, rota));
			snowWalls.push_back(std::move(newSnowWall));
		}
	}
	SnowWall::SetPlayer(player.get());

	//ゴールポール生成
	for (int i = 0; i < 2; i++) {
		std::unique_ptr<GoalPole> newGoalPole;
		Vector3 pos = { -19 + (float)(36 * i), 0, goalPosition };
		newGoalPole.reset(GoalPole::Create(modelGoalPole.get(), pos));
		goalPoles.push_back(std::move(newGoalPole));
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

	//雪玉エフェクトマネージャーの生成
	snowEffectManager.reset(SnowEffectManager::Create());
	SnowEffectManager::SetModel(modelSnowBall.get());

	//暗転中なら暗転解除
	if (Blackout::GetInstance()->GetColor().w != 0.0f) {
		Blackout::GetInstance()->SetBlackoutReturn();
	}
}

void GameScene::Update()
{
	//入力のインスタンスを取得
	Input* input = Input::GetInstance();
	//デバッグテキストのインスタンスを取得
	DebugText* debugText = DebugText::GetInstance();
	//暗転用スプライトのインスタンスを取得
	Blackout* blackout = Blackout::GetInstance();

	//オブジェクト更新
	//自機
	player->Update();

	//ゴールしていないとき
	if (!isGoal) {
		//死亡した障害物の削除
		obstacles.remove_if([](std::unique_ptr<Obstacle>& obstacle) {
			return obstacle->GetIsDead();
			});
		//死亡した雪のフィールドの削除
		snowPlates.remove_if([](std::unique_ptr<SnowPlate>& snowPlate) {
			return snowPlate->GetIsDead();
			});

		//雪玉にカメラ追従させる
		Vector3 eyePos = player->GetPosition();
		eyePos.y += 10;
		eyePos.z -= 15;
		camera->SetEye(eyePos);
		Vector3 targetPos = player->GetPosition();
		targetPos.z += 5;
		camera->SetTarget(targetPos);

		//プレイヤーがゴールラインより奥にいったらゴール
		if (player->GetPosition().z >= goalPosition) {
			isGoal = true;

			//プレイヤーをゴール後の動きにする
			player->SetIsGoal(true);

			//ゴールスプライトを動かす
			goalSprite->MoveStart();

			//ゴールした瞬間の大きさを記録しておく
			FinalSnowBallSize::DetermineFinalSize(player->GetScale().x);

			//ゲームシーン用BGM再生を停止
			Audio::GetInstance()->StopWave("gameBGM.wav");

			//ゴール用効果音を再生
			Audio::GetInstance()->PlayWave("finish.wav", false);
		}
	}
	//ゴール後
	else {
		//ゴール後の余韻時間
		const int goalAfterTime = 180;
		//タイマーを更新
		goalAfterTimer++;

		//タイマーが指定した時間になったら
		if (blackout->GetColor().w == 0.0f) {
			if (goalAfterTimer >= goalAfterTime) {
				//暗転開始
				blackout->SetBlackout();
			}
		}
		//画面が真っ暗になったら
		if (blackout->GetIsAllBlack()) {
			//シーン切り替え
			SceneManager::GetInstance()->ChangeScene("RESULT");
		}
	}

	//オブジェクト更新
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
	//壁
	for (const std::unique_ptr<SnowWall>& snowWall : snowWalls) {
		snowWall->Update();
	}
	//ゴールポール
	for (int i = 0; i < 2; i++) {
		goalPoles[i]->Update();
	}

	//カメラ更新
	camera->Update();


	//UI更新
	//大きさUI更新
	snowBallSizeUI->Update(player->GetScale().x);
	//パッドスティックUI更新
	if (padStickUI) {
		padStickUI->Update();

		//プレイヤーが指定した位置を過ぎたら
		const float padStickUIDeadPos = 500;
		if (player->GetPosition().z >= padStickUIDeadPos) {
			//パッドスティックUIのインスタンスを削除
			padStickUI.reset();
		}
	}
	//カウントダウン更新
	if (countdown) {
		countdown->Update();

		//カウントダウンが終了したらゲーム開始
		if (countdown->GetIsStart()) {
			player->SetIsGameStart(true);
			//カウントダウンのインスタンスを削除
			countdown.reset();

			//ゲームシーン用BGMを再生
			Audio::GetInstance()->PlayWave("gameBGM.wav", true);
		}
	}
	//ミニマップ更新
	miniMap->Update(player->GetPosition().z);
	//ゴールスプライト更新
	goalSprite->Update();

	//雪玉エフェクトマネージャー更新
	snowEffectManager->Update();

	//衝突判定管理
	CollisionCheck3d();

	//デバックテキスト
	//X座標,Y座標,縮尺を指定して表示
	/*debugText->Print("GAME SCENE", 1000, 50);
	std::string obstacleNum = std::to_string(obstacles.size());
	DebugText::GetInstance()->Print("obstacle : " + obstacleNum, 10, 50);
	std::string placeNum = std::to_string(snowPlates.size());
	DebugText::GetInstance()->Print("Plate : " + placeNum, 10, 70);*/

	//if (input->TriggerKey(DIK_RETURN)) {
	//	//シーン切り替え
	//	SceneManager::GetInstance()->ChangeScene("GAME");
	//}
	//if (input->TriggerKey(DIK_SPACE)) {
	//	//シーン切り替え
	//	SceneManager::GetInstance()->ChangeScene("RESULT");
	//	//ゴールした瞬間の大きさを記録しておく
	//	FinalSnowBallSize::DetermineFinalSize(player->GetScale().x);
	//}
}

void GameScene::Draw()
{
	//Object3d共通コマンド
	ObjObject3d::DrawPrev();
	///-------Object3d描画ここから-------///

	//自機
	player->Draw();
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
	//壁
	for (const std::unique_ptr<SnowWall>& snowWall : snowWalls) {
		snowWall->Draw();
	}
	//ゴールポール
	for (int i = 0; i < 2; i++) {
		goalPoles[i]->Draw();
	}

	//雪玉エフェクトマネージャー描画
	snowEffectManager->Draw();

	///-------Object3d描画ここまで-------///


	//スプライト共通コマンド
	SpriteCommon::GetInstance()->DrawPrev();
	///-------スプライト描画ここから-------///

	//UI描画
	snowBallSizeUI->Draw();
	if (padStickUI) {
		padStickUI->Draw();
	}
	if (countdown) {
		countdown->Draw();
	}
	//ミニマップ描画
	miniMap->Draw();
	//ゴールスプライト描画
	goalSprite->Draw();

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
			player->OnCollisionDamage(posB);

			//カメラシェイクを開始
			camera->ShakeStart(30, 100);

			//雪玉エフェクトの追加
			snowEffectManager->AddSnowEffect(player->GetPosition());

			//ダメージ効果音を再生
			Audio::GetInstance()->PlayWave("damage.wav", false);
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
