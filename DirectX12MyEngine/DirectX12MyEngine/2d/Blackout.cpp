#include "Blackout.h"
#include "Easing.h"

Blackout* Blackout::GetInstance()
{
	static Blackout instance;

	return &instance;
}

void Blackout::Initialize(UINT texNumber)
{
	//スプライトを生成する(アンカーポイントを{ 0, 0 }に設定)
	sprite.reset(Sprite::Create(texNumber, { 0, 0 }));
	sprite->SetPosition({ 0, 0 });
	sprite->SetSize({ 1280, 720 });
	sprite->SetColor({ 0, 0, 0, 0 });
}

void Blackout::Update()
{
	//暗転
	if (isBlackout)
	{
		BlackoutUpdate();
	}
	//暗転解除
	if (isReturn)
	{
		BlackoutReturn();
	}

	//スプライト更新
	sprite->Update();
}

void Blackout::Draw()
{
	//スプライト描画
	sprite->Draw();
}

void Blackout::SetBlackout()
{
	//タイマーを初期化する
	blackoutTimer = 0;

	//暗転状態にセット
	isBlackout = true;
}

void Blackout::SetBlackoutReturn()
{
	//タイマーを初期化する
	returnTimer = 0;

	//暗転解除状態にセット
	isReturn = true;

	//真っ暗ではない
	isAllBlack = false;
}

void Blackout::BlackoutUpdate()
{
	//暗転を行う時間
	const int blackoutTime = 80;

	//タイマー更新
	blackoutTimer++;

	//イージング計算用の時間
	float easeTimer = (float)blackoutTimer / blackoutTime;

	//イージングで暗転
	DirectX::XMFLOAT4 color = sprite->GetColor();
	color.w = Easing::OutQuad(0, 1, easeTimer);
	sprite->SetColor(color);

	//タイマーが指定した時間になったら
	if (blackoutTimer >= blackoutTime) {
		//暗転終了
		isBlackout = false;

		//真っ暗
		isAllBlack = true;
	}
}

void Blackout::BlackoutReturn()
{
	//暗転解除を行う時間
	const int returnTime = 50;

	//タイマー更新
	returnTimer++;

	//イージング計算用の時間
	float easeTimer = (float)returnTimer / returnTime;

	//イージングで暗転解除
	DirectX::XMFLOAT4 color = sprite->GetColor();
	color.w = Easing::OutQuad(1, 0, easeTimer);
	sprite->SetColor(color);

	//タイマーが指定した時間になったら
	if (returnTimer >= returnTime) {
		//暗転を戻すか
		isReturn = false;
	}
}
