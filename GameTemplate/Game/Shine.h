#pragma once

class Enemy;
class Player;

class Shine :public IGameObject
{
public:
	Shine();
	~Shine();
	bool Start();
	void Update();

private:
	Vector3 m_position;
	Vector3 m_direction;
	Vector3 m_rotation;
	Vector3 m_enemyMoveSpeed;
	EffectEmitter* m_shineEF;
	Enemy* m_enemy;
	Player* m_player;
	float m_aliveTimer = 0.0f;
};