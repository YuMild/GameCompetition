#pragma once

/// <summary>
/// �X�e�[�W
/// </summary>
class BackGround :public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	Vector3					m_position;
	ModelRender				m_stageMR;
	PhysicsStaticObject		m_physicsStaticObject;
};

