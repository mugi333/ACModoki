#include "pch.h"
#include "Player.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"


Player::Player()
	: m_commonResources{}
	, m_position{}
	, m_playerWorld{}
	, m_rotate{}
	, m_robotModel{}
	
{
}

void Player::Initialize(CommonResources* commonResources)
{
	using namespace DirectX;

	m_commonResources = commonResources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	//座標、回転の初期化
	m_position = SimpleMath::Vector3::Zero;
	m_playerWorld = SimpleMath::Matrix::Identity;
	m_rotate = SimpleMath::Quaternion::Identity;

	// エフェクトファクトリーの作成
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	//モデルを読み込む

	m_robotModel = Model::CreateFromCMO(device, L"Resources/Models/Robot.cmo", *fx);


}

void Player::Update(float elapsedTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	const auto& kb = m_commonResources->GetInputManager()->GetKeyboardState();
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	

	//前進、後退
	if (kb.W)
	{
		SimpleMath::Vector3 scale;
		SimpleMath::Quaternion rotate;
		SimpleMath::Vector3 newPosition;

		(SimpleMath::Matrix::CreateTranslation(SimpleMath::Vector3(0.0f, 0.0f, -0.2f)) *
			SimpleMath::Matrix::CreateFromYawPitchRoll(m_camera.GetRoll().y, 0.0f, 0.0f)).
			Decompose(scale, rotate, newPosition);

		m_position += newPosition;
	}
	if (kb.S)
	{
		SimpleMath::Vector3 scale;
		SimpleMath::Quaternion rotate;
		SimpleMath::Vector3 newPosition;

		(SimpleMath::Matrix::CreateTranslation(SimpleMath::Vector3(0.0f, 0.0f, 0.2f)) *
			SimpleMath::Matrix::CreateFromYawPitchRoll(m_camera.GetRoll().y, 0.0f, 0.0f)).
			Decompose(scale, rotate, newPosition);

		m_position += newPosition;
	}
	if (kb.D)
	{
		SimpleMath::Vector3 scale;
		SimpleMath::Quaternion rotate;
		SimpleMath::Vector3 newPosition;

		(SimpleMath::Matrix::CreateTranslation(SimpleMath::Vector3(0.2f, 0.0f, 0.0f)) *
			SimpleMath::Matrix::CreateFromYawPitchRoll(m_camera.GetRoll().y, 0.0f, 0.0f)).
			Decompose(scale, rotate, newPosition);

		m_position += newPosition;
	}
	if (kb.A)
	{
		SimpleMath::Vector3 scale;
		SimpleMath::Quaternion rotate;
		SimpleMath::Vector3 newPosition;

		(SimpleMath::Matrix::CreateTranslation(SimpleMath::Vector3(-0.2f, 0.0f, 0.0f)) *
			SimpleMath::Matrix::CreateFromYawPitchRoll(m_camera.GetRoll().y, 0.0f, 0.0f)).
			Decompose(scale, rotate, newPosition);

		m_position += newPosition;
	}
	
	


	////旋回
	//if (kb.Left)
	//{
	//	m_rotate *= Quaternion::CreateFromAxisAngle(
	//		Vector3::UnitY, XMConvertToRadians(5.0f));
	//}
	//if (kb.Right)
	//{
	//	m_rotate *= Quaternion::CreateFromAxisAngle(
	//		Vector3::UnitY, XMConvertToRadians(-5.0f));
	//}


	m_camera.SetPlayerPosition(m_position);
	m_camera.Updata(elapsedTime);
}

void Player::Render(
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection)
{
	using namespace DirectX;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// ロボットを移動させる
	SimpleMath::Matrix m = SimpleMath::Matrix::CreateRotationY(DirectX::XM_PI)*SimpleMath::Matrix::CreateFromQuaternion(m_rotate)
		* SimpleMath::Matrix::CreateTranslation(m_position);

	m_robotModel->Draw(context, *states, m, view, projection,false);
	context->RSSetState(states->CullNone());



}

void Player::RockOn(std::weak_ptr<Transform> transform)
{

	m_camera.RockOn(transform);

}
