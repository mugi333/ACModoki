#include "pch.h"
#include "CameraBase.h"

// 一応ディフォルト値を定義するけど調整して下さい
const float Ylib::CameraBase::EYE_SPEED_RATE = 0.05f;		// カメラの位置への距離の差分に対する割合
const float Ylib::CameraBase::TARGET_SPEED_RATE = 0.1f;	// 注視点への距離の差分に対する割合

// コンストラクタ
Ylib::CameraBase::CameraBase()
	: m_initFlag(true)
	, m_eyePt{}
	, m_targetPt{}
	, m_eyeMoveRate(EYE_SPEED_RATE)
	, m_targetMoveRate(TARGET_SPEED_RATE)
{
}


// カメラの切り替え時の初期化関数（切り替え時に呼び出すと補間しないよ！）
void Ylib::CameraBase::InitializeCamera()
{
	m_initFlag = true;
	m_eyeMoveRate = EYE_SPEED_RATE;
	m_targetMoveRate = TARGET_SPEED_RATE;


}

// カメラの位置とターゲットを指定する関数
void Ylib::CameraBase::SetPositionTarget(
	const DirectX::SimpleMath::Vector3& eye,
	const DirectX::SimpleMath::Vector3& target)
{
	if (m_initFlag == true)
	{
		m_initFlag = false;
		m_eyePt = eye;
		m_targetPt = target;
		return;
	}

	// カメラの位置を移動
	m_eyePt += (eye - m_eyePt) * m_eyeMoveRate;

	// カメラのターゲットの位置を移動
	m_targetPt += (target - m_targetPt) * m_targetMoveRate;

}
