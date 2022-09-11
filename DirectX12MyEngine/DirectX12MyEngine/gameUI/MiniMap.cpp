#include "MiniMap.h"

MiniMap* MiniMap::Create(UINT miniMapTexNumber, UINT snowBallTexNumber, const Vector2& position, const Vector2& size, const float goalPos)
{
	//�~�j�}�b�v�̃C���X�^���X�𐶐�
	MiniMap* miniMap = new MiniMap();
	if (miniMap == nullptr) {
		return nullptr;
	}

	// ������
	if (!miniMap->Initialize(miniMapTexNumber, snowBallTexNumber, position, size)) {
		delete miniMap;
		assert(0);
		return nullptr;
	}

	miniMap->goalPos = goalPos;

	return miniMap;
}

bool MiniMap::Initialize(UINT miniMapTexNumber, UINT snowBallTexNumber, const Vector2& position, const Vector2& size)
{
	std::unique_ptr<MiniMapSprite> newMiniMapSprite;
	miniMapSprite.reset(MiniMapSprite::Create(miniMapTexNumber, position, size));

	std::unique_ptr<MiniMapSnowBall> newMiniMapSnowBall;
	Vector2 snowBallPos = position;
	snowBallPos.y += size.y;
	Vector2 snowBallSize = { 40, 40 };
	miniMapSnowBall.reset(MiniMapSnowBall::Create(snowBallTexNumber, snowBallPos, snowBallSize));

    return true;
}

void MiniMap::Update()
{
	//��ʂ̍��W�ύX
	ChangeSnowBallPos();

	//�X�v���C�g�X�V
	miniMapSprite->Update();
	miniMapSnowBall->Update();
}

void MiniMap::Draw()
{
	//�X�v���C�g�`��
	miniMapSprite->Draw();
	miniMapSnowBall->Draw();
}

void MiniMap::ChangeSnowBallPos()
{
	//��ʂ̍��W���擾
	float snowBallPos = player->GetPosition().z;
	if (snowBallPos >= goalPos) {
		snowBallPos = goalPos;
	}

	//�S�[�����W�܂ł̊������v�Z
	const float ratio = snowBallPos / goalPos;

	//���W���X�V
	Vector2 pos = miniMapSnowBall->GetPosition();
	pos.y = miniMapSprite->GetPosition().y + miniMapSprite->GetSize().y - ratio * miniMapSprite->GetSize().y;
	miniMapSnowBall->SetPosition(pos);
}
