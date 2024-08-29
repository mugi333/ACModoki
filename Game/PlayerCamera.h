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

	void SetPlayerPosition(const DirectX::SimpleMath::Vector3& position) { m_playerPotition = position; }

	void RockOn(std::weak_ptr<Transform> transform);

	void UnRockOn();

	virtual void OnMouseMove(float x, float y) override;

	//
	const DirectX::SimpleMath::Matrix& GetViewMatrix() const noexcept;

	const DirectX::SimpleMath::Vector3& GetRoll() const noexcept;

	bool IsLockOn()const noexcept {
		return m_rockonState == RockonState::On && m_rockonState == RockonState::OnAnime; }

private:

	static const int WIDTH = 1280;
	static const int HEIGHT = 720;

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



	std::unique_ptr<TPS_Camera> m_tpsCamera;

	float m_x;
	float m_y;

	//åªç›ÇÃÉJÉÅÉâÇÃâÒì]ó 
	DirectX::SimpleMath::Vector3 m_nowRotate;


};

