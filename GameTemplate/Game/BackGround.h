#pragma once
class BackGround :public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	Vector3 position;
	ModelRender render;
	PhysicsStaticObject physicsStaticObject;
};

