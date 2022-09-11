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

#include "Rock.h"
#include "Tree.h"

using namespace DirectX;


void GameScene::Initialize()
{
	//�J����������
	camera.reset(new Camera());
	camera->Initialize();

	//���C�g����
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

	//�X�v���C�g���ʕ����̃C���X�^���X���擾
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	//�X�v���C�g�p�e�N�X�`���ǂݍ���
	spriteCommon->LoadTexture(1, "white1x1.png");
	spriteCommon->LoadTexture(2, "Number.png");
	spriteCommon->LoadTexture(3, "miniMap.png");
	spriteCommon->LoadTexture(4, "miniSnowBall.png");


	//obj���烂�f���f�[�^��ǂݍ���
	modelSkydome.reset(ObjModel::LoadFromOBJ("skydome"));
	modelSnowBall.reset(ObjModel::LoadFromOBJ("Snowball", true));
	modelRock.reset(ObjModel::LoadFromOBJ("Rock"));
	modelTree.reset(ObjModel::LoadFromOBJ("tree"));
	modelSnowPlate.reset(ObjModel::LoadFromOBJ("Snowplate"));

	//��ʐ���
	player.reset(Player::Create(modelSnowBall.get()));

	//��ʂ̑傫���\������
	snowBallSizeUI.reset(SnowBallSizeUI::Create(2, { 640, 60 }, { 32, 48 }));
	snowBallSizeUI->SetPlayer(player.get());

	//�J�E���g�_�E��UI�\������
	countdown.reset(Countdown::Create(2, { 640, 120 }, { 32, 48 }));

	//�~�j�}�b�v����
	miniMap.reset(MiniMap::Create(3, 4, { 50, 150 }, { 20, 400 }, goalPosition));
	miniMap->SetPlayer(player.get());

	//��Q������
	LoadObstacleSetData();
	ObstacleSet();
	Obstacle::SetPlayer(player.get());

	//�V������
	skydome.reset(Skydome::Create(modelSkydome.get()));
	skydome->SetRotation({ -30, 0, 0 });
	//��̃t�B�[���h����
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 40; j++) {
			std::unique_ptr<SnowPlate> newSnowPlate;

			Vector3 pos = { -50 + (float)(50 * i), 0, (float)(50 * j) };
			newSnowPlate.reset(SnowPlate::Create(modelSnowPlate.get(), pos));
			snowPlates.push_back(std::move(newSnowPlate));
		}
	}
	SnowPlate::SetPlayer(player.get());

	//�Ƃ肠������ʂɃJ�����Ǐ]������
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
	//obj�I�u�W�F�N�g�ɃJ�������Z�b�g
	ObjObject3d::SetCamera(camera.get());
	//obj�I�u�W�F�N�g�Ƀ��C�g���Z�b�g
	ObjObject3d::SetLightGroup(lightGroup.get());

	//��ʃG�t�F�N�g�}�l�[�W���[�̐���
	snowEffectManager.reset(SnowEffectManager::Create());
	SnowEffectManager::SetModel(modelSnowBall.get());
}

