#pragma once
class Bullet;
class BackGround :public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	Vector3 stageposition;
	Vector3 diff;
	ModelRender stagerender;
	PhysicsStaticObject physicsStaticObject;
	Bullet* bullet;
};