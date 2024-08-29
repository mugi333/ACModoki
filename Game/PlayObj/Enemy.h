#pragma once
#include "Libraries/Ylib/Transform.h"

class CommonResources;


class Enemy 
{
public:
	Enemy();
	~Enemy();

	//����������
	void Initialize(CommonResources* commonResources);
	//�X�V����
	void Update(float elapsedTime);
	//�`�揈��
	void Render(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection
	);


	const std::weak_ptr<Transform> GetTransform() { return m_transform; }

private:
	//���ʃ��\�[�X
	CommonResources* m_commonResources;
	
	//���f��
	std::unique_ptr<DirectX::Model> m_Model;

	std::shared_ptr<Transform> m_transform;

};

