#include "GameScene.h"
#include "SceneManager.h"
#include "Input.h"
#include "Audio.h"
#include "SpriteCommon.h"
#include "DebugText.h"
#include "Easing.h"
#include <cassert>

using namespace DirectX;


void GameScene::Initialize()
{
	//�J����������
	camera.reset(new Camera());
	camera->Initialize();
	//�J�����X�V
	camera->SetAngle({30, 0, 0});

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


	//obj���烂�f���f�[�^��ǂݍ���
	modelSkydome.reset(ObjModel::LoadFromOBJ("skydome"));
	modelSphere.reset(ObjModel::LoadFromOBJ("sphere", true));
	modelSnowBall.reset(ObjModel::LoadFromOBJ("Snowball"));
	modelRock.reset(ObjModel::LoadFromOBJ("Rock"));

	//��ʐ���
	player.reset(Player::Create(modelSnowBall.get()));

	//�␶��
	for (int i = 0; i < 5; i++) {
		std::unique_ptr<Rock> newRock;
		newRock.reset(Rock::Create(modelRock.get(), { (float)i * 6 - 15, 0, 10 }));
		rocks.push_back(std::move(newRock));
	}

	//�V������
	objSkydome.reset(Skydome::Create(modelSkydome.get()));

	//obj�I�u�W�F�N�g�ɃJ�������Z�b�g
	ObjObject3d::SetCamera(camera.get());
	//obj�I�u�W�F�N�g�Ƀ��C�g���Z�b�g
	ObjObject3d::SetLightGroup(lightGroup.get());
}

void GameScene::Update()
{
	//���͂̃C���X�^���X���擾
	Input* input = Input::GetInstance();
	//�f�o�b�O�e�L�X�g�̃C���X�^���X���擾
	DebugText* debugText = DebugText::GetInstance();

	//�J�����X�V
	camera->Update();

	//�I�u�W�F�N�g�X�V
	//���@
	player->Update();
	//��
	for (const std::unique_ptr<Rock>& rock : rocks) {
		rock->Update();
	}
	//�V��
	objSkydome->Update();

	//�Փ˔���Ǘ�
	CollisionCheck3d();

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
	if (input->TriggerKey(DIK_SPACE)) {
		camera->ShakeStart(30, 100);
	}

	//�f�o�b�N�e�L�X�g
	//X���W,Y���W,�k�ڂ��w�肵�ĕ\��
	debugText->Print("GAME SCENE", 1000, 50);

	if (input->TriggerKey(DIK_RETURN)) {
		//�V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("GAME");
	}
}

void GameScene::Draw()
{
	//Object3d���ʃR�}���h
	ObjObject3d::DrawPrev();
	///-------Object3d�`�悱������-------///

	//���@
	player->Draw();
	//��
	for (const std::unique_ptr<Rock>& rock : rocks) {
		rock->Draw();
	}
	//�V��
	objSkydome->Draw();

	///-------Object3d�`�悱���܂�-------///


	//�X�v���C�g���ʃR�}���h
	SpriteCommon::GetInstance()->DrawPrev();
	///-------�X�v���C�g�`�悱������-------///




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

	//���@�ƑS�Ă̊�̏Փ˔���
	for (const std::unique_ptr<Rock>& rock : rocks) {
		//�G���W
		posB = rock->GetWorldPos();
		//�G���a
		radiusB = rock->GetScale().x;

		//���Ƌ��̏Փ˔�����s��
		bool isCollision = Collision::CheckSphereToSphere(posA, posB, radiusA, radiusB);

		//�Փ˂��Ă�����
		if (isCollision) {
			//���@�̃_���[�W�p�R�[���o�b�N�֐����Ăяo��
			player->OnCollisionDamage(posB);

			//�J�����V�F�C�N���J�n
			camera->ShakeStart(30, 100);
		}
	}
#pragma endregion
}
