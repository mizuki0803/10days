#include "SnowBall.h"

SnowBall* SnowBall::Create(ObjModel* model)
{
	//自機のインスタンスを生成
	SnowBall* snowBall = new SnowBall();
	if (snowBall == nullptr) {
		return nullptr;
	}

	//モデルをセット
	assert(model);
	snowBall->model = model;

	// 初期化
	if (!snowBall->Initialize()) {
		delete snowBall;
		assert(0);
		return nullptr;
	}

	return snowBall;
}

bool SnowBall::Initialize()
{
	position = { 0 ,1 ,10 };
	scale = { 1.5f, 1.5f, 1.5f };

	//3Dオブジェクトの初期化
	if (!ObjObject3d::Initialize()) {
		return false;
	}

	return true;
}

void SnowBall::Update()
{
}
