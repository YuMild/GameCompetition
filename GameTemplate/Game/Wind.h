#pragma once

class Enemy;
class Player;

class Wind :public IGameObject
{
public:
	Vector3 GetPosition() const
	{
		return m_position;
	}
	Wind();
	~Wind();
	bool Start();
	void Update();

private:
	Vector3 m_position;
	EffectEmitter* m_windEF;
	Enemy* m_enemy;
	Player* m_player;
	float m_aliveTimer = 0.0f;
};