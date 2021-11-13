#pragma once
class BackGround :public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	Vector3 m_position;
	ModelRender m_render;
	PhysicsStaticObject m_physicsStaticObject;
};

