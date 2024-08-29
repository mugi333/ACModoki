#include "pch.h"
#include "TPS_Camera.h"




TPS_Camera::TPS_Camera()
	: m_targetPosition{0.0f,0.0f,0.0f}
	, m_offsetPos{ 0.0f,0.0f,10.0f }
	, m_roll{ 0.0f,0.0f,0.0f }
	, m_rollCenterPosition{ 0.0f,0.0f,0.0f }
	, m_matrix{DirectX::XMMatrixIdentity()}
{
	
}

TPS_Camera::~TPS_Camera()
{

}

void TPS_Camera::Update()
{

	using namespace DirectX;

	m_matrix = DirectX::XMMatrixTranslationFromVector(m_offsetPos);
	m_matrix *= DirectX::XMMatrixRotationRollPitchYawFromVector(m_roll);
	m_matrix *= DirectX::XMMatrixTranslationFromVector(m_rollCenterPosition);
 
	DirectX::XMVECTOR eyePos;            //    カメラ位置（ワールド座標）
	DirectX::XMVECTOR scale;
	DirectX::XMVECTOR rotate;

	DirectX::XMMatrixDecompose(&scale, &rotate , &eyePos, m_matrix);

	m_matrix = DirectX::XMMatrixLookAtRH(eyePos, m_targetPosition, DirectX::SimpleMath::Vector3::Up);


}

