#include "MiniMapSnowBall.h"

MiniMapSnowBall* MiniMapSnowBall::Create(UINT texNumber, const Vector2& position, const Vector2& size)
{
	//�~�j�}�b�v�̐�ʂ̃C���X�^���X�𐶐�
	MiniMapSnowBall* miniMapSnowBall = new MiniMapSnowBall();
	if (miniMapSnowBall == nullptr) {
		return nullptr;
	}

	// ������
	if (!miniMapSnowBall->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete miniMapSnowBall;
		assert(0);
		return nullptr;
	}

	//���W���Z�b�g
	miniMapSnowBall->position = position;

	//�傫�����Z�b�g
	miniMapSnowBall->size = size;
	miniMapSnowBall->texSize = { 768, 768 };

	return miniMapSnowBall;
}
