#pragma once

#include "sound/SoundSource.h"

class Player;

class Fire :public IGameObject
{
public:
	bool GetMoving()const {
		return m_isMoving;
	}
	Fire();
	~Fire();
	bool Start();
	void Update();

private:
	Vector3 m_position;
	Vector3 m_magicCirclePosition;
	SoundSource* m_fireSE;
	EffectEmitter* m_fireEF;
	EffectEmitter* m_fireMagicCircleEF;
	
	Player* m_player;
	bool m_isMoving = false;
	float m_aliveTimer = 0.0f;
};