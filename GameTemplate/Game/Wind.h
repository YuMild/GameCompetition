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
	bool Start();
	void Update();

private:

	Vector3 m_position;
	Vector3 m_magicCirclePosition;
	EffectEmitter* m_windEF;
	EffectEmitter* m_windMagicCircleEF;
	SoundSource* m_windSE;
	Player* m_player;
	float m_aliveTimer = 0.0f;
};