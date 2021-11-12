#pragma once
class Player;

#include "sound/SoundSource.h"

class Bullet :public IGameObject
{
public:
	Bullet();
	~Bullet();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	Vector3 GetMoveSpeed() const
	{
		return moveSpeed;
	}
private:
	ModelRender render;
	Vector3 position;
	Vector3 moveSpeed;
	Vector3 direction;
	Player* player;
	//タイマー。
	float deletetimer = 0.0f;
};
