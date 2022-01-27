#pragma once

class Player;

/// <summary>
/// …–‚–@
/// </summary>
class Water :public IGameObject
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

	Water();
	~Water();
	bool Start();
	void Update();

private:

	Vector3 m_position;
	Vector3 m_magicCirclePosition;
	EffectEmitter* m_waterEF;
	EffectEmitter* m_waterMagicCircleEF;
	SoundSource* m_waterSE;
	Player* m_player;
	float m_aliveTimer = 0.0f;
};