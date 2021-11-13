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
		return m_moveSpeed;
	}
private:
	ModelRender m_render;
	Vector3 m_position;
	Vector3 m_moveSpeed;
	Vector3 m_direction;
	EffectEmitter* m_fireBallEF;
	Player* m_player;
	//タイマー。
	float m_deletetimer = 0.0f;
};