void GameScene::Update()
{
	//���͂̃C���X�^���X���擾
	Input* input = Input::GetInstance();
	//�f�o�b�O�e�L�X�g�̃C���X�^���X���擾
	DebugText* debugText = DebugText::GetInstance();

	//�S�[�����Ă��Ȃ��Ƃ�
	if (!isGoal) {
		//���S������Q���̍폜
		obstacles.remove_if([](std::unique_ptr<Obstacle>& obstacle) {
			return obstacle->GetIsDead();
			});
		//���S������̃t�B�[���h�̍폜
		snowPlates.remove_if([](std::unique_ptr<SnowPlate>& snowPlate) {
			return snowPlate->GetIsDead();
			});

		//��ʂɃJ�����Ǐ]������
		camera->SetTarget(player->GetPosition());
		Vector3 eyePos = player->GetPosition();
		eyePos.y += 10;
		eyePos.z -= 15;
		camera->SetEye(eyePos);
		Vector3 targetPos = player->GetPosition();
		targetPos.z += 5;
		camera->SetTarget(targetPos);

		//�v���C���[���S�[�����C����艜�ɂ�������S�[��
		if (player->GetPosition().z >= goalPosition) {
			isGoal = true;
			player->SetIsGoal(true);

			//�S�[�������u�Ԃ̑傫�����L�^���Ă���
			FinalSnowBallSize::DetermineFinalSize(player->GetScale().x);
		}
	}
	//�S�[����
	else {
		//�S�[����̗]�C����
		const int goalAfterTime = 300;
		//�^�C�}�[���X�V
		goalAfterTimer++;

		//�^�C�}�[���w�肵�����ԂɂȂ�����
		if (goalAfterTimer >= goalAfterTime) {
			//�V�[���؂�ւ�
			SceneManager::GetInstance()->ChangeScene("RESULT");
		}
	}

	//�J�����X�V
	camera->Update();

	//�I�u�W�F�N�g�X�V
	//���@
	player->Update();
	//��Q��
	for (const std::unique_ptr<Obstacle>& obstacle : obstacles) {
		obstacle->Update();
	}
	//�V��
	skydome->Update();
	//��̃t�B�[���h
	for (const std::unique_ptr<SnowPlate>& snowPlate : snowPlates) {
		snowPlate->Update();
	}

	//UI�X�V
	//�傫��UI�X�V
	snowBallSizeUI->Update();
	//�J�E���g�_�E���X�V
	if (countdown) {
		countdown->Update();

		//�J�E���g�_�E�����I��������Q�[���J�n
		if (countdown->GetIsStart()) {
			player->SetIsGameStart(true);
			//�J�E���g�_�E���̃C���X�^���X���폜
			countdown.reset();
		}
	}
	//�~�j�}�b�v�X�V
	miniMap->Update();

	//��ʃG�t�F�N�g�}�l�[�W���[�X�V
	snowEffectManager->Update();

	//�Փ˔���Ǘ�
	CollisionCheck3d();

	//�f�o�b�N�e�L�X�g
	//X���W,Y���W,�k�ڂ��w�肵�ĕ\��
	debugText->Print("GAME SCENE", 1000, 50);
	std::string obstacleNum = std::to_string(obstacles.size());
	DebugText::GetInstance()->Print("obstacle : " + obstacleNum, 10, 50);
	std::string placeNum = std::to_string(snowPlates.size());
	DebugText::GetInstance()->Print("Plate : " + placeNum, 10, 70);

	if (input->TriggerKey(DIK_RETURN)) {
		//�V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("GAME");
	}
	if (input->TriggerKey(DIK_SPACE)) {
		//�V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("RESULT");
		//�S�[�������u�Ԃ̑傫�����L�^���Ă���
		FinalSnowBallSize::DetermineFinalSize(player->GetScale().x);
	}
}

void GameScene::Draw()
{
	//Object3d���ʃR�}���h
	ObjObject3d::DrawPrev();
	///-------Object3d�`�悱������-------///

	//���@
	player->Draw();
	//��Q��
	for (const std::unique_ptr<Obstacle>& obstacle : obstacles) {
		obstacle->Draw();
	}
	//�V��
	skydome->Draw();
	//��̃t�B�[���h
	for (const std::unique_ptr<SnowPlate>& snowPlate : snowPlates) {
		snowPlate->Draw();
	}

	//��ʃG�t�F�N�g�}�l�[�W���[�`��
	snowEffectManager->Draw();

	///-------Object3d�`�悱���܂�-------///


	//�X�v���C�g���ʃR�}���h
	SpriteCommon::GetInstance()->DrawPrev();
	///-------�X�v���C�g�`�悱������-------///

	//UI�`��
	snowBallSizeUI->Draw();
	if (countdown) {
		countdown->Draw();
	}
	//�~�j�}�b�v�X�V
	miniMap->Draw();

	///-------�X�v���C�g�`�悱���܂�-------///


	//�p�[�e�B�N�����ʃR�}���h
	//ParticleManager::DrawPrev();
	///-------�p�[�e�B�N���`�悱������-------///


	//�p�[�e�B�N���`��
	//particleMan->Draw();


	///-------�p�[�e�B�N���`�悱���܂�-------///
}

