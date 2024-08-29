#pragma once
#include "Game/PlayerCamera.h"

class CommonResources;

class Player
{
public:
	Player();
	~Player() = default;

	//����������
	void Initialize(CommonResources* commonResources);
	//�X�V����
	void Update(float elapsedTime);
	//�`�揈��
	void Render(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection
	);

	void RockOn(std::weak_ptr<Transform> transform);


	//�v���C���[�̍��W��n��
	DirectX::SimpleMath::Vector3& GetPlayerPosition()
	{
		return m_position;
	}
	//�v���C���[�̉�]��n��
	DirectX::SimpleMath::Quaternion& GetPlayerRotate()
	{
		return m_rotate;
	}

	const DirectX::SimpleMath::Matrix& GetPlayerCamera() const noexcept 
	{
		return  m_camera.GetViewMatrix();
	}



private:
	//���ʃ��\�[�X
	CommonResources* m_commonResources;
	//���W
	DirectX::SimpleMath::Vector3 m_position;
	//���[���h���W
	DirectX::SimpleMath::Matrix m_playerWorld;
	//��]
	DirectX::SimpleMath::Quaternion m_rotate;
	//�ړ��x�N�g��
	DirectX::SimpleMath::Vector3 m_moveVector;

	//�ړ����x
	const float SPEED = 0.1f;
	//���C
	static constexpr float FRICTION = 0.9f;

	//���{�b�g�̃��f��
	std::unique_ptr<DirectX::Model> m_robotModel;

	//�J����
	PlayerCamera m_camera;
};