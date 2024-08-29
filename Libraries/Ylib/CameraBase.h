#pragma once

namespace Ylib
{
	class CameraBase
	{
	public:
		CameraBase();
		virtual~CameraBase() {};

		// �J�����̐؂�ւ����̏������֐��i�؂�ւ����ɌĂяo���ƕ�Ԃ��Ȃ���I�j
		void InitializeCamera();

		// �J�����̈ʒu�ƃ^�[�Q�b�g���w�肷��֐�
		void SetPositionTarget(const DirectX::SimpleMath::Vector3& eye
			, const DirectX::SimpleMath::Vector3& target);

		// ���_�̈ʒu���擾����֐�
		const DirectX::SimpleMath::Vector3& GetEyePosition() { return m_eyePt; }

		// ���ړ_�̈ʒu���擾����֐�
		const DirectX::SimpleMath::Vector3& GetTargetPosition() { return m_targetPt; }

		// �J�����̈ʒu�ւ̋����̍����ɑ΂��銄����ݒ肷��֐�
		void SetCameraEyeMoveRate(float rate) { m_eyeMoveRate = rate; }

		// �����_�ւ̋����̍����ɑ΂��銄����ݒ肷��֐�
		void SetCameraTargetMoveRate(float rate) { m_targetMoveRate = rate; }

	private:

		// �J�����̈ʒu�ւ̋����̍����ɑ΂��銄��
		static const float EYE_SPEED_RATE;

		// �����_�ւ̋����̍����ɑ΂��銄��
		static const float TARGET_SPEED_RATE;

		// ���_�̈ʒu
		DirectX::SimpleMath::Vector3 m_eyePt;

		// ���ړ_�̈ʒu
		DirectX::SimpleMath::Vector3 m_targetPt;

		// �J�����̈ʒu�ւ̋����̍����ɑ΂��銄��
		float m_eyeMoveRate;

		// �����_�ւ̋����̍����ɑ΂��銄��
		float m_targetMoveRate;

		// �J�����̈ʒu�̏������t���O
		bool m_initFlag;

	};


}