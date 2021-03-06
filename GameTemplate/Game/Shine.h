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
	bool Start();
	void Update();

private:

	Vector3 m_position;
	Vector3 m_magicCirclePosition;
	SoundSource* m_shineSE;
	EffectEmitter* m_shineEF;
	EffectEmitter* m_shineMagicCircleEF;
	Player* m_player;
	float m_aliveTimer = 0.0f;
	bool m_isMoving = false;
};