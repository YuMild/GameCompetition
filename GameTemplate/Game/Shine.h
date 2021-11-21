#pragma once

#include "sound/SoundSource.h"

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
	SoundSource* m_shineSE;
	EffectEmitter* m_shineEF;
	Enemy* m_enemy;
	Player* m_player;
	float m_aliveTimer = 0.0f;
};