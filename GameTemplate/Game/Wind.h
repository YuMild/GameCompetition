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