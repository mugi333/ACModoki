#include "pch.h"
#include "Enemy.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"

Enemy::Enemy()
	: m_commonResources{}
	, m_Model{}
{
	m_transform.reset(new Transform);
}

Enemy::~Enemy()
{
}

void Enemy::Initialize(CommonResources* commonResources)
{
	using namespace DirectX;

	m_commonResources = commonResources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	

	// エフェクトファクトリーの作成
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	//モデルを読み込む

	m_Model = Model::CreateFromCMO(device, L"Resources/Models/Tank.cmo", *fx);

}

void Enemy::Update(float elapsedTime)
{
}

void Enemy::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	using namespace DirectX;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// ロボットを移動させる
	SimpleMath::Matrix m =  SimpleMath::Matrix::CreateFromQuaternion(m_transform->Getrotate())
		* SimpleMath::Matrix::CreateTranslation(m_transform->GetPosition());

	m_Model->Draw(context, *states, m, view, projection, false);
	context->RSSetState(states->CullNone());

}
