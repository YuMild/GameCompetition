#pragma once

class Player;

/// <summary>
/// 風魔法
/// </summary>
class Wind :public IGameObject
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