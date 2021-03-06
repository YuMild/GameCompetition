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