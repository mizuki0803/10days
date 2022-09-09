#include "Player.h"
#include "Input.h"
#include "GameScene.h"

const Vector2 Player::rotLimit = { 35.0f, 25.0f };

Player* Player::Create(ObjModel* model)
{
	//���@�̃C���X�^���X�𐶐�
	Player* player = new Player();
	if (player == nullptr) {
		return nullptr;
	}

	//���f�����Z�b�g
	assert(model);
	player->model = model;

	// ������
	if (!player->Initialize()) {
		delete player;
		assert(0);
		return nullptr;
	}

	return player;
}

bool Player::Initialize()
{
	position = { 0 ,1 ,10 };
	scale = { 1.0f, 1.0f, 1.0f };

	//3D�I�u�W�F�N�g�̏�����
	if (!ObjObject3d::Initialize()) {
		return false;
	}

	return true;
}

void Player::Update()
{
	//��]
	Rotate();

	ChangeScale();

	//�_���[�W��ԂȂ�m�b�N�o�b�N����
	if (isDamage) {
		Knockback();
	}
	//�_���[�W��ԂłȂ��Ȃ�ʏ�ړ�
	else {
		Move();
	}

	//�I�u�W�F�N�g�X�V
	ObjObject3d::Update();
}

void Player::OnCollisionDamage(const Vector3& subjectPos)
{
	//�_���[�W��ԂȂ甲����
	if (isDamage) { return; }

	//�_���[�W����炤
	Damage();

	//�m�b�N�o�b�N�����Z�b�g
	SetKnockback(subjectPos);
}

Vector3 Player::GetWorldPos()
{
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���s�ړ��������擾
	worldPos.x = matWorld.r[3].m128_f32[0];
	worldPos.y = matWorld.r[3].m128_f32[1];
	worldPos.z = matWorld.r[3].m128_f32[2];

	return worldPos;
}

void Player::Damage()
{
	//�̗͂����炷
	HP -= 10;

	//HP��0�ȉ��ɂȂ����玀�S������
	if (HP <= 0) {
		isDead = true;

		//HP��0�ȉ��ɂȂ�Ȃ�
		HP = 0;
	}

	//���̓m�b�N�o�b�N������̂Ő��m�ȋ����ɂ͂Ȃ��Ă��Ȃ�
	if (ballScale < 2.0f)
	{
		//��ʂ̎��Ԃ�0�ɂ���(�ړ��ʗp)
		time /= 2.0f;
	}
	else if (ballScale < 3.0f)
	{
		//��ʂ̎��Ԃ�0�ɂ���(�ړ��ʗp)
		time /= 1.5f;
	}
	else if (ballScale < 4.0f)
	{
		//��ʂ̎��Ԃ�0�ɂ���(�ړ��ʗp)
		time /= 1.2f;
	}


	color = { 1,0,0,1 };

	//�_���[�W��Ԃɂ���
	isDamage = true;
}

void Player::Rotate()
{
	Input* input = Input::GetInstance();

	//��]���x
	const float rotSpeed = 1.0f;
	//�p�x�C�����x
	const float backSpeed = rotSpeed / 1.5f;
	Vector3 rot = { 0, 0, 0 };

	//�ǂ��܂ŌX�����画����Ƃ邩
	const float stickNum = 200;
	//y����]
	{
		//�L�[���͂ŉ�]������
		if (input->PushKey(DIK_A) || input->PushKey(DIK_D)) {
			if (input->PushKey(DIK_A)) { rot.y -= rotSpeed; }
			if (input->PushKey(DIK_D)) { rot.y += rotSpeed; }
		}

		//�p�b�h�X�e�B�b�NX���̔�������
		else if (input->TiltGamePadLStickX(stickNum) || input->TiltGamePadLStickX(-stickNum)) {
			//���@�̓X�e�B�b�N��|���������ɓ���
			const float padRota = input->GetPadLStickAngle();
			const float moveAngle = XMConvertToRadians(padRota);
			const float padStickIncline = input->GetPadLStickIncline().x;
			rot.y = rotSpeed * cosf(moveAngle) * fabsf(padStickIncline);
		}

		//�L�[���͂Ȃ�&�X�e�B�b�N��|���Ă��Ȃ��ꍇ
		else {
			//y����]�̌X�����C������
			if (rotation.y > 1.0f) {
				rot.y -= backSpeed;
			}
			else if (rotation.y < -1.0f) {
				rot.y += backSpeed;
			}
			else {
				rotation.y = 0;
			}
		}
	}
	//x����]
	{
		rot.x = rotSpeed * (scale.x);
	}

	//��]�̍X�V
	rotation += rot;

	//�p�x�̌��E�l����͂ݏo���Ȃ�
	rotation.y = max(rotation.y, -rotLimit.y);
	rotation.y = min(rotation.y, +rotLimit.y);
}

