#pragma once
#include "Game/PlayerCamera.h"

class CommonResources;

class Player
{
public:
	Player();
	~Player() = default;

	//初期化処理
	void Initialize(CommonResources* commonResources);
	//更新処理
	void Update(float elapsedTime);
	//描画処理
	void Render(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection
	);

	void RockOn(std::weak_ptr<Transform> transform);


	//プレイヤーの座標を渡す
	DirectX::SimpleMath::Vector3& GetPlayerPosition()
	{
		return m_position;
	}
	//プレイヤーの回転を渡す
	DirectX::SimpleMath::Quaternion& GetPlayerRotate()
	{
		return m_rotate;
	}

	const DirectX::SimpleMath::Matrix& GetPlayerCamera() const noexcept 
	{
		return  m_camera.GetViewMatrix();
	}



private:
	//共通リソース
	CommonResources* m_commonResources;
	//座標
	DirectX::SimpleMath::Vector3 m_position;
	//ワールド座標
	DirectX::SimpleMath::Matrix m_playerWorld;
	//回転
	DirectX::SimpleMath::Quaternion m_rotate;
	//移動ベクトル
	DirectX::SimpleMath::Vector3 m_moveVector;

	//移動速度
	const float SPEED = 0.1f;
	//摩擦
	static constexpr float FRICTION = 0.9f;

	//ロボットのモデル
	std::unique_ptr<DirectX::Model> m_robotModel;

	//カメラ
	PlayerCamera m_camera;
};