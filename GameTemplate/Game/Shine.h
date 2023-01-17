#pragma once

class Player;

/// <summary>
/// 光魔法
/// </summary>
class Shine :public IGameObject
{
public:

	/// <summary>
	///	実行されているか確認
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