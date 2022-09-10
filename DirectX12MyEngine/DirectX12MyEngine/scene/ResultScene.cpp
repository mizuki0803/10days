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
	//�J����������
	camera.reset(new Camera());
	camera->Initialize();
	camera->SetEye({ 0, 7, -4 });
	camera->SetTarget({ 0, 5, 5 });

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
	spriteCommon->LoadTexture(1, "finish.png");

	//�X�v���C�g����
	sprite.reset(Sprite::Create(1, { 0, 0 }));
	sprite->SetSize({ 1280, 720 });

	//obj���烂�f���f�[�^��ǂݍ���
	modelSkydome.reset(ObjModel::LoadFromOBJ("skydome"));
	modelSnowBall.reset(ObjModel::LoadFromOBJ("Snowball", true));
	modelRock.reset(ObjModel::LoadFromOBJ("Rock"));
	modelSnowPlate.reset(ObjModel::LoadFromOBJ("Snowplate"));

	//�Ⴞ��ܐ���
	snowMan.reset(SnowMan::Create(modelSnowBall.get(), modelSnowBall.get(), { 0, 0, 15 }, FinalSnowBallSize::GetFinalSize()));

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

	//obj�I�u�W�F�N�g�ɃJ�������Z�b�g
	ObjObject3d::SetCamera(camera.get());
	//obj�I�u�W�F�N�g�Ƀ��C�g���Z�b�g
	ObjObject3d::SetLightGroup(lightGroup.get());
}

void ResultScene::Update()
{
	//���͂̃C���X�^���X���擾
	Input* input = Input::GetInstance();
	//�f�o�b�O�e�L�X�g�̃C���X�^���X���擾
	DebugText* debugText = DebugText::GetInstance();


	//�J�����X�V
	camera->Update();

	//��ʍX�V
	snowMan->Update();
	//�V��
	skydome->Update();
	//��̃t�B�[���h
	for (const std::unique_ptr<SnowPlate>& snowPlate : snowPlates) {
		snowPlate->Update();
	}


	//�X�v���C�g�X�V
	sprite->Update();

	std::string scale = std::to_string(FinalSnowBallSize::GetFinalSize());
	DebugText::GetInstance()->Print("Scale : " + scale, 100, 200);

	//�f�o�b�N�e�L�X�g
	//X���W,Y���W,�k�ڂ��w�肵�ĕ\��
	debugText->Print("RESULT SCENE", 1000, 50);

	if (input->TriggerKey(DIK_SPACE)) {
		//�V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
}

void ResultScene::Draw()
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

	//��ʕ`��
	snowMan->Draw();
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


	//sprite->Draw();


	///-------�X�v���C�g�`�悱���܂�-------///


	//�p�[�e�B�N�����ʃR�}���h
	ParticleManager::DrawPrev();
	///-------�p�[�e�B�N���`�悱������-------///


	//�p�[�e�B�N���`��
	//particleMan->Draw();


	///-------�p�[�e�B�N���`�悱���܂�-------///
}

