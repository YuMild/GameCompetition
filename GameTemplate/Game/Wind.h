#pragma once

#include "sound/SoundSource.h"

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
	Vector3 m_magicCirclePosition;
	EffectEmitter* m_windEF;
	EffectEmitter* m_windMagicCircleEF;
	SoundSource* m_windSE;
	Enemy* m_enemy;
	Player* m_player;
	float m_aliveTimer = 0.0f;
};