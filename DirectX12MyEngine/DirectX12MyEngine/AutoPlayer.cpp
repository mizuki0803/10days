#include "AutoPlayer.h"
#include "Input.h"
#include "Blackout.h"
//#include "GameScene.h"

const Vector2 AutoPlayer::rotLimit = { 35.0f, 25.0f };

AutoPlayer* AutoPlayer::Create(ObjModel* model)
{
	//自機のインスタンスを生成
	AutoPlayer* autoPlayer = new AutoPlayer();
	if (autoPlayer == nullptr) {
		return nullptr;
	}

	//モデルをセット
	assert(model);
	autoPlayer->model = model;

	// 初期化
	if (!autoPlayer->Initialize()) {
		delete autoPlayer;
		assert(0);
		return nullptr;
	}

	return autoPlayer;
}

bool AutoPlayer::Initialize()
{
	position = { 0 ,1 ,10 };
	scale = { 1.0f, 1.0f, 1.0f };

	//3Dオブジェクトの初期化
	if (!ObjObject3d::Initialize()) {
		return false;
	}

	return true;
}

void AutoPlayer::Update()
{
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

	Black();

	//オブジェクト更新
	ObjObject3d::Update();
}

void AutoPlayer::OnCollisionDamage(const Vector3& subjectPos)
{
	//ダメージ状態なら抜ける
	if (isDamage) { return; }

	//ダメージを喰らう
	Damage();

	//ノックバック情報をセット
	SetKnockback(subjectPos);
}

Vector3 AutoPlayer::GetWorldPos()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//平行移動成分を取得
	worldPos.x = matWorld.r[3].m128_f32[0];
	worldPos.y = matWorld.r[3].m128_f32[1];
	worldPos.z = matWorld.r[3].m128_f32[2];

	return worldPos;
}

void AutoPlayer::Damage()
{
	//体力を減らす
	HP -= 10;

	//HPが0以下になったら死亡させる
	if (HP <= 0) {
		isDead = true;

		//HPは0以下にならない
		HP = 0;
	}

	//今はノックバックがあるので正確な挙動にはなっていない
	if (ballScale < 2.0f)
	{
		//雪玉の時間を0にする(移動量用)
		time /= 2.0f;
	}
	else if (ballScale < 3.0f)
	{
		//雪玉の時間を0にする(移動量用)
		time /= 1.5f;
	}
	else if (ballScale < 4.0f)
	{
		//雪玉の時間を0にする(移動量用)
		time /= 1.2f;
	}


	color = { 1,0,0,1 };

	//ダメージ状態にする
	isDamage = true;
}

void AutoPlayer::Rotate()
{
	timer++;
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
		//オートプレイ
		if (timer % 300 > 90 && timer % 300 < 150 || timer % 300 > 240 && timer % 300 < 300) {
			if (timer % 300 > 90 && timer % 300 < 150) { rot.y -= rotSpeed; }
			if (timer % 300 > 240 && timer % 300 < 300) { rot.y += rotSpeed; }
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

void AutoPlayer::Move()
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

	//移動限界から出ないようにする(Zを追加したのでVector3にした)
	const float moveLimit = 20;
	position.x = max(position.x, -moveLimit);
	position.x = min(position.x, +moveLimit);
}

void AutoPlayer::SetKnockback(const Vector3& subjectPos)
{
	//ノックバックする方向を決める(自機のワールド座標 - 対象のワールド座標)
	knockbackVec = GetWorldPos() - subjectPos;
	//ベクトルを正規化
	knockbackVec.normalize();

	//ノックバックタイマーを初期化
	knockbackTimer = 0;
}

void AutoPlayer::Knockback()
{
	//ノックバックする時間
	const float knockbackTime = 30;
	knockbackTimer++;
	const float time = knockbackTimer / knockbackTime;

	//速度を作成
	knockbackVel = knockbackVec;
	knockbackVel.normalize();
	//Z軸方向には移動しないようにする
	knockbackVel.z = 0;
	//ノックバック時間を速度にかけて減速っぽくする
	knockbackVel *= (1 - time);

	//自機をノックバックさせる
	const float speed = 0.2f;
	position.x += knockbackVel.x *= speed;

	//移動限界から出ないようにする(Zを追加したのでVector3にした)
	const float moveLimit = 20;
	position.x = max(position.x, -moveLimit);
	position.x = min(position.x, +moveLimit);

	//ノックバックが終了したらダメージ状態を解除する
	if (knockbackTimer >= knockbackTime) {
		isDamage = false;
		color = { 1,1,1,1 };
	}
}

void AutoPlayer::ChangeScale()
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

void AutoPlayer::DemoEnd()
{
	position = { 0 ,1 ,10 };
	ballScale = 1.0f;
	isDamage = false;
	time = 0.0f;
	timer = 0.0f;
	rotation.y = 0;
	Blackout::GetInstance()->SetBlackoutReturn();
	isStart = false;
}

void AutoPlayer::Black()
{
	//暗転用スプライトのインスタンスを取得
	Blackout* blackout = Blackout::GetInstance();

	if (position.z > blackPosition)
	{
		if (blackout->GetColor().w == 0.0f)
		{
			//暗転開始
			blackout->SetBlackout();
			isStart = true;
		}
	}
	//画面が真っ暗になったら
	if (blackout->GetIsAllBlack() && isStart == true) {
		//シーン切り替え
		DemoEnd();
	}
}


float AutoPlayer::VelicityZ(float time)
{
	float velZ = (speedRate + scale.x / 50) * time;
	return velZ;
}
