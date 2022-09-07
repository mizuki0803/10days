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
	//�I�[�f�B�I�̃C���X�^���X���擾
	Audio* audio = Audio::GetInstance();

	//���S�̂̃{�����[���ύX
	audio->ChangeVolume(0.1f);
	//audio->PlayWave("BGM.wav", true);

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
	spriteCommon->LoadTexture(1, "finish.png");

	//�X�v���C�g����
	sprite.reset(Sprite::Create(1, { 0, 0 }));
	sprite->SetSize({ 1280, 720 });
}

void ResultScene::Update()
{
	//���͂̃C���X�^���X���擾
	Input* input = Input::GetInstance();
	//�f�o�b�O�e�L�X�g�̃C���X�^���X���擾
	DebugText* debugText = DebugText::GetInstance();


	//���C�g�X�V
	lightGroup->Update();

	//�J�����X�V
	camera->Update();

	//�X�v���C�g�X�V
	sprite->Update();

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


	///-------Object3d�`�悱���܂�-------///


	//�X�v���C�g���ʃR�}���h
	SpriteCommon::GetInstance()->DrawPrev();
	///-------�X�v���C�g�`�悱������-------///


	sprite->Draw();


	///-------�X�v���C�g�`�悱���܂�-------///


	//�p�[�e�B�N�����ʃR�}���h
	ParticleManager::DrawPrev();
	///-------�p�[�e�B�N���`�悱������-------///


	//�p�[�e�B�N���`��
	//particleMan->Draw();


	///-------�p�[�e�B�N���`�悱���܂�-------///
}

