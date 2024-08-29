#pragma once


class TPS_Camera
{
public:


public:
	// コンストラクタ
	TPS_Camera();

	//デストラクタ
	~TPS_Camera();

	// 更新関数
	void Update();

	// プレイヤーの位置を設定する関数 noexcept-> 例外処理の一つランタイムエラーを吐かないようにする getterセッターが（内部的にも）ポインターを返さないのならつけたほうが良い。
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& position)noexcept {m_targetPosition = position;}

	//カメラの回転の中心の設定
	void SetrollCentPos(const DirectX::SimpleMath::Vector3& position)noexcept { m_rollCenterPosition = position; }

	//カメラの回転の設定
	void Setroll(const DirectX::SimpleMath::Vector3& roll)noexcept 
	{
		m_roll = roll; 
		
		//角度制限(クランプ処理)
		if (m_roll.x < -DirectX::XMConvertToRadians(89))
		{
			m_roll.x = -DirectX::XMConvertToRadians(89);
		}
		if (m_roll.x > DirectX::XMConvertToRadians(89))
		{
			m_roll.x = DirectX::XMConvertToRadians(89);
		}

	}

	void SetOffSet(const DirectX::SimpleMath::Vector3& offset) noexcept { m_offsetPos = offset; }

	//ViewMatrixを渡す const参照を返す 呼び出された際にそのメンバは変更されない,（内部的にも）ポインターを返さないのならつけたほうが良い.
	// inline 呼び出された所にその関数をコピペするから処理が少し早い
	const DirectX::SimpleMath::Matrix& GetViewMatrix()const noexcept { return m_matrix; }

	const DirectX::SimpleMath::Vector3& GetRoll() const noexcept { return m_roll; }

private:

	 //注視点
	 DirectX::SimpleMath::Vector3 m_targetPosition;
	 //回転の中心
	 DirectX::SimpleMath::Vector3 m_rollCenterPosition;
	 //カメラの位置（ワールド座標）
	 //DirectX::SimpleMath::Vector3 eyePosition;
	 
	 //カメラの位置（ローカル座標）
	 DirectX::SimpleMath::Vector3 m_offsetPos;
	 //カメラの回転量
	 DirectX::SimpleMath::Vector3 m_roll;
	 //カメラの回転
	 DirectX::SimpleMath::Matrix m_matrix;


};