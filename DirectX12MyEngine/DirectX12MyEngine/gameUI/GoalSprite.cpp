#include "GoalSprite.h"
#include "Easing.h"

GoalSprite* GoalSprite::Create(UINT texNumber, const Vector2& size)
{
	//�S�[���X�v���C�g�̃C���X�^���X�𐶐�
	GoalSprite* goalSprite = new GoalSprite();
	if (goalSprite == nullptr) {
		return nullptr;
	}

	// ������
	if (!goalSprite->Initialize(texNumber, { 0.5f, 0.5f }, false, false)) {
		delete goalSprite;
		assert(0);
		return nullptr;
	}

	//���W���Z�b�g
	goalSprite->position = { -1200, 300 };

	//�傫�����Z�b�g
	goalSprite->size = size;
	goalSprite->texSize = size;

	return goalSprite;
}

void GoalSprite::Update()
{
	//�ړ�������
	if (isMove) {
		Move();
	}

	//�X�v���C�g�X�V
	Sprite::Update();
}

void GoalSprite::MoveStart()
{
	//�ړ�����
	isMove = true;
}

void GoalSprite::Move()
{
	//�ړ������鎞��
	const float moveTime = 90;
	//�^�C�}�[���X�V
	moveTimer++;
	//�C�[�W���O�œ�����
	const float time = moveTimer / moveTime;
	const float startPos = -500;
	const float stayPos = 640;
	position.x = Easing::OutBack(startPos, stayPos, time);

	//�^�C�}�[���w�肵�����ԂɂȂ�����
	if (moveTimer >= moveTime) {
		//�ړ��I��
		isMove = false;
	}
}
