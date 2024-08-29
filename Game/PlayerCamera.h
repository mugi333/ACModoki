#pragma once
#include "Libraries/Ylib/InputHundler.h"

//‘O•ûéŒ¾
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

	//Œ»İ‚ÌƒJƒƒ‰‚Ì‰ñ“]—Ê
	DirectX::SimpleMath::Vector3 m_nowRotate;


};

