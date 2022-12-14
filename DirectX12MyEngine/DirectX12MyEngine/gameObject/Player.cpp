#include "Player.h"
#include "Input.h"
#include "GameScene.h"

const Vector2 Player::rotLimit = { 35.0f, 25.0f };

Player* Player::Create(ObjModel* model)
{
	//自機のインスタンスを生成
	Player* player = new Player();
	if (player == nullptr) {
		return nullptr;
	}

	//モデルをセット
	assert(model);
	player->model = model;

	// 初期化
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

	//3Dオブジェクトの初期化
	if (!ObjObject3d::Initialize()) {
		return false;
	}

	return true;
}

void Player::Update()
{
	//ゲーム開始していたらゲーム処理をする
	if (isGameStart) {
		//回転
		Rotate();

		ChangeScale();

		//ダメージ状態ならノックバックする
		if (isDamage) {
			Knockback();
		}
		//ダメージ状態でないなら通常移動
		else {
			Move();
		}
	}

	//オブジェクト更新
	ObjObject3d::Update();
}

void Player::OnCollisionDamage(const Vector3& subjectPos)
{
	//ダメージ状態なら抜ける
	if (isDamage) { return; }

	//ノックバック情報をセット
	SetKnockback(subjectPos);

	//ダメージを喰らう
	Damage();
}

Vector3 Player::GetWorldPos()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//平行移動成分を取得
	worldPos.x = matWorld.r[3].m128_f32[0];
	worldPos.y = matWorld.r[3].m128_f32[1];
	worldPos.z = matWorld.r[3].m128_f32[2];

	return worldPos;
}

void Player::Damage()
{
	time = 0;

	//ダメージ状態にする
	isDamage = true;
	isDam = true;
}

void Player::Rotate()
{
	Input* input = Input::GetInstance();

	//回転速度
	const float rotSpeed = 1.0f;
	//角度修正速度
	const float backSpeed = rotSpeed / 1.5f;
	Vector3 rot = { 0, 0, 0 };

	//どこまで傾けたら判定をとるか
	const float stickNum = 200;
	//y軸回転
	{
		//ゴールしていなければ左右回転を受け付ける
		//キー入力で回転させる
		if (!isGoal && (input->PushKey(DIK_A) || input->PushKey(DIK_D))) {
			if (input->PushKey(DIK_A)) { rot.y -= rotSpeed; }
			if (input->PushKey(DIK_D)) { rot.y += rotSpeed; }
		}

		//パッドスティックX軸の判定を取る
		else if (!isGoal && (input->TiltGamePadLStickX(stickNum) || input->TiltGamePadLStickX(-stickNum))) {
			//自機はスティックを倒した方向に動く
			const float padRota = input->GetPadLStickAngle();
			const float moveAngle = XMConvertToRadians(padRota);
			const float padStickIncline = input->GetPadLStickIncline().x;
			rot.y = rotSpeed * cosf(moveAngle) * fabsf(padStickIncline);
		}

		//キー入力なし&スティックを倒していない場合
		else {
			//y軸回転の傾きを修正する
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
	//x軸回転
	{
		rot.x = rotSpeed * (scale.x);
	}

	//回転の更新
	rotation += rot;

	//角度の限界値からはみ出さない
	rotation.y = max(rotation.y, -rotLimit.y);
	rotation.y = min(rotation.y, +rotLimit.y);
}

void Player::Move()
{
	//移動量用のタイマー
	time += 0.02f;
	//自機が傾いている角度に移動させる
	Vector3 move = { 0, 0, 0 };
	const float moveSpeed = 0.4f * ((scale.x * scale.x) / 10);
	move.x = moveSpeed * (rotation.y / rotLimit.y);
	//move.y = moveSpeed * -(rotation.x / rotLimit.x);
	move.z = VelicityZ(time);
	position += move;

	position.y = ballScale;

	//移動限界から出ないようにする
	const float moveLimitX = 20.0f - scale.x;
	position.x = max(position.x, -moveLimitX);
	position.x = min(position.x, +moveLimitX);
}

void Player::SetKnockback(const Vector3& subjectPos)
{
	//ノックバックする方向を決める(自機のワールド座標 - 対象のワールド座標)
	knockbackVec = GetWorldPos() - subjectPos;
	//ベクトルを正規化
	knockbackVec.normalize();
	//ノックバック字の大きさを記録
	knockbackScale = scale.x;

	//ノックバックタイマーを初期化
	knockbackTimer = 0;
}

void Player::Knockback()
{
	//ノックバックする時間
	const float knockbackTime = 30 + 2 * knockbackScale;
	knockbackTimer++;
	if (knockbackTimer > 0)
	{
		isDam = false;
	}
	const float time = knockbackTimer / knockbackTime;

	//速度を作成
	knockbackVel = knockbackVec;
	knockbackVel.normalize();
	//Y方向には移動しないようにする
	knockbackVel.y = 0;
	//Z方向は大きさで強さが変わる
	knockbackVel.z *= knockbackScale;
	//ノックバック時間を速度にかけて減速っぽくする
	knockbackVel *= (1 - time);

	//自機をノックバックさせる
	const float speed = 0.2f;
	position += knockbackVel *= speed;

	//移動限界から出ないようにする
	const float moveLimitX = 20.0f - scale.x;
	position.x = max(position.x, -moveLimitX);
	position.x = min(position.x, +moveLimitX);

	//ノックバックが終了したらダメージ状態を解除する
	if (knockbackTimer >= knockbackTime) {
		isDamage = false;
		color = { 1,1,1,1 };
	}
}

void Player::ChangeScale()
{
	//ゴール後なら抜ける
	if (isGoal) { return; }

	if (isDam)
	{
		if (ballScale < 2.5f)
		{
			ballScale = 1.0f;
		}
		else if (ballScale < 3.5f)
		{
			ballScale /= 2.5f;
		}
		else if (ballScale < 4.0f)
		{
			ballScale /= 2.25f;
		}
		else
		{
			ballScale /= 2.0f;
		}
	}
	else
	{
		if (!isDamage)
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
	}

	position.y = ballScale;
	scale = { ballScale,ballScale,ballScale };
}

float Player::VelicityZ(float time)
{
	float velZ = (speedRate + scale.x / 50) * time;
	return velZ;
}
