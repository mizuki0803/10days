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
	//�J����������
	camera.reset(new Camera());
	camera->Initialize();
	camera->SetTarget({ 0, 2.5f, 0 });
	camera->SetDistance(8.0f);

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
	spriteCommon->LoadTexture(1, "title.png");
	spriteCommon->LoadTexture(2, "Number.png");
	spriteCommon->LoadTexture(3, "pushAStart.png");

	//obj���烂�f���f�[�^��ǂݍ���
	modelSkydome.reset(ObjModel::LoadFromOBJ("skydome"));
	modelSnowBall.reset(ObjModel::LoadFromOBJ("Snowball", true));
	modelRock.reset(ObjModel::LoadFromOBJ("Rock"));
	modelTree.reset(ObjModel::LoadFromOBJ("tree"));
	modelSnowPlate.reset(ObjModel::LoadFromOBJ("Snowplate"));

	//��ʐ���
	autoPlayer.reset(AutoPlayer::Create(modelSnowBall.get()));

	//��Q������
	LoadObstacleSetData();
	ObstacleSet();
	Obstacle::SetPlayer(nullptr);

	//�V������
	skydome.reset(Skydome::Create(modelSkydome.get()));
	//��̃t�B�[���h����
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 35; j++) {
			std::unique_ptr<SnowPlate> newSnowPlate;

			Vector3 pos = { -50 + (float)(50 * i), 0, (float)(50 * j) };
			newSnowPlate.reset(SnowPlate::Create(modelSnowPlate.get(), pos));
			snowPlates.push_back(std::move(newSnowPlate));
		}
	}
	SnowPlate::SetPlayer(nullptr);

	//�Ƃ肠������ʂɃJ�����Ǐ]������
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
	//obj�I�u�W�F�N�g�ɃJ�������Z�b�g
	ObjObject3d::SetCamera(camera.get());
	//obj�I�u�W�F�N�g�Ƀ��C�g���Z�b�g
	ObjObject3d::SetLightGroup(lightGroup.get());

	//�Ó]���Ȃ�Ó]����
	if (Blackout::GetInstance()->GetColor().w != 0.0f) {
		Blackout::GetInstance()->SetBlackoutReturn();
	}

	//�^�C�g�����S����
	titleLogo.reset(TitleLogo::Create(1, { 640, 150 }, { 600, 500 }));
	//PushA�X�v���C�g����
	pushASprite.reset(TitlePushASprite::Create(3, { 640, 550 }, { 350, 50 }));

	//�^�C�g���V�[���pBGM���Đ�
	Audio::GetInstance()->PlayWave("titleBGM.wav", true);
}

void TitleScene::Update()
{
	//���͂̃C���X�^���X���擾
	Input* input = Input::GetInstance();
	//�f�o�b�O�e�L�X�g�̃C���X�^���X���擾
	DebugText* debugText = DebugText::GetInstance();
	//�Ó]�p�X�v���C�g�̃C���X�^���X���擾
	Blackout* blackout = Blackout::GetInstance();


	//���C�g�X�V
	lightGroup->Update();
	//�Ƃ肠������ʂɃJ�����Ǐ]������
	camera->SetTarget(autoPlayer->GetPosition());
	Vector3 eyePos = autoPlayer->GetPosition();
	eyePos.y += 10;
	eyePos.z -= 15;
	camera->SetEye(eyePos);
	Vector3 targetPos = autoPlayer->GetPosition();
	targetPos.z += 5;
	camera->SetTarget(targetPos);
	//�J�����X�V
	camera->Update();

	//���@
	autoPlayer->Update();
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

	//�^�C�g�����S�`��
	titleLogo->Update();
	//PushA�X�v���C�g�X�V
	pushASprite->Update();

	//�Փ˔���Ǘ�
	CollisionCheck3d();

	//�f�o�b�N�e�L�X�g
	//X���W,Y���W,�k�ڂ��w�肵�ĕ\��
	//debugText->Print("TITLE SCENE", 1000, 50);

	if (blackout->GetColor().w == 0.0f) {
		if (input->TriggerKey(DIK_SPACE) || input->TriggerGamePadButton(Input::PAD_A)) {
			//�Ó]�J�n
			blackout->SetBlackout();
			isStart = true;

			//PushA�X�v���C�g�̓_�ł̑�����ς���
			pushASprite->ChangeFlashingSpeed();

			//�{�^�����������ʉ����Đ�
			Audio::GetInstance()->PlayWave("select01.wav", false);
		}
	}
	//��ʂ��^���ÂɂȂ�����
	if (blackout->GetIsAllBlack() && isStart == true) {
		//�V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("GAME");
		//�^�C�g���V�[���pBGM�Đ����~
		Audio::GetInstance()->StopWave("titleBGM.wav");
	}
}

void TitleScene::Draw()
{
	//�w�i�X�v���C�g���ʃR�}���h
	SpriteCommon::GetInstance()->DrawPrev();
	///-------�w�i�X�v���C�g�`�悱������-------///


	//sprite->Draw();

	//dxbase->ClearDepthBuffer();

	///-------�w�i�X�v���C�g�`�悱���܂�-------///


	//Object3d���ʃR�}���h
	ObjObject3d::DrawPrev();
	///-------Object3d�`�悱������-------///
	//���@
	autoPlayer->Draw();
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

	///-------Object3d�`�悱���܂�-------///


	//�X�v���C�g���ʃR�}���h
	SpriteCommon::GetInstance()->DrawPrev();
	///-------�X�v���C�g�`�悱������-------///


	//�^�C�g�����S�`��
	titleLogo->Draw();
	//PushA�X�v���C�g�`��
	pushASprite->Draw();


	///-------�X�v���C�g�`�悱���܂�-------///


	//�p�[�e�B�N�����ʃR�}���h
	ParticleManager::DrawPrev();
	///-------�p�[�e�B�N���`�悱������-------///


	//�p�[�e�B�N���`��
	//particleMan->Draw();


	///-------�p�[�e�B�N���`�悱���܂�-------///
}

void TitleScene::CollisionCheck3d()
{
	//����Ώۂ̍��W
	Vector3 posA, posB;
	float radiusA, radiusB;

#pragma region ���@�ƓG�̏Փ˔���
	//���@���W
	posA = autoPlayer->GetWorldPos();
	//���@���a
	radiusA = autoPlayer->GetScale().x;

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
			autoPlayer->OnCollisionDamage(posB);

			//�J�����V�F�C�N���J�n
			camera->ShakeStart(30, 100);
		}
	}
#pragma endregion
}

void TitleScene::LoadObstacleSetData()
{
	//�t�@�C�����J��
	std::ifstream file;
	file.open("Resources/demoPlay.csv");
	assert(file.is_open());

	//�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
	obstacleSetCommands << file.rdbuf();

	//�t�@�C�������
	file.close();
}

void TitleScene::ObstacleSet()
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