void Player::Move()
{
	//�ړ��ʗp�̃^�C�}�[
	time += 0.02f;
	//���@���X���Ă���p�x�Ɉړ�������
	Vector3 move = { 0, 0, 0 };
	const float moveSpeed = 0.4f * ((scale.x * scale.x) / 10);
	move.x = moveSpeed * (rotation.y / rotLimit.y);
	//move.y = moveSpeed * -(rotation.x / rotLimit.x);
	move.z = VelicityZ(time);
	position += move;

	position.y = ballScale;

	//�ړ����E����o�Ȃ��悤�ɂ���(Z��ǉ������̂�Vector3�ɂ���)
	const Vector3 moveLimit = { 20.0f, 5.0f, goalPosition };
	position.x = max(position.x, -moveLimit.x);
	position.x = min(position.x, +moveLimit.x);
	position.y = max(position.y, -moveLimit.y);
	position.y = min(position.y, +moveLimit.y);
	position.z = max(position.z, -moveLimit.z);
	position.z = min(position.z, +moveLimit.z);
}

void Player::SetKnockback(const Vector3& subjectPos)
{
	//�m�b�N�o�b�N������������߂�(���@�̃��[���h���W - �Ώۂ̃��[���h���W)
	knockbackVec = GetWorldPos() - subjectPos;
	//�x�N�g���𐳋K��
	knockbackVec.normalize();

	//�m�b�N�o�b�N�^�C�}�[��������
	knockbackTimer = 0;
}

void Player::Knockback()
{
	//�m�b�N�o�b�N���鎞��
	const float knockbackTime = 30;
	knockbackTimer++;
	const float time = knockbackTimer / knockbackTime;

	//���x���쐬
	knockbackVel = knockbackVec;
	knockbackVel.normalize();
	//Z�������ɂ͈ړ����Ȃ��悤�ɂ���
	knockbackVel.z = 0;
	//�m�b�N�o�b�N���Ԃ𑬓x�ɂ����Č������ۂ�����
	knockbackVel *= (1 - time);

	//���@���m�b�N�o�b�N������
	const float speed = 0.2f;
	position.x += knockbackVel.x *= speed;

	//�ړ����E����o�Ȃ��悤�ɂ���(Z��ǉ������̂�Vector3�ɂ���)
	const Vector3 moveLimit = { 10.0f, 5.0f, goalPosition };
	position.x = max(position.x, -moveLimit.x);
	position.x = min(position.x, +moveLimit.x);
	position.y = max(position.y, -moveLimit.y);
	position.y = min(position.y, +moveLimit.y);
	position.z = max(position.z, -moveLimit.z);
	position.z = min(position.z, +moveLimit.z);

	//�m�b�N�o�b�N���I��������_���[�W��Ԃ���������
	if (knockbackTimer >= knockbackTime) {
		isDamage = false;
		color = { 1,1,1,1 };
	}
}

void Player::ChangeScale()
{
	if (isDamage)
	{
		if (ballScale < 2.0f)
		{
			ballScale = 1.0f;
		}
		else if (ballScale < 3.0f)
		{
			ballScale /= 1.5f;
		}
		else if (ballScale < 4.0f)
		{
			ballScale /= 1.2f;
		}
		else
		{
			ballScale /= 1.05f;
		}
	}
	else
	{
		if (ballScale < 5.0f)
		{
			ballScale += scaleRate;
		}
		else
		{
			ballScale = 5.0f;
		}
	}
	scale = { ballScale,ballScale,ballScale };
}

float Player::VelicityZ(float time)
{
	float velZ = (speedRate + scale.x / 50) * time;
	return velZ;
}
