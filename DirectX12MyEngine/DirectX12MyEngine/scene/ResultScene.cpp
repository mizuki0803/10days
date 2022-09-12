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
	spriteCommon->LoadTexture(2, "Number.png");
	spriteCommon->LoadTexture(3, "lank.png");

	//obj���烂�f���f�[�^��ǂݍ���
	modelSkydome.reset(ObjModel::LoadFromOBJ("skydome"));
	modelSnowBall.reset(ObjModel::LoadFromOBJ("Snowball", true));
	modelRock.reset(ObjModel::LoadFromOBJ("Rock"));
	modelSnowPlate.reset(ObjModel::LoadFromOBJ("Snowplate"));

	//�Ⴞ��ܐ���
	snowMan.reset(SnowMan::Create(modelSnowBall.get(), modelSnowBall.get(), { 0, 0, 15 }, FinalSnowBallSize::GetFinalSize()));

	//�ŏI�I�Ȑ�ʂ̑傫���\������
	finalSnowBallSizeUI.reset(FinalSnowBallSizeUI::Create(2, { 640, 60 }, { 32, 48 }, FinalSnowBallSize::GetFinalSize()));

	//�V������
	skydome.reset(Skydome::Create(modelSkydome.get()));
	//��̃t�B�[���h����
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			std::unique_ptr<SnowPlate> newSnowPlate;

			Vector3 pos = { -250 + (float)(50 * i), 0, -50 + (float)(50 * j) };
			newSnowPlate.reset(SnowPlate::Create(modelSnowPlate.get(), pos));
			snowPlates.push_back(std::move(newSnowPlate));
		}
	}
	SnowPlate::SetPlayer(nullptr);

	//obj�I�u�W�F�N�g�ɃJ�������Z�b�g
	ObjObject3d::SetCamera(camera.get());
	//obj�I�u�W�F�N�g�Ƀ��C�g���Z�b�g
	ObjObject3d::SetLightGroup(lightGroup.get());

	//��ʂ̑傫�������N��\������UI
	snowBallLankUI.reset(SnowBallLankUI::Create(3, { 1000, 200 }, { 50, 50 }, FinalSnowBallSize::GetFinalSize()));

	//�Ó]���Ȃ�Ó]����
	if (Blackout::GetInstance()->GetColor().w != 0.0f) {
		Blackout::GetInstance()->SetBlackoutReturn();
	}
}

void ResultScene::Update()
{
	//���͂̃C���X�^���X���擾
	Input* input = Input::GetInstance();
	//�f�o�b�O�e�L�X�g�̃C���X�^���X���擾
	DebugText* debugText = DebugText::GetInstance();
	//�Ó]�p�X�v���C�g�̃C���X�^���X���擾
	Blackout* blackout = Blackout::GetInstance();

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


	//UI�X�V
	//�傫��UI�X�V
	finalSnowBallSizeUI->Update();
	//��ʂ̑傫�������NUI�X�V
	snowBallLankUI->Update();

	std::string scale = std::to_string(FinalSnowBallSize::GetFinalSize());
	DebugText::GetInstance()->Print("Scale : " + scale, 100, 200);

	//�f�o�b�N�e�L�X�g
	//X���W,Y���W,�k�ڂ��w�肵�ĕ\��
	debugText->Print("RESULT SCENE", 1000, 50);

	if (blackout->GetColor().w == 0.0f) {
		if (input->TriggerKey(DIK_SPACE) || input->TriggerGamePadButton(Input::PAD_A)) {
			//�Ó]�J�n
			blackout->SetBlackout();
		}
	}
	//��ʂ��^���ÂɂȂ�����
	if (blackout->GetIsAllBlack()) {
		//�V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
}

void ResultScene::Draw()
{
	//�w�i�X�v���C�g���ʃR�}���h
	SpriteCommon::GetInstance()->DrawPrev();
	///-------�w�i�X�v���C�g�`�悱������-------///


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


	//UI�X�V
	//�傫��UI�X�V
	finalSnowBallSizeUI->Draw();
	//��ʂ̑傫�������NUI�`��
	snowBallLankUI->Draw();


	///-------�X�v���C�g�`�悱���܂�-------///


	//�p�[�e�B�N�����ʃR�}���h
	ParticleManager::DrawPrev();
	///-------�p�[�e�B�N���`�悱������-------///


	//�p�[�e�B�N���`��
	//particleMan->Draw();


	///-------�p�[�e�B�N���`�悱���܂�-------///
}

