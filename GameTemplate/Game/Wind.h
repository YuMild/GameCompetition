#pragma once

class Player;

/// <summary>
/// •—–‚–@
/// </summary>
class Wind :public IGameObject
{
public:

	/// <summary>
	/// À•W‚ğæ“¾
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition() const
	{
		return m_position;
	}

	Wind();
	~Wind();
	bool Start()override;
	void Update()override;

private:

	Vector3				m_position;
	Vector3				m_magicCirclePosition;
	EffectEmitter*		m_windEF					= nullptr;
	EffectEmitter*		m_windMagicCircleEF			= nullptr;
	SoundSource*		m_windSE					= nullptr;
	Player*				m_player					= nullptr;

	float				m_aliveTimer				= 0.0f;
};