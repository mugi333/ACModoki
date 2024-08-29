#include "pch.h"
#include "PlayerCamera.h"
#include "TPS_Camera.h"
#include "Libraries/Ylib/Transform.h"
#include <iostream>

PlayerCamera::PlayerCamera()
	: m_playerPotition{0.0f,0.0f,0.0f}
	, m_rockonAnimationTimer{0.0f}
	, m_rockonState{RockonState::Off}
	, m_tpsCamera{new TPS_Camera}
	, m_rockonTarget{}
	, m_x{0}
	, m_y{0}
{
	m_tpsCamera.reset(new TPS_Camera);

}

PlayerCamera::~PlayerCamera()
{

}

void PlayerCamera::Updata(float elapsedTime)
{
	m_tpsCamera->SetrollCentPos(m_playerPotition);

	switch (m_rockonState)
	{
	case PlayerCamera::RockonState::On:
		//ランタイムエラーが起こったらここのlockが原因かも
	//もらってきたポインターが生きてるかを見る関数があるからそれを使ってRockAnimeをOffAnimeにしてOFFに入らないようにする
		m_tpsCamera->SetTargetPosition(m_rockonTarget.lock()->GetPosition());

		//カメラを敵の方向へ向ける
		{
			//プレイヤーから見た敵の座標
			DirectX::SimpleMath::Vector3 localEnemyPosition = 
				m_rockonTarget.lock()->GetPosition() - m_playerPotition;

			m_nowRotate.y = DirectX::XM_PI
				+ atan2(localEnemyPosition.x, localEnemyPosition.z);

		}
	
		break;
	case PlayerCamera::RockonState::Off:
	
		m_tpsCamera->SetTargetPosition(m_playerPotition);

		break;
	case PlayerCamera::RockonState::OnAnime:
		m_rockonState = RockonState::On;

		break;
	case PlayerCamera::RockonState::OffAnime:
		m_rockonState = RockonState::Off;

		break;
	}

	m_tpsCamera->Setroll(m_nowRotate);


	m_tpsCamera->Update();
}



void PlayerCamera::RockOn(std::weak_ptr<Transform> transform)
{

	m_rockonTarget = transform;
	m_rockonState = RockonState::OnAnime;

}

void PlayerCamera::UnRockOn()
{
	m_rockonState = RockonState::OffAnime;


}

void PlayerCamera::OnMouseMove(float x, float y)
{
	
	if (m_rockonState == RockonState::On)
	{
		return;
	}

	m_nowRotate.x -= (y - (HEIGHT / 2)) / 1000.0f;
	m_nowRotate.y -= (x - (WIDTH / 2)) / 1000.0f;
	

	Input::GetInstance().SetCursolPosition(WIDTH/2, HEIGHT/2);

}

void PlayerCamera::ZAnim(bool isMoveInput)
{
	if (isMoveInput)
	{
		m_cameraZAnim += CAMERA_Z_SPEED;
	}
	else
	{
		m_cameraZAnim -= CAMERA_Z_SPEED;
	}

	//(クランプ処理)
	if (m_cameraZAnim < 0)
	{
		m_cameraZAnim = 0;
	}
	if (m_cameraZAnim > 1.0f)
	{
		m_cameraZAnim = 1.0f;
	}
	DirectX::SimpleMath::Vector3 newOffset;

	//ラープ処理
	newOffset.z = MIN_CAMERA_DISTANCE + m_cameraZAnim *
		(MAX_CAMERA_DISTANCE - MIN_CAMERA_DISTANCE);

	m_tpsCamera->SetOffSet(newOffset);

}


const DirectX::SimpleMath::Matrix& PlayerCamera::GetViewMatrix() const noexcept
{
	return m_tpsCamera->GetViewMatrix();
}

const DirectX::SimpleMath::Vector3& PlayerCamera::GetRoll() const noexcept
{
	return m_tpsCamera->GetRoll();
}


