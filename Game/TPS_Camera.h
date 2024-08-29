#pragma once


class TPS_Camera
{
public:


public:
	// �R���X�g���N�^
	TPS_Camera();

	//�f�X�g���N�^
	~TPS_Camera();

	// �X�V�֐�
	void Update();

	// �v���C���[�̈ʒu��ݒ肷��֐� noexcept-> ��O�����̈�����^�C���G���[��f���Ȃ��悤�ɂ��� getter�Z�b�^�[���i�����I�ɂ��j�|�C���^�[��Ԃ��Ȃ��̂Ȃ�����ق����ǂ��B
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& position)noexcept {m_targetPosition = position;}

	//�J�����̉�]�̒��S�̐ݒ�
	void SetrollCentPos(const DirectX::SimpleMath::Vector3& position)noexcept { m_rollCenterPosition = position; }

	//�J�����̉�]�̐ݒ�
	void Setroll(const DirectX::SimpleMath::Vector3& roll)noexcept 
	{
		m_roll = roll; 
		
		//�p�x����(�N�����v����)
		if (m_roll.x < -DirectX::XMConvertToRadians(89))
		{
			m_roll.x = -DirectX::XMConvertToRadians(89);
		}
		if (m_roll.x > DirectX::XMConvertToRadians(89))
		{
			m_roll.x = DirectX::XMConvertToRadians(89);
		}

	}

	void SetOffSet(const DirectX::SimpleMath::Vector3& offset) noexcept { m_offsetPos = offset; }

	//ViewMatrix��n�� const�Q�Ƃ�Ԃ� �Ăяo���ꂽ�ۂɂ��̃����o�͕ύX����Ȃ�,�i�����I�ɂ��j�|�C���^�[��Ԃ��Ȃ��̂Ȃ�����ق����ǂ�.
	// inline �Ăяo���ꂽ���ɂ��̊֐����R�s�y���邩�珈������������
	const DirectX::SimpleMath::Matrix& GetViewMatrix()const noexcept { return m_matrix; }

	const DirectX::SimpleMath::Vector3& GetRoll() const noexcept { return m_roll; }

private:

	 //�����_
	 DirectX::SimpleMath::Vector3 m_targetPosition;
	 //��]�̒��S
	 DirectX::SimpleMath::Vector3 m_rollCenterPosition;
	 //�J�����̈ʒu�i���[���h���W�j
	 //DirectX::SimpleMath::Vector3 eyePosition;
	 
	 //�J�����̈ʒu�i���[�J�����W�j
	 DirectX::SimpleMath::Vector3 m_offsetPos;
	 //�J�����̉�]��
	 DirectX::SimpleMath::Vector3 m_roll;
	 //�J�����̉�]
	 DirectX::SimpleMath::Matrix m_matrix;


};