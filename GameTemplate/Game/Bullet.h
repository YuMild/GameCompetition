#pragma once
class Background;
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
	ModelRender bulletRender;
	Vector3 bulletMoveSpeed;
	Vector3 bulletPosition;
	Player* player;
	Background* backGround;
	//タイマー。
	float deleteTimer = 0.0f;
};