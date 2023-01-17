#pragma once

#include "sound/SoundSource.h"

class Player;

/// <summary>
/// 炎魔法
/// </summary>
class Fire :public IGameObject
{
public:

	/// <summary>
	/// 実行されているか確認
	/// </summary>
	/// <returns></returns>
	bool GetMoving()const {
		return m_isMoving;
	}

	Fire();
	~Fire();
	bool Start()override;
	void Update()override;

private:

	Vector3				m_position;
	Vector3				m_magicCirclePosition;
	SoundSource*		m_fireSE					= nullptr;
	EffectEmitter*		m_fireEF					= nullptr;
	EffectEmitter*		m_fireMagicCircleEF			= nullptr;
	
	Player*				m_player					= nullptr;
	bool				m_isMoving					= false;
	float				m_aliveTimer				= 0.0f;
};