void GameScene::CollisionCheck3d()
{
	//����Ώۂ̍��W
	Vector3 posA, posB;
	float radiusA, radiusB;

#pragma region ���@�ƓG�̏Փ˔���
	//���@���W
	posA = player->GetWorldPos();
	//���@���a
	radiusA = player->GetScale().x;

	//���@�ƑS�Ă̏�Q���̏Փ˔���
	for (const std::unique_ptr<Obstacle>& obstacle : obstacles) {
		//��Q�����`�悳��Ă��Ȃ���Δ�΂�
		if (!obstacle->GetIsDraw()) { continue; }

		//��Q�����W
		posB = obstacle->GetWorldPos();
		//��Q�����a
		radiusB = obstacle->GetScale().x;

		//���Ƌ��̏Փ˔�����s��
		bool isCollision = Collision::CheckSphereToSphere(posA, posB, radiusA, radiusB);

		//�Փ˂��Ă�����
		if (isCollision) {
			//���@�̃_���[�W�p�R�[���o�b�N�֐����Ăяo��
			player->OnCollisionDamage(posB);

			//�J�����V�F�C�N���J�n
			camera->ShakeStart(30, 100);

			//��ʃG�t�F�N�g�̒ǉ�
			snowEffectManager->AddSnowEffect(player->GetPosition());
		}
	}
#pragma endregion
}

void GameScene::LoadObstacleSetData()
{
	//�t�@�C�����J��
	std::ifstream file;
	file.open("Resources/obstacleSet.csv");
	assert(file.is_open());

	//�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
	obstacleSetCommands << file.rdbuf();

	//�t�@�C�������
	file.close();
}

void GameScene::ObstacleSet()
{
	//1�s���̕����������ϐ�
	std::string line;
	//csv�t�@�C���̐��������Ă���2�dvector
	std::vector<std::vector<int>> mapData;
	//�s��
	int lineNum = 0;

	//�S�Ă̍s��ǂݎ��
	while (getline(obstacleSetCommands, line)) {
		//1�s���̕�������X�g���[���ϊ����ĉ�͂��₷��
		std::istringstream line_stream(line);
		//1����������ϐ�
		std::string word;

		//�s���𑝂₷
		lineNum++;
		mapData.resize(lineNum);

		//�s�̑S�Ă̕�����ǂݎ��
		while (std::getline(line_stream, word, ',')) {
			//�v�f�ԍ���0����Ȃ̂ŁA�s�ԍ� - 1
			const int elementNumber = lineNum - 1;
			//�������L�^
			mapData[elementNumber].push_back(std::atoi(word.c_str()));
		}
	}

	//�ǂݍ��񂾃f�[�^�����ɏ�Q����ݒu����
	for (int i = 0; i < mapData.size(); i++) {
		for (int j = 0; j < mapData[i].size(); j++) {
			//1�̂Ƃ��͊���Z�b�g
			if (mapData[i][j] == 1) {
				std::unique_ptr<Rock> newRock;
				newRock.reset(Rock::Create(modelRock.get(), { (float)j * 5 - 17.5f, 0, (float)i * 50 + 30 }));
				obstacles.push_back(std::move(newRock));
			}
			//2�̂Ƃ��͖؂��Z�b�g
			else if (mapData[i][j] == 2) {
				std::unique_ptr<Tree> newTree;
				newTree.reset(Tree::Create(modelTree.get(), { (float)j * 5 - 17.5f, 0, (float)i * 50 + 30 }));
				obstacles.push_back(std::move(newTree));
			}
		}
	}
}
