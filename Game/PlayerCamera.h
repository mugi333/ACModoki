#pragma once
#include "Libraries/Ylib/InputHundler.h"

//ëOï˚êÈåæ
class Transform;
class TPS_Camera;

class PlayerCamera :public Input::Hundler
{
public:
	PlayerCamera();
	~PlayerCamera();

	void Updata(float elapsedTime);

	void SetPlayerPosition(const DirectX::SimpleMath::Vector3& position) 
	{ m_playerPotition = position; 
	  m_playerPotition += PLAYER_POSITION_OFFSET;
	}

	void RockOn(std::weak_ptr<Transform> transform);

	void UnRockOn();

	virtual void OnMouseMove(float x, float y) override;

	void ZAnim(bool isMoveInput);

	//
	const DirectX::SimpleMath::Matrix& GetViewMatrix() const noexcept;

	const DirectX::SimpleMath::Vector3& GetRoll() const noexcept;

	bool IsLockOn()const noexcept {
		return m_rockonState == RockonState::On || m_rockonState == RockonState::OnAnime; }

private:

	static constexpr int WIDTH = 1280;
	static constexpr int HEIGHT = 720;

	static constexpr float MIN_CAMERA_DISTANCE = 3.0f;

	static constexpr float MAX_CAMERA_DISTANCE = 10.0f;

	static constexpr float CAMERA_Z_SPEED = 0.01f;

	static constexpr DirectX::SimpleMath::Vector3 PLAYER_POSITION_OFFSET =
		DirectX::SimpleMath::Vector3(0, 1.0f, 0);



	enum class RockonState
	{

		On,
		Off,
		OnAnime,
		OffAnime

	};
	DirectX::SimpleMath::Vector3 m_playerPotition;

    std::weak_ptr<Transform>  m_rockonTarget;

	RockonState m_rockonState;

	float m_rockonAnimationTimer;

	float m_cameraDistance;

	float m_cameraZAnim;

	std::unique_ptr<TPS_Camera> m_tpsCamera;

	float m_x;
	float m_y;

	//åªç›ÇÃÉJÉÅÉâÇÃâÒì]ó 
	DirectX::SimpleMath::Vector3 m_nowRotate;


};

