#pragma once

class Player;

/// <summary>
/// 水魔法
/// </summary>
class Water :public IGameObject
{
public:

	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition() const
	{
		return m_position;
	}

	Water();
	~Water();
	bool Start()override;
	void Update()override;

private:

	Vector3				m_position;
	Vector3				m_magicCirclePosition;
	EffectEmitter*		m_waterEF					= nullptr;
	EffectEmitter*		m_waterMagicCircleEF		= nullptr;
	SoundSource*		m_waterSE					= nullptr;
	Player*				m_player					= nullptr;

	float				m_aliveTimer				= 0.0f;
};