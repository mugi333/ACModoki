#include "pch.h"
#include "Transform.h"

Transform::Transform()
	: m_moveVector{0.0f,0.0f,0.0f}
	, m_position{ 0.0f,0.0f,0.0f }
	, m_rotate{DirectX::SimpleMath::Quaternion::Identity}
	, m_scale{ 0.0f,0.0f,0.0f }
{
}

Transform::~Transform()
{

}

void Transform::Update(float elapseTime)
{
	
	m_position += m_moveVector * elapseTime;

}
