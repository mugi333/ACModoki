#pragma once
#include "Libraries/Ylib/Transform.h"

class CommonResources;


class Enemy 
{
public:
	Enemy();
	~Enemy();

	//初期化処理
	void Initialize(CommonResources* commonResources);
	//更新処理
	void Update(float elapsedTime);
	//描画処理
	void Render(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection
	);


	const std::weak_ptr<Transform> GetTransform() { return m_transform; }

private:
	//共通リソース
	CommonResources* m_commonResources;
	
	//モデル
	std::unique_ptr<DirectX::Model> m_Model;

	std::shared_ptr<Transform> m_transform;

};

