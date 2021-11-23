#pragma once
class Player;

#include "sound/SoundSource.h"

class Bullet :public IGameObject
{
public:
	Vector3 GetPosition() const
	{
		return m_position;
	}
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
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
	Vector3 m_forward;
	Vector3 collisionPosition;
	CollisionObject* collisionObject;
	EffectEmitter* m_fireBallEF;
	SoundSource* m_gunShotSE;
	Player* m_player;
	//タイマー。
	float m_deleteTimer = 0.0f;
};
