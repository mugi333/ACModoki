#pragma once


class Transform
{
public:
	Transform();
	~Transform();

	void Update(float elapseTime);


	//アクセッサ―
	const DirectX::SimpleMath::Vector3& GetMoveVector()const noexcept { return m_moveVector; }
	const DirectX::SimpleMath::Vector3& GetPosition()const noexcept { return m_position; }
	const DirectX::SimpleMath::Quaternion& Getrotate()const noexcept { return m_rotate; }
	const DirectX::SimpleMath::Vector3& GetScale()const noexcept { return m_scale; }
	//ワールド行列を返す
	const DirectX::SimpleMath::Matrix   GetMatrix()const noexcept {
		return  DirectX::SimpleMath::Matrix::CreateScale(m_scale) * DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotate) * DirectX::SimpleMath::Matrix::CreateTranslation(m_position); }

	void SetMoveVector(const DirectX::SimpleMath::Vector3& moveVector) noexcept{ m_moveVector = moveVector; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) noexcept{ m_position = position; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) noexcept{ m_rotate = rotate; }
	void SetScale(const DirectX::SimpleMath::Vector3& scale) noexcept{ m_scale = scale; }


private:


	DirectX::SimpleMath::Vector3 m_moveVector;

	DirectX::SimpleMath::Vector3 m_position;

	DirectX::SimpleMath::Quaternion m_rotate;

	DirectX::SimpleMath::Vector3 m_scale;


};

