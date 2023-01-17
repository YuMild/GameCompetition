#pragma once

class Player;

/// <summary>
/// �����@
/// </summary>
class Shine :public IGameObject
{
public:

	/// <summary>
	///	���s����Ă��邩�m�F
	/// </summary>
	/// <returns></returns>
	bool GetMoving()const
	{
		return m_isMoving;
	}

	Shine();
	~Shine();
	bool Start()override;
	void Update()override;

private:

	Vector3				m_position;
	Vector3				m_magicCirclePosition;
	SoundSource*		m_shineSE					= nullptr;
	EffectEmitter*		m_shineEF					= nullptr;
	EffectEmitter*		m_shineMagicCircleEF		= nullptr;
	Player*				m_player					= nullptr;

	float				m_aliveTimer				= 0.0f;
	bool				m_isMoving					= false;
};