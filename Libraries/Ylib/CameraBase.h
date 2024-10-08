#pragma once

namespace Ylib
{
	class CameraBase
	{
	public:
		CameraBase();
		virtual~CameraBase() {};

		// カメラの切り替え時の初期化関数（切り替え時に呼び出すと補間しないよ！）
		void InitializeCamera();

		// カメラの位置とターゲットを指定する関数
		void SetPositionTarget(const DirectX::SimpleMath::Vector3& eye
			, const DirectX::SimpleMath::Vector3& target);

		// 視点の位置を取得する関数
		const DirectX::SimpleMath::Vector3& GetEyePosition() { return m_eyePt; }

		// 注目点の位置を取得する関数
		const DirectX::SimpleMath::Vector3& GetTargetPosition() { return m_targetPt; }

		// カメラの位置への距離の差分に対する割合を設定する関数
		void SetCameraEyeMoveRate(float rate) { m_eyeMoveRate = rate; }

		// 注視点への距離の差分に対する割合を設定する関数
		void SetCameraTargetMoveRate(float rate) { m_targetMoveRate = rate; }

	private:

		// カメラの位置への距離の差分に対する割合
		static const float EYE_SPEED_RATE;

		// 注視点への距離の差分に対する割合
		static const float TARGET_SPEED_RATE;

		// 視点の位置
		DirectX::SimpleMath::Vector3 m_eyePt;

		// 注目点の位置
		DirectX::SimpleMath::Vector3 m_targetPt;

		// カメラの位置への距離の差分に対する割合
		float m_eyeMoveRate;

		// 注視点への距離の差分に対する割合
		float m_targetMoveRate;

		// カメラの位置の初期化フラグ
		bool m_initFlag;

	};


}