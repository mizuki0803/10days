#pragma once
#include "BaseScene.h"
#include "Sprite.h"
#include "ObjObject3d.h"
#include "ParticleManager.h"
#include "LightGroup.h"
#include "Camera.h"
#include "CollisionShape.h"
#include "Collision.h"
#include "Player.h"
#include "SnowBallSizeUI.h"
#include "Obstacle.h"
#include "Skydome.h"
#include "SnowPlate.h"
#include "SnowWall.h"
#include "GoalPole.h"
#include "PadStickUI.h"
#include "Countdown.h"
#include "MiniMap.h"
#include "GoalSprite.h"
#include "SnowEffectManager.h"
#include <sstream>

/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene :public BaseScene
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 3D�I�u�W�F�N�g�̏Փ˔���
	/// </summary>
	void CollisionCheck3d();

	/// <summary>
	/// ��Q��csv�f�[�^�ǂݍ���
	/// </summary>
	void LoadObstacleSetData();

	/// <summary>
	/// ��Q���Z�b�g
	/// </summary>
	void ObstacleSet();

private: //�����o�ϐ�
	//�J����
	std::unique_ptr<Camera> camera;

	//���C�g
	std::unique_ptr<LightGroup> lightGroup;
	float ambientColor0[3] = { 1,1,1 };
	// �������������l
	float lightDir0[3] = { 0,0,1 };
	float lightColor0[3] = { 1,0,0 };

	float lightDir1[3] = { 0,1,0 };
	float lightColor1[3] = { 0,1,0 };

	float lightDir2[3] = { 1,0,0 };
	float lightColor2[3] = { 0,0,1 };

	float pointLightPos[3] = { 0,0,0 };
	float pointLightColor[3] = { 1,1,1 };
	float pointLightAtten[3] = { 0.3f, 0.1f, 0.1f };

	float spotLightDir[3] = { 0, -1, 0 };
	float spotLightPos[3] = { 0, 5, 0 };
	float spotLightColor[3] = { 1, 1, 1 };
	float spotLightAtten[3] = { 0.0f, 0.0f, 0.0f };
	float spotLightfactorAngleCos[2] = { 20.0f, 30.0f };

	float circleShadowDir[3] = { 0, -1, 0 };
	float circleShadowAtten[3] = { 0.5f, 0.6f, 0.0f };
	float circleShadowFactorAngle[2] = { 0.0f, 0.5f };

	//obj���f���f�[�^
	std::unique_ptr<ObjModel> modelSkydome;
	std::unique_ptr<ObjModel> modelRock;
	std::unique_ptr<ObjModel> modelTree;
	std::unique_ptr<ObjModel> modelSnowBall;
	std::unique_ptr<ObjModel> modelSnowPlate;
	std::unique_ptr<ObjModel> modelSnowWall;
	std::unique_ptr<ObjModel> modelGoalPole;

	//���@
	std::unique_ptr<Player> player;
	//��ʂ̑傫���\��
	std::unique_ptr<SnowBallSizeUI> snowBallSizeUI;
	//��Q��
	std::list<std::unique_ptr<Obstacle>> obstacles;
	//��Q���R�}���h
	std::stringstream obstacleSetCommands;
	//�V��
	std::unique_ptr<Skydome> skydome;
	//��̃t�B�[���h
	std::list<std::unique_ptr<SnowPlate>> snowPlates;
	//��
	std::list<std::unique_ptr<SnowWall>> snowWalls;
	//�S�[���|�[��
	std::vector<std::unique_ptr<GoalPole>> goalPoles;

	//�p�b�h�X�e�B�b�NUI
	std::unique_ptr<PadStickUI> padStickUI;
	//�J�E���g�_�E��
	std::unique_ptr<Countdown> countdown;
	//�~�j�}�b�v
	std::unique_ptr<MiniMap> miniMap;
	//�S�[���X�v���C�g
	std::unique_ptr<GoalSprite> goalSprite;
	//��ʃG�t�F�N�g
	std::unique_ptr<SnowEffectManager> snowEffectManager;

	//�S�[���̈ʒu
	const float goalPosition = 1500.0f;
	//�S�[��������
	bool isGoal = false;
	//�S�[����̗]�C����
	int32_t goalAfterTimer = 0;
};
