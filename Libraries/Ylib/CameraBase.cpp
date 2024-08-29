#include "pch.h"
#include "CameraBase.h"

// �ꉞ�f�B�t�H���g�l���`���邯�ǒ������ĉ�����
const float Ylib::CameraBase::EYE_SPEED_RATE = 0.05f;		// �J�����̈ʒu�ւ̋����̍����ɑ΂��銄��
const float Ylib::CameraBase::TARGET_SPEED_RATE = 0.1f;	// �����_�ւ̋����̍����ɑ΂��銄��

// �R���X�g���N�^
Ylib::CameraBase::CameraBase()
	: m_initFlag(true)
	, m_eyePt{}
	, m_targetPt{}
	, m_eyeMoveRate(EYE_SPEED_RATE)
	, m_targetMoveRate(TARGET_SPEED_RATE)
{
}


// �J�����̐؂�ւ����̏������֐��i�؂�ւ����ɌĂяo���ƕ�Ԃ��Ȃ���I�j
void Ylib::CameraBase::InitializeCamera()
{
	m_initFlag = true;
	m_eyeMoveRate = EYE_SPEED_RATE;
	m_targetMoveRate = TARGET_SPEED_RATE;


}

// �J�����̈ʒu�ƃ^�[�Q�b�g���w�肷��֐�
void Ylib::CameraBase::SetPositionTarget(
	const DirectX::SimpleMath::Vector3& eye,
	const DirectX::SimpleMath::Vector3& target)
{
	if (m_initFlag == true)
	{
		m_initFlag = false;
		m_eyePt = eye;
		m_targetPt = target;
		return;
	}

	// �J�����̈ʒu���ړ�
	m_eyePt += (eye - m_eyePt) * m_eyeMoveRate;

	// �J�����̃^�[�Q�b�g�̈ʒu���ړ�
	m_targetPt += (target - m_targetPt) * m_targetMoveRate;

}
