#include "TitleLogo.h"

TitleLogo* TitleLogo::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//タイトルロゴのインスタンスを生成
	TitleLogo* titleLogo = new TitleLogo();
	if (titleLogo == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!titleLogo->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete titleLogo;
		assert(0);
		return nullptr;
	}

	//座標をセット
	titleLogo->position = position;

	//大きさをセット
	titleLogo->size = size;
	titleLogo->texSize = size;

	return titleLogo;
}
