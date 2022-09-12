#pragma once
#include "Sprite.h"
#include <memory>

/// <summary>
/// �Ó]�X�v���C�g
/// </summary>
class Blackout final
{
private: //�V���O���g����
	//�R���X�g���N�^���B��
	Blackout() = default;
public:
	//�R�s�[�R���X�g���N�^�𖳌���
	Blackout(const Blackout& blackout) = delete;
	//������Z�q�𖳌���
	void operator = (const Blackout& blackout) = delete;

public:
	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns>�Ó]</returns>
	static Blackout* GetInstance();

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="texNumber">�e�N�X�`���ԍ�</param>
	/// <returns>����</returns>
	void Initialize(UINT texNumber);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �Ó]��ԂɃZ�b�g
	/// </summary>
	void SetBlackout();

	/// <summary>
	/// �Ó]������ԂɃZ�b�g
	/// </summary>
	void SetBlackoutReturn();

	//getter
	const DirectX::XMFLOAT4& GetColor() { return sprite->GetColor(); }
	bool GetIsAllBlack() { return isAllBlack; }
	bool GetIsBlackout() { return isBlackout; }
	bool GetIsBlackReturn() { return isReturn; }

private:
	/// <summary>
	/// �Ó]
	/// </summary>
	void BlackoutUpdate();

	/// <summary>
	/// �Ó]��߂�
	/// </summary>
	void BlackoutReturn();

private: //�ÓI�����o�ϐ�
	//�Ó]�p�X�v���C�g
	std::unique_ptr<Sprite> sprite;
	//�^���Â�
	bool isAllBlack = false;
	//�Ó]����
	bool isBlackout = false;
	//�Ó]���鎞�ԃ^�C�}�[
	int blackoutTimer = 0;
	//�Ó]��߂���
	bool isReturn = false;
	//�Ó]�������鎞�ԃ^�C�}�[
	int returnTimer = 0;
};