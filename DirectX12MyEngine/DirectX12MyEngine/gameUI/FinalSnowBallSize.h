#pragma once

/// <summary>
/// �ŏI�I�Ȑ�ʂ̑傫�����L�^����
/// </summary>
class FinalSnowBallSize
{
public: //�ÓI�����o�֐�
	/// <summary>
	/// �ŏI�I�Ȑ�ʂ̑傫�����L�^
	/// </summary>
	static void DetermineFinalSize(float finalSize);

	//getter
	static const float GetFinalSize() { return FinalSnowBallSize::finalSize; }

private: //�ÓI�����o�ϐ�
	//�I�����̑傫��
	static float finalSize;
};