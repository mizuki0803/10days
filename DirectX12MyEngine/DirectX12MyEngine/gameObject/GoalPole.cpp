#include "GoalPole.h"

GoalPole* GoalPole::Create(ObjModel* model, const Vector3& position)
{
	//ゴールポールのインスタンスを生成
	GoalPole* goalPole = new GoalPole();
	if (goalPole == nullptr) {
		return nullptr;
	}

	//モデルをセット
	assert(model);
	goalPole->model = model;

	// 初期化
	if (!goalPole->Initialize()) {
		delete goalPole;
		assert(0);
		return nullptr;
	}

	//座標をセット
	goalPole->position = position;

	//座標をセット
	goalPole->scale = { 5, 5, 5 };

	return goalPole;
}
