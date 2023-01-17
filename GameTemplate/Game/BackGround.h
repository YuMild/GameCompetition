#pragma once

/// <summary>
/// ステージ
/// </summary>
class BackGround :public IGameObject
{
public:
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

private:
	Vector3					m_position;
	ModelRender				m_stageMR;
	PhysicsStaticObject		m_physicsStaticObject;
};

